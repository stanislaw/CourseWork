# C++ for C programmers. Part A.

## Lesson 1: C++ as a better C

B.Stroustrup: 

> More to the point, I don't think "purity" is a virtue. The signal strength of C++ is exactly that it supports several effective styles of programming (several paradigms, if you must), and combinations of these styles. Often, the most elegant, most efficient, and the most maintainable solution involves more than one style (paradigm). If you must use fancy words, C++ is a multi-paradigm programming language. Given the wide variety of demands in the huge area of software development, there is a need for at least one general-purpose language supporting a range of programming and design styles, and probably for more than one such language. Also, there is room for many programming languages in the world. The idea that a single language is best for every application and every programmer is absurd. 

- More type safe (more caught by compiler)
- More libraries (reuse)
- Less reliance on preprOcessor: no longer a good practice as it does not obey language rules but just textual processing
- OO vs imperative


- include -> .h may be omitted
- C imports become c-prefixed: `<cstdio>`
- Use of preprocessor is discouraged
  - Use of `inline`
  - Use of `const`

- Namespaces: `using namespace std` (namespace encapsulation). `::` is called "scope resolution operator".
- iostream: `cout/cin` instead of `printf/scanf`
- `<<` operator with typesafety, based on overloading feature
- Memory management: `new/delete` instead of `malloc/free`. `new/delete` are compiler keywords, allow for more typesafety.
- Safe casts (`static_cast<type>`)
- force casting is discouraged
- Declarations anywhere
  - `for` statement can include declaration initializer: `for (int i = 0;`

### Call by value vs call by reference

C only has call by reference simulated with pointers (indirection).
C++ has call by reference argument passing

### C++ Overloading

Involves discriminating by signature which is the types and number of arguments that function uses ("Signature matching algorithm").

### Generics in C++

"Generic"

a) relating to or characteristic of a whole group or class: general
b) being or having a nonproprietary name <generic drugs>
c) having no particular distinction

In C++ "Generic programming" is programming using templates.

Influenced by Alex Stepanov.

Much code is the same except for type. If the code can be applied universally there can be a big saving in coding and debugging.

Compile generics to instances:

> - Compiler uses the template to write code appropriate to each set of parameters
> - The m,n parameters are ints - so the compiled code is swap(int &, int &) signature.
> - Similarly for the other two signatures. So the compiler is compiling code appropriate to each distinct signature.

Specialized functions take precendence over template-defined functions.







