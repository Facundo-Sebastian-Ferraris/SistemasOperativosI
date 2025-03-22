# Resultados TP 0 🖥️✨

_Alumno:_ [Facundo Ferraris [FAI-3810]](https://github.com/Facundo-Sebastian-Ferraris/SistemasOperativosI)

## 0. Hola Mundo

- **Codigo**

```c
#include <stdio.h>

int main() {
    printf("\tHOLA MUNDO! 🌱✨\n");
    return 0;
}
```

- **Salida**

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

---

```c
#include <stdio.h>

int main() {
    printf(
        "\"PC con arquitectura de 64 bits 🖥️ \"\n\tBits en un int: %zu ✨\n ",
        sizeof(int) * 8);
    return 0;
}
```

donde `%zu` es un especificador de formato 

- **Salida**

```bash
"PC con arquitectura de 64 bits 🖥️ "
        Bits en un int: 32 ✨
```

---

Entonces podemos concluir que en nuestra PC, el int ocupa 32 bits

## 4. Diferencia en la salida con `printf()` ✏️

Dado el codigo

```c
char a = 'M';
printf("a = %i \n", a);
printf("La letra %c \n", a);
```

- **Salida**

```bash
a = 77 
La letra M
```
