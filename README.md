# C Sugar
## What is this?
C Sugar is a conversion from an abbreviated of C++ code to C++ code. You can use this if you are doing simple functions or classes and want to write C++ code just that much faster. This will also be useful if you are trying to write tech questions and dont want to be bogged down by having to make loops to print vectors, using cout, ect ect. C Sugar will also help you comment your c++ code and will insert @TODO for comments you need to fill out.

## How to use:
To use C sugar:
1.	Clone the repo
2.	cd into the directory
3.	`make`
4.	Run your file through ./run,  i.e `./run path/to/file`
5.	Watch your code get converted to a .cpp file!

I encourage you to try it out and play with it. If you find any bugs (there are a ton) please make an issue and I will get to it ASAP. 

## Reference 
### var
Var will be used instead of types. Var will try to deduce the type that is on the rhs, or just set it to auto if it doesn’t know. 

Int:
`var x = 5;`

String:
`var y = "I am a string"`

Vector:
`var z = std::vector<int>();`

Bool:
`var a = true`

### includes
I made a `#inc e` that will give you a bunch of useful libraries so you dont have 
import random things like vectors or strings. 

### header
In your config.txt file, you can customize certain settings. For example, the header. If you place `@header` at the top of your file, it will put your name, the date, and the version number.

### print();
print() is a direct implantation of std::cout. Code like Print(“Hello”); will be translated to std::cout << “Hello”;

Prints hello world:
`print("Hello world);`

Print var 5:
```
var x = 5; 
print(x);
```

Print more things:
```
var x = 5;
print("I am X " + x + " this is my value");
```

### println();
Just like print(), but prints a newline after. 

### printv();
printv() helps you print out a vector with a delim. 

print a vector with no delim:
`printv(vec);`

print a vector with a comma:
`printv(vec, ",");`

print a vector with a '-':
`printv(vec, "-");`

### vector
This helps create vectors quicker.

create an int vector:
`var vec = vector int;`

create a string vector:
`var vec = vector std::string;`

create a bool vector:
`var vec = vector bool;`

### push();
This helps you push things into your vectors.

push one thing:
`vec.pushv(3);`

push 4 things:
`vec.pushv(3,4,5,6);`

## Help!
If you are able to read through my code, I would love some tips. I am also looking for people to contribute, so please let me know!