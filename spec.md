# Wanted Features
- Polymorphism including return types
- Reflections
- Delegations
- Packages
- OOP
    - Constructor
    - Destructor
    - Variadic Generics

# Primitives
Primitivity should be abstracted away

## Boolean
It's a Boolean.

## Numbers

### Integer
- I8 aka Byte (8)
- I16 aka Short (16)
- I32 aka Int (32)
- I64 aka Long (64)
- U8 aka UByte (8)
- U16 aka UShort (16)
- U32 aka UInt (32)
- U64 aka ULong (64)

### Decimal
- F32 aka Float (32)
- F64 aka Double (64)
- P32 aka Fixed (32, Fixed point number)
- P64 aka DFixed (64, Fixed point number)

# Spec-Syntax
This explains the syntax used for explaining the code syntax.
```
[] means optional
[]... means that optional part can have 0 ore more occurences
<> is a reference to a pattern
\< is an escaped <
\> is an escaped >
\[ is an escaped [
\] is an escaped ]
// starts a comment on that line
/* starts a comment
*/ ends a comment
```

## Identifier
`<id>`

Restricted by following regex.
```
[a-zA-Z_][a-zA-Z0-9_]*
// or
`[a-zA-Z0-9_ ]+` // only for variables and infix functions
```

## Expression
An expression always "returns" something.
An expression is also a statement.
An expression can be encased by parenthesis.
```
<expr>
// or
<expr: Type>
// for specifying return type
```

### String
```
"whatever string
 multiline by default
 including unicode\u0073"

sql"SELECT codeHighlighting FROM `ide`;" // regex for prefix [a-zA-Z0-9_]+

@"file.txt" // reads string from file at compile time
```

### Number
```
1234              // Integer
1234.5678         // Decimal
1_000_000_000     // Cleaner with underscores
0001_123___4      // Valid but why?
0b0101001         // Binary
0b010100__01.1010 // Binary with underscores or point number
0x789AbcD         // Hexadecimal
0x789AbcD.__23F   // Hexadecimal
1e4               // 1e10 = 1*10^4 = 10000 = 10_000

// On base 2 and base 10 append case insencitive b (Byte) s (Short) l (Long) ub (Unsigned Byte) us (Unsigned Short) ul (Unsigned Long) f (Float) d (Double) fix (Fixed) dfix (DFixed)
```

### Array
```
\[[<expr>[,<expr>]...]\]
```

### Map
```
{
    [<expr>:<expr>[,<expr>:<expr>]...]
}
```

### Variable
```
nameOfTheVariable
`idk why but you can go crazy with this variable names`
```

### Function
```
<expr: Function>([<expr>[,<expr>]...]) [<lambda>]
```

### Field
```
<expr>.<id>
```

### If
```
if (<expr: Boolean>) <e-body>

if (<expr: Boolean>) <e-body> else <e-body>
```

### Switch
```
switch (<expr>) {
    [<expr> -> <e-body>]...
    _ -> <e-body>
}

switch {
    [<expr: Boolean> -> <e-body>]...
    _ -> <body>
}

// special case (the first <expr> is moved to {})
switch (<expr>) {
    [{} <operator: Boolean> <expr> -> <e-body>]...
    [{} <infix: Boolean> <expr> -> <e-body>]...
    _ -> <e-body>
}
```

### Ternary
```
<expr: Boolean> ? <expr> : <expr>
```

## Statement
A Statement is a piece of code that does something.
Statements are separated by `;` or `\n`.

`<stmt>`

### Variable Declaration
```
var <id>[:<type>] = <expr> // mutable

val <id>[:<type>] = <expr> // immutable

var (<id>[:<type>][<id>[:<type>]]...) = <expr> // mutable

val (<id>[:<type>][<id>[:<type>]]...) = <expr> // immutable

var <id>[:<type>] by <expr: Type> // Use of delegation returning mutable value

val <id>[:<type>] by <expr: Type> // Use of delegation returning immutable value
```

### Switch
```
switch (<expr>) {
    [case:
        [<stmt>]...
        [break;]
    ]...
    [default:
        [<stmt>]...
        [break;]
    ]
}
```

### Loops

#### For
A for loop is usually covered by lambda except counter loops
```
for (<id>[:<type>]; <expr: Boolean>; <expr>) <scope>
```

#### While
```
[do] while [(<expr: Boolean>)] <scope>

do <scope> while (<expr: Boolean>)
```

## Scope
Scope is generally
```
{
    // whatever
}
```
where each scope has some things that can be used inside of it.
A Scope can be an expression.
Below are some patterns used across the spec.

```
<body> = <scope> /* or */ <stmt>
<e-body> = <e-scope> /* or */ <expr>
<e-body: Type> = <e-scope: Type> /* or */ <expr: Type>
```
```
<scope>

{
    [<stmt>]...
}

<e-scope>
{
    [<stmt>]...
    <expr>
}

<e-scope: Type>
{
    [<stmt>]...
    <expr: Type>
}
```

### Lambda
`<lambda>`
```
{ [<id>[=<expr>][,<id>[=<expr>]]... ->] // when omitting it uses 1 param with the name `it` or none
    [return[@<id /* of scope (can be a class or function)*/>] [<expr>]]...
    [<stmt>]...
    [<expr>] // when it returns something
}
```

## Type
`<type>` or `<type !u>` for excluding Unions

### Class
Just a class name either by import, it being local or fully qualified names.
```
<class> // by regex [a-zA-Z_][a-zA-Z0-9_.]*[a-zA-Z_]

<class>[<generics>]
```

### Union
`<type !u>[|<type !u>]...`

### Function-Type
```
([<type>[,<type>]...])-><type> // for normal lambda

<type>.([<type>[,<type>]...])-><type> // for extension function lambda
```

## Generics
`<generics>`

```
\<<type>[:<type>],[<type>[:<type>]]...\>
```

## Declaration

### Function
`<func-decl>`
```
[private /* or */ internal /* or */ protected /* or */ public] [[final] override /* or */ abstract /* or */ open] [<generics>] fun <id>([[<id>:<type>[=<expr>]]]...) [: <type>] [{
    [<stmt>]...
    [return [<expr>]]
}]

[private /* or */ internal /* or */ protected /* or */ public] [[final] override /* or */ abstract /* or */ open] [<generics>] fun <id>([[<id>:<type>[=<expr>]]]...) [: <type>] = <stmt>
```

### Field
`<field-decl>`
```
var <id>[:Type] = <expr> // mutable
[get() <scope>] /* or */ [get() = <expr: Type>]
[set(<id>) <scope>] /* or */ [set(<id>) = <expr: Type>]

val <id>[:Type] = <expr> // immutable
[get() <scope>] /* or */ [get() = <expr: Type>]

var (<id>[:<type>][<id>[:<type>]]...) = <expr> // mutable

val (<id>[:<type>][<id>[:<type>]]...) = <expr> // immutable

var <id>[:Type] by <expr: Type> // Use of delegation returning mutable value
[get() <scope>] /* or */ [get() = <expr: Type>]         // Proxy for getter
[set(<id>) <scope>] /* or */ [set(<id>) = <expr: Type>] // Proxy for setter

val <id>[:Type] by <expr: Type> // Use of delegation returning immutable value
[get() <scope>] /* or */ [get() = <expr: Type>] // Proxy for getter
```

### Classes

#### Class
```
[private /* or */ internal] [open /* or */ abstract /* or */ sealed] class <id>[([[<id>:<type>[=<expr>]]]...)] [: <type>[,<type>]...] {
    [singleton {
        [<field-decl>]...
        [<func-decl>]...
        [init <scope>]
    }]
    [constructor([[<id>:<type>[=<expr>]]]...) : this([<expr>]...) [<scope>]]...
    [<field-decl>]...
    [<func-decl>]...
    [init <scope>]
}
```

#### Interface
```
[private /* or */ internal] [open /* or */ abstract /* or */ sealed] interface <id> [:<type>[,<type>]...] {
    [<field-decl>]...
    [<func-decl>]... // allowed without scope
}
```

#### Enum
```
[private /* or */ internal] enum <id>[([[<id>:<type>[=<expr>]]]...)] [: <type>[,<type>]...] {
    [<id>[([<expr>[,<expr>]...])]][,[<id>[([<expr>[,<expr>]...])]]]...
    [;
    [<field-decl>]...
    [<func-decl>]...
    [init <scope>]]
}
```

#### Singleton
```
[private /* or */ internal] [open /* or */ sealed] singleton <id> [: <type>[,<type>]...] {
    [<field-decl>]...
    [<func-decl>]...
    [init <scope>]
}
```

#### Annotation
```
annotation <id>[([<id>:<type>[,<id>:<type>]...])]

// Usage
@<id>([<expr>[,<expr>]...])
```
