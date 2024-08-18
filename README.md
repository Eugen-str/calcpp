# calcpp

Calculator in C++.

Basically copies the AST from [Crafting Interpreters](https://craftinginterpreters.com) but for just a calculator.

Running it with no arguments starts a REPL, problem with the REPL is that there is no easy way of implementing arrow key movement cross-platform, so the best way to use the program is by providing the string to calculate as an argument.

---

examples:

REPL:
```console
$ make
$ ./calcpp
; 1 + 2
3
; quit
```

instant calculation:
```console
$ ./calcpp "4 * (7 + (3 * 2))"
52
```

