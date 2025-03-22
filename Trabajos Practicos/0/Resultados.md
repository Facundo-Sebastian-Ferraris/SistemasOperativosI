# Resultados TP 0 🖥️✨

`Facundo Ferraris [FAI-3810]`

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

En arquitectura de computadoras, una **"word"** (palabra) se refiere a la **unidad de datos básica** que el procesador puede manejar de manera eficiente en una sola operación. Es el tamaño estándar de los registros del procesador y determina cuántos bits puede procesar o transferir simultáneamente. El tamaño de una "word" varía según la arquitectura:

- En una arquitectura de **8 bits**, una word suele ser **1 byte** (8 bits).  
- En una arquitectura de **32 bits**, una word es típicamente **4 bytes** (32 bits).  
- En una arquitectura de **64 bits**, una word es generalmente **8 bytes** (64 bits).  

Por ejemplo, en un procesador de 64 bits, una "word" de 8 bytes permite manejar números enteros o direcciones de memoria de hasta 64 bits en una sola instrucción. Este concepto es clave para entender la capacidad de procesamiento y el diseño de los sistemas operativos y programas en C, ya que afecta cómo se almacenan y operan los tipos de datos como `int`.

> **Nota** ℹ️: El tamaño de una "word" no siempre coincide con el tamaño de un `int` en C, ya que este último depende también del compilador y no solo de la arquitectura.