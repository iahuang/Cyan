# Cyan
**A dynamically-typed, compiled programming language, designed for speed and usability**

> upload your code to Github ffs

– My friend

This language is a work in progress. The repository (a horible mess at the moment) contains:
- `cyan/` The code for the "compiler"
- `lib/` Legacy code
- `legacy_code/` Also legacy code. The names of the subfolders don't really makes sense
- `src/` The Cyan backend. Handles the basic mechanics of the language

## How does it work?

The language compiler is an intermediate program that parses the Cyan code and translates it into C++ code. This new code is then actually compiled by `clang` or whatever, producing a standalone executable.

## The C++ backend

Honestly, I don't even know how it works, and I wrote the stupid thing. This is partially because the system is a result of mostly trial and error, and because I succ at C++

Find out more about the language (here)[https://github.com/iahuang/Cyan/wiki]
