# Resultados TP 0 🖥️✨

_Alumno:_ [Facundo Ferraris [FAI-3810]](https://github.com/Facundo-Sebastian-Ferraris/SistemasOperativosI)

## 0. Hola Mundo

Dado el codigo ([helloWorld.c](./00-HelloWorld.c)) la salida resultante es:

```bash
    HOLA MUNDO! 🌱✨
```

## 1. Tipos de datos

- Los tipos de datos basicos utilizados son

```c
int     a = 2       // Es un numero entero con signo
float   b = 2.5     // Un entero largo
double  c = 2.12321 // Un numero en punto flotante
char    e = 'e';    // Un elemento del tamaño de un byte
```

- A su vez se encuentran modificadores que permiten agregar/restringir criterios para cada tipo: 🔧
  - **`short`**: Reduce el tamaño del tipo base, generalmente usado con `int`.  
  - **`long`**: Aumenta el tamaño del tipo base, aplicable a `int` o `double`.  
  - **`unsigned`**: Elimina el signo, usando todos los bits para valores positivos.
  - **`signed`**: Especifica que el tipo incluye valores negativos (predeterminado en la mayoría de los casos).  

- **Observaciones:**
  - Cuando se invoca los modificadores short y long, se asumen por default como int

## 2. "word" en Arquitectura de Computadoras 🖥️

Una **"word"** es la **unidad de datos básica** que el procesador puede manejar de manera eficiente en una sola operación.
Es el tamaño estándar de los registros del procesador y determina cuántos bits puede procesar o transferir simultáneamente.

El tamaño de una "word" varía según la arquitectura:

- **8 bits**, una word suele ser **1 byte** (8 bits).  
- **32 bits**,  una word es típicamente **4 bytes** (32 bits).  
- **64 bits**,  una word es generalmente **8 bytes** (64 bits).

## 3. Bits en una variable `int` en C 🔢

  Los bits que ocupará una variable `int` dependerá del compilador y de la arquitectura de la computadora

- **Arquitectura de 8 bits** ⚙️  
  Suele ser **16 bits** (2 bytes), ya que el estándar de C requiere que un `int` tenga al menos 16 bits.
  Aunque la `word` del procesador sea 8 bits, el compilador ajusta el `int` para cumplir con esta regla mínima.

- **Arquitectura de 32 bits** 💾  
  Ocupa **32 bits** (4 bytes), coincidiendo con el tamaño de la `word` del procesador.
  Es el tamaño más común en sistemas de 32 bits.

- **Arquitectura de 64 bits** 🖥️  
  Ocupa nuevamente **32 bits** (4 bytes) a pesar de que la word sea de 64 bits.
  Aunque, en algunos sistemas o compiladores podrían definir un `int` de 64 bits (8 bytes) aumentando mucho mas su rango.

- **Nuestra PC**
Para averiguar la cantidad de bits que ocupa un entero en mi computadora (de 64bits), se implementa el siguiente codigo:

Dado el codigo en el enlace ([ver codigo](./03-SizeInt.c)) con salida por pantalla:

```bash
"PC con arquitectura de 64 bits 🖥️ "
        Bits en un int: 32 ✨

 Se utilizo %zu que es un especificador de formato para poder 
 leer el tipo de dato size_t.
(esto es porque el metodo sizeOf() retorna ese mismo tipo)
```

Entonces podemos concluir que en nuestra PC, el int ocupa 32 bits

## 4. Diferencia en la salida con `printf()` ✏️

Dado el codigo en el enlace ([ver codigo](./04-Diferencias.c)) con salida:

- **Salida**

```bash
a = 77 
La letra M
```

La diferencia radica en los especiicadores de formato que se estan utilizando:

| Especificador de Formato  | Funcionalidad |
|:-:                        |:-             |
| **%i**                    | i de entero, por lo que interpreta el valor entero de `a` |
| **%c**                    | c de caracter, interpreta el caracter ascii de `a` |

## 5. Rango de char y unsigned char

```c
   char i;
   unsigned char j;
```

En los archivos del lenguaje existe una libreria llamada `<limits.h>`, donde se sentan los valores minimos y maximos de cada tipo de dato.
Por lo tanto importando esta libreria a un codigo, e imprimos las constantes, podremos saber dichos rangos.

El codigo en cuestion se encuentra en el enlace [ver aqui](05-RangosNumericos.c), y la salida por pantalla es:

```bash
Utilizado libreria "<limits.h>" 📚, donde se guardan las constantes de dichos rangos 📐 

Rango de char 🅰️:                 -128   a 127
Rango de signed char ✔️ ➖ ➕:    -128   a 127
Rango de unsigned char ❌ ➖:    0      a 255
```

## 6. ¿Cuál es el valor en base 2 (binario) de i, j, k?

Dado las declaraciones de las variables

```c
    char i = 'a';
    char j = 77;
    char k = 0x4D;
```

Por medio de este [codigo](./06-Binario.c) obtenemos la salida

```bash
🔢 Números en Decimal:
----------------------
👉 i = 97
👉 j = 77
👉 k = 77

🔍 Conversión a Binario:
------------------------
🟢 i en binario: 00000000 00000000 00000000 01100001 
🟡 j en binario: 00000000 00000000 00000000 01001101 
🔴 k en binario: 00000000 00000000 00000000 01001101 

📚 Explicaciones:
-----------------
El método `printToBin`:
        ✅ Recorre de izquierda a derecha (bit por bit) e imprime 1 y 0 secuencialmente.
La instrucción `(a >> bit) & 1` realiza lo siguiente:
        ✅ `(a >> bit)`: Desplaza `a`, `bit` veces hacia la derecha (ej: `(10010 >> 1) = 01001`).
        ✅ `&`: Es el operador AND bitwise, que compara los bits menos significativos (ej: `1 & 0 = 0`; `1 & 1 = 1`).
```

Obteniendo asi, el pasaje a binario.

## 7. Correción de Declaraciones

```c
    integer a;                // ❌ Es int, no integer
    short i,j,k;              // ✅
    long float (h);           // ❌ No existe long float, para ello se tiene double
    double long d3;           // ❌ Debe ser long double
    unsigned float n;         // ❌ unsigned solo es valido para enteros
    char 2j;                  // ❌ Variables nunca empiezan con numero
    int MY;                   // ✅
    float ancho, alto, long;  // ❌ Variables no se deben llamar igual que reservadas
    bool i;                   // ⚠️ Solo es valido si se importa <stdbool.h>
```

## 8. Averigüe los tamaños de todos los tipos básicos en su sistema aplicando el operador `sizeof()`

Implementando el [codigo](./08-Sizes.c) se obtiene la siguiente salida:

```bash
📏 Tamaños de los tipos básicos en este sistema:
--------------------------------------------
🔤 char:        1 bytes
🔢 short:       2 bytes
🔢 int:         4 bytes
🔢 long:        8 bytes
🔢 long long:   8 bytes
🎈 float:       4 bytes
🎈🎈 double:    8 bytes
🎈🎈🎈 long double:     16 bytes
--------------------------------------------
```

---

## 9. Desbordamiento del signed char vs. unsigned char

Con el codigo enlazado ([click aqui](./09-Chars.c)), obtenemos la siguiente salida:

```bash
🔵🔴 Comportamiento de desbordamiento (overflow) en chars:
--------------------------------------------------
🔵 A (signed char) [127] antes de sumar:         
🔴 B (unsigned char) [255] antes de sumar:       �
--------------------------------------------------
⚠️ ¡Overflow! ⚠️
🔵 A (signed char) [-128] después de sumar:      �
🔴 B (unsigned char) [0] después de sumar:       
--------------------------------------------------
📝 Explicación:
🔵 Signed char: Al superar CHAR_MAX, vuelve al valor mínimo que es -128.
🔴 Unsigned char: Al superar UCHAR_MAX, vuelve al valor minimo que es 0.
```

Podemos concluir que ante cualquier desbordamiento se vuelve al otro valor extremo del rango.


## 10. (utilice como soporte la sección "3.3. Operaciones con distintos tipos" del PDF taller-c.pdf)

### a) ¿Qué hace falta corregir para que la variable r contenga la división exacta de a y b?

```c
    int a, b;
    float r;
    a = 5;
    b = 2;
    r = a / b;
```

### b) ¿Qué resultado puede esperarse del siguiente fragmento de código?

```c
    int a, b, c, d;
    a = 1;
    b = 2;
    c = a / b;
    d = a / c;
```

### c) ¿Cuál es el resultado del siguiente fragmento de código? Anticipe su respuesta en base a lo dicho en esta unidad y luego confírmela mediante un programa

```c
    printf("%d\n", 20/3);
    printf("%f\n", 20/3);
    printf("%f\n", 20/3.);
    printf("%d\n", 10%3);
    printf("%d\n", 3.1416);
    printf("%f\n", (double)20/3);
    printf("%f\n", (int)3.1416);
    printf("%d\n", (int)3.1416);
```

---

### 11. Escribir un programa que multiplique e imprima 100000 \* 100000

¿De qué tamaño son los ints en su sistema?

---

## 12. Descargue el código ahorcado.c propuesto por la cátedra

### a) Investigar cuál es la función que cumplen las siguientes lineas de código

```c
    #include <stdio.h>
    #include <stdlib.h>
    system ("/bin/stty raw");
    system ("/bin/stty sane erase ^H");
```

### b) Complete el código ahorcado.c usando printf() y getchar(), para desarrollar el juego del ahorcado

```c
#include <stdio.h>
#include <stdlib.h> /* para las funciones system y exit */

int main() {

 int c;

 /* Decirle al sistema que el modo input es RAW */
 system ("/bin/stty raw");

 while(1) {
  printf("\r                                                          ");
  printf("\r c = %c  ingrese una letra (0 para salir): ", c);
  c = getchar();

  if (c == '0')
   break;
 }

 system ("/bin/stty sane erase ^H");
}
```
