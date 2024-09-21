- [Reference](#reference)
  - [Calclations](#calclations)
  - [Variables](#variables)
  - [Functions](#functions)
  - [Classes](#classes)
  - [Statements](#statements)

# Reference

## Calclations

Each operator works as shown in the table below.

| Precedence | Operator | Format | Expression Value |
| :-: | :-: | :- | :- |
| 1 | ref | 1. ref *V*<br>2. ref *T* | 1. The value referenced by a reference type variable *V*<br>2. Reference type *T* |
| 1 | add | add *V* | The address of the variable's value |
| 2 | . | *a*.*b* | Member *b* of class *a* |
| 3 | + | +*a* | *a* |
| 3 | - | -*a* | -*a* |
| 4 | \*\* | *a* \*\* *b* | a to the power of b |
| 5 | * | *a* \* *b* | *a* times *b* |
| 5 | / | *a* / *b* | *a* divide *b* |
| 5 | % | *a* % *b* | Remainder when dividing *a* by *b* |
| 6 | + | *a* + *b* | *a* plus *b* |
| 6 | - | *a* - *b* | *a* minus *b* |
| 7 | == | *a* == *b* | 1 if *a* is equal to *b*, 0 otherwise |
| 7 | != | *a* != *b* | 1 if *a* is not equal to *b*, 0 otherwise |
| 7 | > | *a* > *b* | 1 if *a* > *b*, otherwise 0 |
| 7 | < | *a* < *b* | 1 if *a* < *b*, otherwise 0 |
| 7 | >= | *a* >= *b* | 1 if *a* > *b* or *a* and *b* are equal, 0 otherwise |
| 7 | <= | *a* <= *b* | 1 if *a* < *b* or *a* and *b* are equal, 0 otherwise |
| 8 | and | *a* and *b* | 1 if *a* and *b* are both 1, 0 otherwise |
| 8 | or | *a* or *b* | 1 if either *a* or *b* is 1, 0 otherwise |
| 9 | = | *a* = *b* | Assign *b* to *a* |

## Variables

To define a variable, use the let statement:
```
let VARIABLE : VARIABLE_T => VALUE
```
For example:
```
let a : float = 3.5
```
You can define constants using the const statement instead of the let statement.
```
const CONSTANT_NAME : TYPE_NAME => VALUE
```

## Functions

To define a function, use the let statement:
```
func FUNCTION(ARG1 : ARG_T1, ARG2 : ARG_t2, ...) : RETURN_T =>
    (expressions or statements)...
end
```

For example:
```
func f(a : int, b : int) : int =>
    let c : int = a + b
    return c * a
end
```

To call a function:
```
FUNCTION(ARG1, ARG2, ...)
```

## Classes

To define a class, use the class statement:
```
class CLASS    (If you want to inherit, ": INHERITED_CLASS") =>
    (public/private/protected) (Define function or variable)
    ...
end
```

You can define structures by using the struct statement instead of the class statement.
```
struct STRUCT    (If you want to inherit, ": INHERITED_STRUCT") =>
    (public/private/protected) (Define function or variable)
    ...
end
```

Constructors and destructors can be defined by using the con and des statements instead of the func and let statements.
They do not require you to specify a return type.

For example:
```
class Dog =>
    public let name : string => ""
    
    public con Dog(name : string) =>
        ref this.name = name
    end

    public func GetAge() : int =>
        return 0
    end
end
```

You can define an interface by changing the class statement to an interface statement.
Also, to define a pure virtual member function (constructor, destructor), do not write "=>" in the func(con, des) statement, and just write "end" without writing any processing content.
```
func VIRTUAL_FUNCTION(ARG1 : ARG_T1, ARG2 : ARG_T2) : RETURN_T end
```

For example:
```
interface Animal =>
    public func Cry() : void end
    public func GetKind() : int end
    public des Animal() end
end

class Cat : Animal =>
    public con Animal() =>
        neitive =>
            "cout << $mew(hello)$ << endl;"
        end
    end

    public func Cry() : void =>
        neitive =>
            "cout << $mew$ << endl;"
        end
    end

    public func GetKind() : int =>
        return 001
    end

    public des Cat() =>
        neitive =>
            "cout << $mew(bye)$ << endl;"
        end
    end
end
```

## Statements

|Statement|Format|Example|
|:--:|:---|:---|
|if|if(*expression*) => *statements*... end|if(a == 3) => a = 10 end|
|elif|elif(*expression*) => *statements*... end|if(a == 0) => a = 10 end<br>elif(a == 1) => a = 20 end|
|else|else => *statements*... end|(if statement and some elif statement)<br>else => a = 50 end|
|for|for(*expression1(let statement)*, *expression2*, *expression3*) => *statements*... end|for(let i : int => 0, i < 30, i = i + 1) => a = i end|
|while|while(*expression*) => *statements*... end|while(i < 20) => i = i + 1 end|
|break|break|while(*expression*) => *statements* ... break *statements* ...  end|
|continue|continue|while(*expression*) => *statements* ... continue *statements* ...  end|
|return|return *expression*|return 1 + 2|
|include|include *include_file* {": F" or ": H"}|include iostream|
|neitive|neitive => "*statements of C++*" end|neitive => "using namespace std;" end|

If you do not add anything after the file name in the include statement, it will be recognized as a standard library, if you add ": F" it will be recognized as a focus file, and if you add ": H" it will be recognized as a header file.

For example:
```
include TestHeader : H
```
```
include TestFocas : F
```
