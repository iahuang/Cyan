""" Cyan syntax parser """

import re
from collections import namedtuple
from utils import removeall


class CharacterSets:
    alpha_l = set("abcdefghijklmnopqrstuvwxyz")
    alpha_u = set("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
    alpha = alpha_l.union(alpha_u)
    alpha_v = alpha.union(set("_"))
    num = set("0123456789")
    num_f = set("0123456789.")
    var = alpha.union(num).union(set("_."))
    grouping = ["()", '""', "''", "[]", "{}"]
    brackets = ["()", "[]", "{}"]


def find_type(s):
    return "function"


def parse_csv(s, separator=",", valid_grouping=CharacterSets.grouping, escape_token="\\", strip_whitespace=True):
    """ Split a string on character, ignoring escaped and grouped characters """

    assert len(separator) == 1, "Separator must be a single character"
    return parse_dsv(s, [separator], valid_grouping, escape_token, strip_whitespace)[::2]


def parse_dsv(s, separators=[","], valid_grouping=CharacterSets.grouping, escape_token="\\", strip_whitespace=True):
    """ Split a string on characters, ignoring escaped and grouped characters """

    s = group(s, valid_grouping=valid_grouping,
                      escape_token=escape_token)
    split = []
    block = ""
    for c in s:
        if c in separators:
            if strip_whitespace:
                block = block.strip()
            split.append(block)
            block = ""
            split.append(c)
        else:
            block += c
    split.append(block)

    return split


def strip_grouping(s, grouping=CharacterSets.brackets):
    """ Removes any possible forms of grouping from s """
    i = 0
    while i < len(grouping):
        opening, closing = grouping[i]
        if s.startswith(opening) and s.endswith(closing):
            i = 0  # Repeat to check for extraneous brackets (((((hmmm)))))
            s = s[1:-1]  # Remove first and last chars
        i += 1
    return s


def escape_values(s, valid_set=CharacterSets.var):
    s = group(s)

    block = ""
    string = []
    last_valid = True
    for c in s:
        if c in valid_set:
            block += c
        else:
            if block:
                string.append(block)
                block = ""
            string.append(c)
    if block:
        string.append(block)
    return string

def group_quotes(s, grouping="\"'", escape_token="\\"):
    stack = []
    block = ""
    string = []
    for c in escape(s, token=escape_token):
        if c in grouping:  # Open group
            if not stack: # Lowest level
                stack.append(c)
                block = c
            elif stack[-1] == c: # Close group
                string.append(block+c)
                stack = stack[:-1]
                block = ""
            else:
                stack.append(c)
        elif stack == []:  # Is on root nesting, and delimiter is reached
            string.append(c)
        else:
            block += c

    if block:
        string.append(block)

    return string

def group_brackets(s, valid_grouping=CharacterSets.brackets, escape_token="\\"):
    opening = {g[0]: g[1] for g in valid_grouping}
    closing = {g[1]: g[0] for g in valid_grouping}
    stack = []
    block = ""
    string = []
    for c in escape(s, token=escape_token):
        if c in opening:  # Open group ex: (
            stack.append(c)

        if c in closing:  # Close group ex: )
            if closing[c] != stack[-1]:  # Unbalanced brackets
                raise SyntaxError("Unbalanced brackets")
            stack = stack[:-1]
            block += c
            if stack == []:
                string.append(block)
                block = ""
                
        elif stack == []:  # Is on root nesting, and delimiter is reached
            string.append(c)
        else:
            block += c
    return string

def group(s,valid_grouping=CharacterSets.grouping, escape_token="\\"):
    quote_grouping = []
    bracket_grouping = []

    for g in valid_grouping:
        if g[0] == g[1]:
            quote_grouping.append(g[0])
        else:
            bracket_grouping.append(g)
    
    return group_brackets(group_quotes(s, quote_grouping, escape_token), bracket_grouping, escape_token)

def escape(s, token="\\"):
    """ Group escaped characters into one cell """
    chrs = []
    i = 0
    while i < len(s):
        c = s[i]
        if c == token:
            chrs.append(c+s[i+1])
            i += 1
        else:
            chrs.append(c)
        i += 1
    return chrs


class Token:  # An atomic part of an Expression that represents a raw value. A variable, type literal, etc.
    def __init__(self, s):
        self.data = s
        self.type = Token.parse_token(s)
        if self.type == "list":
            self.data = []
            subexp = parse_csv(strip_grouping(s))

            for exp in subexp:
                self.data.append(Node.parse(exp))

    @staticmethod
    def parse_token(s):
        if all([c in CharacterSets.var for c in s]) and any([c in CharacterSets.alpha_v for c in s]):
            return "name"
        if all([c in CharacterSets.num for c in s]):
            return "int"
        if all([c in CharacterSets.num_f for c in s]):
            return "float"
        if s.startswith('"') and s.endswith('"'):
            return "string"
        if s.startswith('[') and s.endswith(']'):
            return "list"

        return "undefined"

    def __str__(self):
        return self.type.upper()+" "+str(self.data)


class BinaryOp:
    def __init__(self, chars, type="binary", debug_name=None):
        """ Type is either 'binary' or 'arg'
        binary - Default type. a*b 1+2, 0xff<<1, etc. 
        arg    - array[index], function(arg1, arg2), etc."""
        self.type = type
        self.chars = chars
        if debug_name == None:
            self.debug_name = chars
        else:
            self.debug_name = debug_name

    def matches_token(self, token, last):
        if not isinstance(token, str):
            return False
        if self.type == "binary":
            return token == self.chars
        elif self.type == "arg":
            if last == None:
                return False

            if isinstance(last, str):
                if Token.parse_token(last) != "name":
                    return False

            op, cl = self.chars
            return token.startswith(op) and token.endswith(cl)

    def handle(self, values, at):
        if self.type == "binary":
            a, op, b = values[at-1:at+2]
            a = Node.parse(a)
            b = Node.parse(b)
            values.insert(at+2, Node(args=[a, b], op=self))
            del values[at-1:at+2]
        elif self.type == "arg":
            a, args = values[at-1:at+1]
            a = Node.parse(a)
            args = Node.parse(strip_grouping(args))
            values.insert(at+1, Node(args=[a, args], op=self))
            del values[at-1:at+1]


def preparse(s):
    return removeall(escape_values(strip_grouping(s, grouping=["()"])), " ")


class Node:
    pemdas = [  # Expanded order of operations.
        BinaryOp(","),
        BinaryOp("()", type="arg"),
        BinaryOp("*"),
        BinaryOp("/"),
        BinaryOp("+"),
        BinaryOp("-")
    ]

    def __init__(self, args=None, op=None):
        self.args = tuple((a if isinstance(a, Node) else Token(a)
                           for a in args))
        self.op = op

    @staticmethod
    def parse(s):
        if isinstance(s, Node):
            return s
        values = preparse(s)

        if len(values) == 1:
            return Node(args=values)

        for op in Node.pemdas:
            i = 0
            while i < len(values):
                token = values[i]
                last = values[i-1] if i > 0 else None
                if op.matches_token(token, last):
                    op.handle(values, i)
                    i = 0
                else:
                    i += 1

        return values[0]

    @property
    def atomic(self):
        return len(self.args) == 1

    @property
    def binary(self):
        return len(self.args) == 2

    def __repr__(self):
        if self.atomic:
            return str(self.args[0])
        elif self.binary:
            return "("+str(self.args[0])+" "+self.op.debug_name+" "+str(self.args[1])+")"


class Parser:
    def __init__(self):
        self.lines = []

    def parse(self, s):
        t = find_type(s)
        line = Line(t)

        if t == "function":
            name, args = self.parse_function(s)
            assert args != None, "Error parsing function call"
            line.args = args

            line.fname = name

        self.lines.append(line)

    def parse_function(self, s):
        name = re.findall("\w+(?=\()", s)[0]
        if name:
            argstring = re.findall("(?<=\().+(?=\))", s)[0]
            args = argstring.split(",")

            return name, list([Token(arg) for arg in args])


class Line:
    def __init__(self, s):
        self.s = s
        self.assign = None
        self.head = None
        self.expression = s
        values = group(s)

        if "=" in values:
            segs = parse_csv(s,separator='=',strip_whitespace=True)
            self.expression = segs[1]
            self.assign = segs[0]

        self.head = Node.parse(self.expression)


def tests():
    assert escape("a\\\"\\b") == ["a", "\\\"", "\\b"]
    assert parse_csv("a, b, (c,d), \\\",2") == ['a', 'b', '(c,d)', '\\"', '2']
    # print(group_quotes(""" abc "def" 123 """,grouping=['"']))

if __name__ == "__main__":
    print("Running tests...")
    tests()
    # print(parse_csv("print(oofer()) + of (oof)", separator="("))
    # print(group("oofer (oofer ()oof) (oof)"))
    #print(escape_values("oof(thing()) + ree() - a * b(S)"))
    #exp = Node.parse("function(b+6, 8, 9) * (1*2+1.2) - [1,(2+3)]")
    line = Line('print("Hello World!")')

    print(line.head)
