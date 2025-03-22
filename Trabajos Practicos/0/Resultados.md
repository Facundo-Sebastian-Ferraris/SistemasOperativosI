# Resultados TP 0 🖥️✨

`_Alumno:_ Facundo Ferraris [FAI-3810]`

## 0. Hola Mundo!

### Codigo

```c
#include <stdio.h>

int main() {
    printf("\tHOLA MUNDO! 🌱✨\n");
    return 0;
}
```

### Salida

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

- A su vez se encuentran los modificadores que permiten agregar/restringir criterios para cada tipo: 🔧
  - **`short`**: Reduce el tamaño del tipo base, generalmente usado con `int`.  
    - **Tamaño típico**: 2 bytes (16 bits).  
    - **Rango**: -32,768 a 32,767.  
    - **Efecto**: Limita la capacidad para ahorrar memoria.
  - **`long`**: Aumenta el tamaño del tipo base, aplicable a `int` o `double`.  
    - **Tamaño típico**: 4 bytes (32 bits) o 8 bytes (64 bits) para `long int`; 10-16 bytes para `long double`.  
    - **Rango**: Para `long int` en 64 bits: -9,223,372,036,854,775,808 a 9,223,372,036,854,775,807.  
    - **Efecto**: Permite almacenar valores más grandes o mayor precisión.
  - **`unsigned`**: Elimina el signo, usando todos los bits para valores positivos.  
    - **Tamaño típico**: Igual al tipo base (ej. 4 bytes para `unsigned int`).  
    - **Rango**: Para `unsigned int`: 0 a 4,294,967,295.  
    - **Efecto**: Duplica el límite superior, restringe a solo positivos.
  - **`signed`**: Especifica que el tipo incluye valores negativos (predeterminado en la mayoría de los casos).  
    - **Tamaño típico**: Igual al tipo base (ej. 4 bytes para `signed int`).  
    - **Rango**: Para `signed int`: -2,147,483,648 a 2,147,483,647.  
    - **Efecto**: Asegura un rango con signo (rara vez necesario explícitamente).

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

¿Cuántos bits puede almacenar una variable declarada como `int` en C? (Ejemplo: `int var;`).
Supón 3 computadoras con arquitecturas diferentes:

- Arquitectura de **8 bits**
- Arquitectura de **32 bits**
- Arquitectura de **64 bits**

¿Y en tu PC? 🖱️

> **NOTA** ℹ️: La respuesta no es tan trivial como parece. Deberás buscar información sobre el lenguaje de programación C. Usa Wikipedia u otros recursos.
