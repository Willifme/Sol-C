# Sol-C 

This is a rewrite of Sol a toy programming langauge orginally written in Ruby.
It exists for two reasons - speed using something like C for speed removes any
silly optimisations that might have to be in the Ruby codebase which could 
result in bad code or having to mess with alternative versions of Ruby interpreters. C also has a mucher richer ecosystem for the building of compilers which
ruby does not have. This is very much a work in progress with barely anything working. This project also serves as me to better understand C to a better level.

## Todo

* Make the parser fully capable of parsing Sol code.
* Develop through tests atleast equivalant to the Ruby ones.
* A proper REPL.
* A better Makefile (I have little experience of building them).
* Optimisations to be made once the compiler reaches a decent stage of capability. 
* A good AST.
* Someform of codegen either LibJIT or LLVM (Leaning towards LLVM).
* Documentation which exists.
* A furthered language design with refined features.
