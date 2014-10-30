# Sol-C

This is a rewrite of Sol a toy programming language originally written in Ruby.
It exists for two reasons - speed using something like C for speed removes any
silly optimisations that might have to be in the Ruby codebase which could
result in bad code or having to mess with alternative versions of Ruby interpreters. C also has a much richer ecosystem for the building of compilers which
ruby does not have. This is very much a work in progress with barely anything working. This project also serves as me to better understand C to a decent level.

## Todo

* Make the parser fully capable of parsing Sol code.
* Develop through tests at least equivalent to the Ruby ones.
* A proper REPL. - Partially done however cannot handle newlines
* A better Makefile (I have little experience of building them).
* Optimisations to be made once the compiler reaches a decent stage of capability.
* A good AST. - Partially done
* Proper printing of the AST 
* Someform of codegen either LibJIT or LLVM (Leaning towards LLVM).
* Documentation which exists.
* A furthered language design with refined features.
