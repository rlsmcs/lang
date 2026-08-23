# Lang

A small programming language implemented from scratch in C, covering the pipeline from source code to tokens, to an abstract syntax tree, and eventually to program execution.

The project exists to study how a language works internally by implementing the lexer, parser, and interpreter by hand rather than relying on existing tooling.

## Status

Early stage. The frontend (lexer and parser) supports variable declarations, `print`, and basic binary expressions with operator precedence. Execution, control flow, and functions are not yet implemented. See the Roadmap section below for details.

## Pipeline

```text
Source Code
    |
  Lexer
    |
  Tokens
    |
  Parser
    |
   AST
    |
Interpreter / Compiler
    |
  Output
```

The lexer and parser form the frontend of the language. The AST is kept independent of execution so it can later be consumed by an interpreter, a bytecode VM, a compiler, or a transpiler.

## Current Syntax

### Variables

```lang
let x = 14;
```

### Print

```lang
print(x);
```

### Expressions

```lang
5 + 3
5 - 3
5 * 3
5 / 3
```

Variables can also be used in expressions:

```lang
let x = 10;
x + 5;
x * 2;
```

### Operator Precedence

Multiplication and division bind tighter than addition and subtraction:

```lang
5 + 3 * 2;
```

is parsed as:

```text
      +
     / \
    5   *
       / \
      3   2
```

The parser uses recursive descent:

```text
parse()
    |
parseExpression()   -> + -
    |
parseTerm()          -> * /
    |
parsePrimary()        -> numbers, variables, (...)
```

## Architecture

### Lexer

Converts raw source code into a stream of tokens.

For example:

```lang
let x = 14;
```

becomes roughly:

```text
LET
IDENTIFIER
EQUALS
NUMBER
SEMICOLON
```

### Parser

Consumes the token stream and builds an abstract syntax tree.

Currently supported:

- Number literals
- Variables
- Variable declarations
- `print`
- Binary expressions
- Operator precedence

### AST

The AST represents the structure of the program.

For:

```lang
5 + 3 * 2
```

the AST is:

```text
Binary(+)
|-- Number(5)
`-- Binary(*)
    |-- Number(3)
    `-- Number(2)
```

## Project Structure

```text
lang/
|-- include/
|   |-- ast.h
|   |-- interpreter.h
|   |-- lexer.h
|   |-- parser.h
|   |-- token.h
|   `-- vector.h
|
|-- src/
|   |-- ast.c
|   |-- interpreter.c
|   |-- lexer.c
|   |-- main.c
|   |-- parser.c
|   `-- vector.c
|
|-- examples/
|   `-- test.lang
|
|-- Makefile
`-- README.md
```

## Build

Build the project:

```bash
make
```

Run:

```bash
make run
```

Clean build artifacts:

```bash
make clean
```

## Roadmap

Completed:

- Lexer
- Token system
- Dynamic vector
- AST structure
- Number parsing
- Variable parsing
- Variable declarations
- `print`
- Binary operators
- Operator precedence

Working on:

- Parentheses
- Unary operators
- Multiple statements and complete programs
- Runtime environment
- Interpreter
- Conditions and loops
- Functions
- Arrays and data structures
- Pointers and references
- Bytecode VM or compiler backend

## Long-Term Goals

The near-term goal is to turn the current frontend into a working tree-walking interpreter, then extend it into a compiled pipeline that reuses the same frontend:

```text
Source
  |
Lexer
  |
Parser
  |
AST
  |-- Interpreter
  |-- Bytecode VM
  |-- Compiler
  `-- Transpiler
```

Longer term, the language is intended to draw design influence from Zig, Go, and Rust: manual memory management, static explicit typing, and explicit error returns in the style of Zig and Go, while keeping C's minimal syntax and leaning toward a functional style. None of this is implemented yet; the current build only supports variables, `print`, and basic binary expressions.

The language and its implementation are under active development.
