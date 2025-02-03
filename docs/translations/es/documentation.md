# Documentación de código

Este documento otorga una serie de plantillas y ejemplos para documentar las [estructuras](#estructuras), [funciones](#funciones) y [macros](#macros) de la aplicación.

Las documentaciones que se realicen deben seguir las siguientes reglas:

-   Ser escritas en inglés.
-   Realizarse sobre archivos con extensión `.h`.

> [!TIP]
> Si utilizas [Visual Studio Code](https://code.visualstudio.com/) puedes utilizar los Snippets ya creados.

## Estructuras

### Plantilla

```c
/**
 * @struct <NOMBRE DE LA ESTRUCTURA>.
 * @brief <BREVE DESCRIPCIÓN DE LO QUE REPRESENTA LA ESTRUCTURA>.
 *
 * <DESCRIPCIÓN DETALLADA DE LA ESTRUCTURA (PROPÓSITO Y LISTADO DE CAMPOS)>.
 */
typedef struct {
    DataType01 member01; /** <BREVE DESCRIPCIÓN DEL MIEMBRO>. */

    // ...
} MyStruct;
```

_Por ejemplo..._

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
    int x; /** The x-coordinate of the point. */
    int y; /** The y-coordinate of the point. */
} Point2D;
```

## Funciones

### Plantilla

```c
/**
 * @brief <BREVE DESCRIPCIÓN DE LA FUNCIÓN>.
 *
 * <DESCRIPCIÓN DETALLADA DE LA FUNCIÓN (QUÉ HACE, CÓMO FUNCIONA Y CUALQUIER INFORMACIÓN IMPORTANTE)>.
 *
 * @param param01 <BREVE DESCRIPCIÓN DEL PARÁMETRO `param01`>.
 *
 * @return <BREVE DESCRIPCIÓN DEL VALOR DE RETORNO DE LA FUNCIÓN>.
 *
 * @warning <INFORMACIÓN RELEVANTE SOBRE EFECTOS SECUNDARIOS O CONSIDERACIONES IMPORTANTES (OPCIONAL)>.
 */
ReturnDataType myFn(DataType01 param01);
```

> `@return` puede omitirse si la función retorna `void`.

_Por ejemplo..._

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

### Plantilla

```c
/**
 * @def <NOMBRE DE LA MACRO>
 * @brief <BREVE DESCRIPCIÓN DE LO QUE HACE LA MACRO>.
 *
 * <DESCRIPCIÓN DETALLADA DE LA MACRO (OPCIONAL)>.
 *
 * @warning <ADVERTENCIAS SOBRE EL USO DE LA MACRO>.
 */
#define MY_MACRO value
```

_Por ejemplo..._

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
