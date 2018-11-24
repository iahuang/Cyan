import cyan.parser
import os

def tokenize(token):
    if token.type == "string":
        return "String({})".format(token.s)

class Translator:
    def __init__(self, libpath):
        self.libpath = libpath

        with open(libpath+"/includes.txt") as fl:
            self.includes = fl.read().split("\n")
        self.parser = cyan.parser.Parser()
      
    def build(self, s):
        self.parser.parse(s)
        output = ""
        for include in self.includes:
            with open(self.libpath+"/"+include) as fl:
                output+=fl.read()+"\n"
        output+="int main() {\n"
        for line in self.parser.lines:
            translated = ""
            if line.t == "function":
                translated = line.fname+"("+",".join([tokenize(arg) for arg in line.args])+")"
            output+=translated+";\n"
        output+="return 0;\n}"
        os.system("make")
        return output