# Cyan
## The dynamically-typed, compiled programming language 

> upload your code to Github ffs

– My friend

This language is a work in progress. The repository (a horible mess at the moment) contains:
- `cyan/` The code for the "compiler"
- `lib/` Legacy code
- `legacy_code/` Also legacy code
- `src/` The Cyan backend. Handles the basic mechanics of the language

## How does it work?

The language compiler is an intermediate program that parses the Cyan code and translates it into C++ code. This new code is then actually compiled by `clang` or whatever, producing a standalone executable.