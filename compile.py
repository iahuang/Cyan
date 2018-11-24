import sys
from cyan.translate import Translator

target = sys.argv[1]

with open(target) as fl:
    s = fl.read()

trans = Translator("lib")

with open("main.cpp","w") as fl:
    fl.write(trans.build(s))
