# 🖥️ Sistemas Operativos I - Trabajo Práctico 0 📚

## 📖 Bibliografía

- **Brian Kernighan y Dennis Ritchie**, _El lenguaje de programación C_ 📘  
  (título original en inglés: _The C Programming Language_).
- **Eduardo Grosclaude**, _Taller de Lenguaje en C_ 📄  
  [Enlace al PDF](https://se.fi.uncoma.edu.ar/so/clases/apuntes/taller-c.pdf).

---

## 🛠️ Ejercicios

### 0. **¡Hola, Mundo!** 🌍

Escriba un programa `hello world`. Compilar y ejecutar.  
(Utilice como soporte la sección **"1.4 Un primer ejemplo"** del PDF _taller-c.pdf_).

#### Ejemplo

vi hello.c \# Edición. Usar `vi` u otro editor de preferencia (como `pluma`).
make hello \# Compilación.

#### También se puede compilar el programa invocando `gcc`

```bash
gcc -o hello hello.c # Compilación invocando `gcc`.
```

#### NOTA: No use `make` y luego `gcc`. Uno u otro

```bash
./hello # Ejecución.\
```

> **NOTA** 📝: Para los ejercicios 1 al 9 inclusive, utiliza como soporte el capítulo "Capítulo 3 Tipos de datos y expresiones" del PDF _taller-c.pdf_.

---

### 1. Tipos de datos básicos en C 🚀

Enumera los tipos de datos básicos en C. Escribe una definición de una variable de cada tipo. Por ejemplo: `int a;`.

---

### 2. ¿Qué es una "word" en Arquitectura de Computadoras? 🖥️

Explica qué significa la palabra _word_ cuando el contexto es la Arquitectura de una Computadora.

---

### 3. Bits en una variable `int` en C 🔢

¿Cuántos bits puede almacenar una variable declarada como `int` en C? (Ejemplo: `int var;`).
Supón 3 computadoras con arquitecturas diferentes:

- Arquitectura de **8 bits**
- Arquitectura de **32 bits**
- Arquitectura de **64 bits**

¿Y en tu PC? 🖱️

> **NOTA** ℹ️: La respuesta no es tan trivial como parece. Deberás buscar información sobre el lenguaje de programación C. Usa Wikipedia u otros recursos.

---

### 4. Diferencia en la salida con `printf()` ✏️

Explica la diferencia en la salida de las siguientes instrucciones:

```c
char a = 'M';
printf("a = %i \n", a);
printf("La letra %c \n", a);
```

¿Cuál es el valor numérico de a?

Ayuda: En la función "printf()" se pasa como parámetro la cadena de
caracteres que se desea imprimir y, además, cada una de las variables
que serán visualizadas.

Si deseamos imprimir más de una variable en una cadena de caracteres,
    el orden de los parámetros debe corresponder al orden de dichas
        variables en la cadena.

```c
    char sensor;
    float temp;
    printf('La temperatura de %c es %f',sensor, temp);
```

---

### 5. ¿Cuál es el rango numérico de i y j en su PC?

```c
   char i;
   unsigned char j;
```

---

### 6. ¿Cuál es el valor en base 2 (binario) de i, j, k?

```c
    char i = 'a';
    char j = 77;
    char k = 0x4D;
```

---

### 7. Cuáles de entre estas declaraciones contienen errores?

```c
    integer a;
    short i,j,k;
    long float (h);
    double long d3;
    unsigned float n;
    char 2j;
    int MY;
    float ancho, alto, long;
    bool i;
```

---

### 8. Averigüe los tamaños de todos los tipos básicos en su sistema aplicando el operador `sizeof()`

---

### 9. Prepare un programa con una variable de tipo char y otra de tipo unsigned char

Inicialice ambas variables con los valores máximos de cada tipo,
para comprobar el resultado de incrementarlas en una unidad.
Imprima los valores de cada variable antes y después del incremento.

#### (Nota: vea la sección "3.2. Tamaños de los objetos de datos" de taller-c.pdf.)

---

### 10. (utilice como soporte la sección "3.3. Operaciones con distintos tipos" del PDF taller-c.pdf)

#### a) ¿Qué hace falta corregir para que la variable r contenga la división exacta de a y b?

```c
    int a, b;
    float r;
    a = 5;
    b = 2;
    r = a / b;
```

#### b) ¿Qué resultado puede esperarse del siguiente fragmento de código?

```c
    int a, b, c, d;
    a = 1;
    b = 2;
    c = a / b;
    d = a / c;
```

#### c) ¿Cuál es el resultado del siguiente fragmento de código? Anticipe su respuesta en base a lo dicho en esta unidad y luego confírmela mediante un programa

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

### 12. Descargue el código ahorcado.c propuesto por la cátedra

#### a) Investigar cuál es la función que cumplen las siguientes lineas de código

```c
    #include <stdio.h>
    #include <stdlib.h>
    system ("/bin/stty raw");
    system ("/bin/stty sane erase ^H");
```

#### b) Complete el código ahorcado.c usando printf() y getchar(), para desarrollar el juego del ahorcado

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
