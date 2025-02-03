# Code documentation

This document provides a series of templates and examples to document the [structures](#structures), [functions](#functions), and [macros](#macros) of the application.

The documentation must follow these rules:

-   It must be written in English.
-   It should be done in files with a `.h` extension.

> [!TIP]
> If you use [Visual Studio Code](https://code.visualstudio.com/), you can use the pre-made Snippets.

## Structures

### Template

```c
/**
 * @struct <STRUCTURE NAME>.
 * @brief <BRIEF DESCRIPTION OF WHAT THE STRUCTURE REPRESENTS>.
 *
 * <DETAILED DESCRIPTION OF THE STRUCTURE (PURPOSE, AND LISTS OF FIELDS)>.
 */
typedef struct {
    DataType01 member01; /** <BRIEF DESCRIPTION OF THE MEMBER>. */

    // ...
} MyStruct;
```

_For example..._

```c
/**
 * @struct Point2D
 * @brief Represents a point in 2D space.
 *
 * The Point struct is used to represent a coordinate in a
 * two-dimensional Cartesian plane. It contains two members
 * representing the x and y coordinates.
 */
typedef struct {
    int x; /**  The x-coordinate of the point. */
    int y; /** The y-coordinate of the point. */
} Point2D;
```

## Functions

### Template

```c
/**
 * @brief <BRIEF DESCRIPTION OF THE FUNCTION>.
 *
 * <DETAILED DESCRIPTION OF THE FUNCTION (WHAT IT DOES, HOW IT WORKS, AND ANY IMPORTANT INFORMATION)>.
 *
 * @param param01 <BRIEF DESCRIPTION OF `param01` PARAMETER>.
 *
 * @return <BRIEF DESCRIPTION OF THE FUNCTION'S RETURN VALUE>.
 *
 * @warning <RELEVANT INFORMATION ABOUT SIDE EFFECTS OR IMPORTANT CONSIDERATIONS (OPTIONAL)>.
 */
ReturnDataType myFn(DataType01 param01);
```

> `@return` can be omitted if the function returns `void`.

_For example..._

```c
/**
 * @brief Calculates the factorial of a number.
 *
 * This function computes the factorial of a non-negative integer
 * using an iterative approach. It handles the base case of 0! as 1.
 *
 * @param n The integer whose factorial is to be calculated.
 *          Must be non-negative.
 *
 * @return The factorial of the given number. If the input is
 *         negative, returns -1 as an error code.
 *
 * @warning The function does not handle large values of n well due to
 *          potential integer overflow.
 */
int factorial(int n) {
    int i = 1;
    int result = 1;

    if (n < 0) return -1;

    for (i = 2; i <= n; i++) {
        result *= i;
    };

    return result;
}
```

## Macros

### Template

```c
/**
 * @def <MACRO NAME>
 * @brief <BRIEF DESCRIPTION OF WHAT THE MACRO DOES>.
 *
 * <DETAILED DESCRIPTION OF THE MACRO (OPTIONAL)>.
 *
 * @warning <WARNINGS ABOUT THE USE OF THE MACRO>.
 */
#define MY_MACRO value
```

_For example..._

```c
/**
 * @def PI
 * @brief The value of Pi to 5 decimal places.
 *
 * @warning This value may not be precise enough for some applications
 *          requiring high accuracy in mathematical computations.
 */
#define PI 3.14159
```
