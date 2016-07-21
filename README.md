# Stack [![Build status](https://travis-ci.org/DontBelieveMe/Stack.svg?branch=master)](https://travis-ci.org/DontBelieveMe/Stack)
A small stack based programming language written in C.

## Notes
- There are quite a few formatting issues, due to a tab v spaces problem with VS Code.
- Some of the code is quite bad. For example:
  - parse.c: This file contains quite a lot of code that it shouldn't.
    - The actual code is bad aswell: slow, verbose, inefficent. (oh and memory is not being managed properly.)
  - stacky.c: This doesn't check the amount of command arguments supplied. A small thing but oh well.
  - Some of the operations are parsed and performed at 'run-time'. This isn't good. (`jump` and `ifeq`)
- stack.c and stack.h on the other hand I think are quite good. But again, that might just be me.
- I don't know if this is cross platform compatible. (At the minuite it only works on windows). I should probably setup CI.

### Limitations
- There are also some quite serious limitations. 
  - Only integers can be pushed and handled by the stack.
  - Macros are cannot be changed (as they are swapped out at 'compile-time') and this means that they cannot be used as variables to  - store changing values. For example counters.
  
## Using Stack
Stack source files have the extension .stck.

Compile the source and then use the resultant `stack.exe` program to execute your code.

(Assuming that `stack.exe` is in your path or in the same folder) 
`stack <filename>.stck` will compile the stack file and output to standard output.

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
`push` takes one argument (`x`) and pushes `x` onto the top of the stack.
  - e.g `push 10` will push 10 on top of the stack.

`pop` takes no arguments and removes the top element from the stack.

`add` takes no arguments and will pop off and add together the two top elements on the stack and then push the result to the top of         the stack.

`sub` takes no arguments and will pop off and subtract the two top elements on the stack and then push the result to the top of the stack.

`mult` takes no arguments and will pop off and multiply the two top elements on the stack and push the result to the top of the stack.

`dup`  takes no arguments and duplicated the top element on the stack, pushing the duplicated element on top of the old one.

`print` takes no arguments and will print the top element on the stack.

`swap` takes no arguments and will swap over the first two elements on the stack.

`div` takes no arguments and will divide the top two elements on the stack and push the result onto the top of the stack.

`jump` takes one argument (`x`) and will jump to line number `x`

`ifeq` takes one argument (`x`). If the top element on the stack equals 0 then continue else jump to line `x`

`set`  takes two arguments (`n` and `v`) and will define a macro with a name of `n` and a value of `v`. 
  - e.g `set variable 7` will set a macro called `variable` to the value of `7`
  - `push variable` would then push 7 on top of the stack.

## TODO
- [ ] Labels for `jump` and `ifeq` - using line numbers is a pain
- [ ] Refactor the parse.c file to be better.
- [ ] Rename and change `file_t` to be `module_t`
- [ ] Changable variable
- [ ] Support for other data types
  - [ ] Double
  - [ ] String ([const?] char *)
  - [ ] Boolean (?
- [ ] Functions
- [ ] Continious integration
- [ ] Sort obj, exe, .c, .c and .stck files into different folders.
- [ ] Removed .vscode folder.
