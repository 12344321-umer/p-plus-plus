# P++ Programming Language

P++ is a custom programming language I built from scratch where all the keywords are written in desi slang (Urdu/English mix). Instead of writing `if` you write `lowkey`, instead of `while` you write `chalBro`, and instead of `print` you write `spillTea`. It is a fully working language with a real compiler pipeline behind it, not just a gimmick.

The goal of this project was to learn how programming languages actually work under the hood — how code goes from plain text to a structured tree that a computer can understand and validate.

---

## What Does It Actually Do

When you write P++ code and hit run, here is what happens behind the scenes:

1. The **lexer** reads your code character by character and breaks it into tokens (keywords, numbers, variable names, operators etc.)
2. The **parser** takes those tokens and checks if they follow the grammar rules of P++, then builds an **Abstract Syntax Tree (AST)** which is a tree representation of your program
3. The **semantic analyzer** walks the AST and checks for logical errors like using a variable before declaring it
4. All of this gets sent as JSON to a React frontend that displays the AST visually and shows you a symbol table of all your variables

---

## The Language Syntax

Every P++ program starts with `sceneOnHa` and ends with `sceneOffHa`.

Here is a quick reference of all the keywords:

| What it means | P++ keyword |
|---|---|
| Program start | `sceneOnHa` |
| Program end | `sceneOffHa` |
| Declare integer | `numYesKarao` |
| Declare float | `floatYesKarao` |
| Assign a value | `<-` |
| Print something | `spillTea` |
| If | `lowkey` |
| Else | `warnaBro` |
| Else if | `phirBro` |
| While loop | `chalBro` |
| Break | `ghosted` |
| Continue | `missKara` |
| Return | `wapas` |
| True | `noCap` |
| False | `cap` |
| Addition | `^+` |
| Equals | `==?` |
| Block start | `basYar` |
| End of statement | `!!` |

---

## Code Examples

**Hello World**
```
sceneOnHa
    spillTea "Salam Duniya!" !!
    wapas 0 !!
sceneOffHa
```

**Variables and Math**
```
sceneOnHa
    numYesKarao x <- 10 !!
    numYesKarao y <- 5 !!
    numYesKarao result <- x ^+ y !!
    spillTea result !!
    wapas 0 !!
sceneOffHa
```

**If Else**
```
sceneOnHa
    numYesKarao score <- 8 !!
    lowkey (score > 5)
    basYar
        spillTea "noCap passing" !!
    warnaBro
    basYar
        spillTea "cap failing" !!
    wapas 0 !!
sceneOffHa
```

**While Loop**
```
sceneOnHa
    numYesKarao counter <- 0 !!
    numYesKarao limit <- 5 !!
    chalBro (counter < limit)
    basYar
        spillTea "looping..." !!
        counter <- counter ^+ 1 !!
    wapas 0 !!
sceneOffHa
```

---

## Project Structure

```
p-plus-plus/
├── compiler/         The actual compiler written in C
│   ├── scanner.l     Flex lexer — tokenizes your code
│   ├── parser.y      Bison parser — builds the AST
│   ├── ast.c / ast.h         AST node definitions and constructors
│   ├── semantic.c / semantic.h   Semantic analysis and symbol table
│   ├── main.c        Entry point — runs the full pipeline
│   └── p-plus-plus.exe   Pre-built Windows executable
│
├── server/           Node.js + Express backend
│   ├── index.js      API server on port 3001
│   └── compile.js    Calls the compiler exe and returns JSON
│
└── web/              React frontend
    └── src/
        ├── App.jsx
        ├── components/
        │   ├── Editor.jsx    Code editor with sample programs
        │   └── Output.jsx    AST viewer and symbol table
        └── api/
            └── compilerApi.js    Talks to the backend
```

---

## How to Run It

You need Node.js installed. The compiler executable is already built and included so you do not need to install anything for the C side.

**Step 1 — Start the backend server**

Open a terminal and run:
```
cd server
node index.js
```

You should see: `P++ server running at http://localhost:3001`

**Step 2 — Start the frontend**

Open a second terminal and run:
```
cd web
npm install
npm run dev
```

Then open your browser and go to `http://localhost:5173`

**Step 3 — Write some code and hit Run**

Type your P++ code in the editor or pick one of the sample programs, click the Run button, and you will see the AST and symbol table appear on the right side.

---

## How the Compiler Was Built

The compiler is written in C using two classic tools:

**Flex** is a lexer generator. You write rules that describe what your tokens look like (numbers, keywords, identifiers etc.) and Flex generates C code that can scan through your source file and produce a stream of tokens.

**Bison** is a parser generator. You write a grammar that describes the structure of your language and Bison generates C code that can take a token stream and build an AST from it.

After parsing, a hand-written semantic analysis pass walks the tree and checks things like whether a variable was declared before it was used.

The final output is a JSON object containing the AST and symbol table, which gets sent to the frontend.

---

## Things You Can Try

- Write a program with an undeclared variable and see the semantic error get caught
- Write a syntax error (like missing `!!` at the end of a line) and see the parse error
- Look at the AST panel to understand how your code is represented as a tree
- Check the symbol table to see all the variables your program declared and what types they are

---

## Why I Built This

I built P++ to properly understand what happens when you write code in any language. Most people use Python or JavaScript without ever thinking about how the computer figures out what `if` means or how it knows that `x = 5` assigns a value. Building this from scratch made all of that click for me.
