# Stack
A small stack based programming language written in C.

## Notes
- There are quite a few formatting issues, due to a tab v spaces problem with VS Code.
- Some of the code is quite bad. For example:
  - parse.c: This file contains quite a lot of code that it shouldn't.
    - The actual code is bad aswell: slow, verbose, inefficent. (oh and memory is not being managed properly.)
  - stacky.c: This doesn't check the amount of command arguments supplied. A small thing but oh well.
  - Some of the operations are parsed and performed at 'run-time'. This isn't good. (`jump` and `ifeq`)
- stack.c and stack.h on the other hand I think are quite good. But again, that might just be me.

## Using Stack
Currently there are 12 operations
```
push
pop
add
sub
mult
dup
print
swap
div
jump
ifeq
set
```
`push` takes one argument (`x`) and pushed `x` onto the top of the stack.
  - e.g `push 10` will push 10 on top of the stack.
`pop` takes no arguments and removes the top element from the stack.
  - e.g ``` 
         push 10
         push 20
         pop
         ``` will leave 10 at the top of the stack.
