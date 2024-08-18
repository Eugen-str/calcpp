SRCS=src/main.cpp src/scanner.cpp src/parser.cpp src/interpreter.cpp

calc:
	clang++ -o calcpp $(SRCS)
