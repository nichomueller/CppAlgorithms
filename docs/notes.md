### GENERAL NOTES ###

In this file, I'll gather some notes on C++ syntax that are non-standard and are useful for the development of a modular repo.

## Structure of the repo

For medium - large projects, the following structure is recommended:
* ``bin/``: contains the executables that are created when running make. This folder should be added to the .gitignore.
* ``docs/`` : documentation files are kept here.
* ``data/`` : data that can be read from file and used during numerical tests are kept here; this is also where outputs should potentially be written to file. This folder should be added to the .gitignore.
* ``libs/`` : where the external libraries (the .so files) are kept.
* ``build/``: temporary build files are generated while compiling and building the code, for example *.o files created by make. The files should be placed in this folder -- which should also be added to the .gitignore.
* ``tests/ ``: here the test files should be kept. It is recommended to keep one test file per module of the repo. These files can be run with the help of (CUnit)[https://cunit.sourceforge.net/].
* ``src/``: this is the most important folder, where the source code is placed. In a C++ repo, this should be populated by all the `.cpp` files written as part of the project. 
* ``include/``: where the header files -- usually one per `.cpp` file in the ``src/`` directory -- are located. Header files have a `.h` extension.

## Notes on C++

I found this link (here)[https://learn.microsoft.com/en-us/cpp/cpp/header-files-cpp?view=msvc-170] quite interesting. It's an example of header file, and there are quite a few things here that I saw which I didn't know about:
* A header file should start as follows:
```c++
#pragma once
#include <vector> 
#include <string>
// other includes...
```
The ``pragma once`` syntax is good practice, and it ensures that the header file is not loaded more than once across all files in the ``src/`` directory. It basically acts in lieu of the #ifndef block:
```c++
#ifndef MY_HEADER // include guard
#define MY_HEADER
```
* *Inline namespaces*: check (this)[https://www.foonathan.net/2018/11/inline-namespaces/] website for a comprehensive explanation. This is the syntax:
```c++
namespace A{
    inline namespace B{
        // stuff goes here
    }
    // more stuff goes here
}
```
The most important feature of an inlined namespace is that its members are directly accessible in its parent namespace. So it appears to not be a "proper" namespace after all. It is mainly used in the following situation. Suppose that you have a member class ``foo`` in namespace ``A`` 
```c++
namespace A{
    class foo{
        // stuff goes here
    }
}
```
which you substantially modify in later versions of your library. There might be users of your library who, for versioning reasons, are stuck with the old version of ``foo``. In this scenario, you might be interested in defining an inlined namespace:
```c++
namespace A{
    namespace v1{
        class foo{
            // deprecated stuff goes here
        }
    }

    inline namespace v2{
        class foo{
            // new stuff goes here
        }
    }
}
```
By default, users will have access to ``A::foo``, which is contained in ``A::v2``; however, users who wish to use the deprecated version can still use ``A::v1::foo`` instead.
* ``constexpr``: an expression that is executed at compile time, for example:
```c++
constexpr int a = 7;
```
That way the value of ``a`` is known prior to runtime. Also, a ``constexpr`` function can also be run at runtime when providing inputs with runtime values!
* ``static_assert``: an assert statement that is also executed at compile time, for example:
```c++
static_assert(a == 7, "unexpected!");
```
As any assertion, nothing happens if the condition is met; otherwise, the compilation fails and ``"unexpected!"`` is printed.
* *Type aliasing*: this is commonly done with the keyword ``using``, for example:
```c++
using vint = std::vector<int>; 
```
Now we can use ``vint`` instead of the longer ``std::vector<int>`` declaration! Aliasing also works for namespaces, and here ``using`` is no longer necessary:
```c++
namespace foo
{
    namespace bar
    {
         namespace baz
         {
             int qux = 42;
         }
    }
}
 
namespace fbz = foo::bar::baz;
```
* *Inline functions*: I must say the AI-generated response pretty much covers it all:
``
The inline keyword suggests that the compiler substitute the code within the function definition in place of each call to that function. In theory, using inline functions can make your program faster because they eliminate the overhead associated with function calls.
``
This is an example: 
```c++
inline void foo(){ 
    // body goes here
}
```