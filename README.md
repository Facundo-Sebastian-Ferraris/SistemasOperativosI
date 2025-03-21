# 📚 Introducción a Sistemas Operativos 🖥️

Bienvenido al repositorio de estudio de **Sistemas Operativos**! 🎉 Aquí encontrarás un resumen detallado de las unidades y conceptos clave que debes aprender para dominar esta materia. Desde las **System Calls** hasta otros temas introductorios, este README te guiará paso a paso. 🚀

---

## 🧠 Unidades de Estudio

### 1. **Introducción a los Sistemas Operativos** 🏁

- **¿Qué es un Sistema Operativo?** 🤔
  - Definición y objetivos.
  - Funciones principales: gestión de recursos, abstracción del hardware, seguridad, etc.
- **Evolución histórica** 📜
  - Desde los primeros sistemas batch hasta los sistemas modernos.
- **Tipos de Sistemas Operativos** 🖥️
  - Monousuario vs multiusuario.
  - Monotarea vs multitarea.
  - Sistemas en tiempo real, distribuidos y embebidos.

### 2. **Estructura de un Sistema Operativo** 🏗️

- **Kernel (Núcleo)** 💻
  - Modo kernel vs modo usuario.
  - Funciones del kernel: gestión de procesos, memoria, dispositivos, etc.
- **Capas del Sistema Operativo** 🧅
  - Hardware, kernel, bibliotecas, aplicaciones.
- **Interfaces de usuario** 🖱️
  - CLI (Línea de comandos) vs GUI (Interfaz gráfica).

### 3. **System Calls (Llamadas al Sistema)** 📞

- **¿Qué son las System Calls?** ❓
  - Puente entre las aplicaciones y el kernel.
  - Ejemplos: `read`, `write`, `open`, `close`, `fork`, `exec`.
- **Cómo funcionan** ⚙️
  - Interrupciones y trampas.
  - Cambio de modo (user to kernel).
- **API vs System Calls** 🔄
  - Diferencias y relación entre ambas.

### 4. **Gestión de Procesos** 🔄

- **¿Qué es un proceso?** 🤖
  - Definición y estados: nuevo, listo, en ejecución, bloqueado, terminado.
- **Planificación de procesos (Scheduling)** ⏳
  - Algoritmos: FCFS, SJF, Round Robin, Prioridades.
- **Creación y terminación de procesos** 🛠️
  - `fork()`, `exec()`, `wait()`, `exit()`.

### 5. **Gestión de Memoria** 🧠

- **Memoria principal y secundaria** 💾
  - Diferencias y usos.
- **Fragmentación** 🧩
  - Interna vs externa.
- **Paginación y Segmentación** 📄
  - Conceptos básicos y ventajas/desventajas.
- **Memoria virtual** 🌐
  - Paginación bajo demanda, swapping.

### 6. **Sistemas de Archivos** 📂

- **¿Qué es un sistema de archivos?** ❓
  - Estructura y organización.
- **Tipos de sistemas de archivos** 🗂️
  - FAT, NTFS, ext4, etc.
- **Operaciones básicas** 🛠️
  - Crear, leer, escribir, eliminar archivos.
- **Permisos y seguridad** 🔒
  - Usuarios, grupos y permisos (lectura, escritura, ejecución).

### 7. **Concurrencia y Sincronización** 🔗

- **Problemas de concurrencia** ⚠️
  - Condiciones de carrera, deadlocks, inanición.
- **Mecanismos de sincronización** 🔐
  - Semáforos, mutex, monitores.
- **Ejemplos clásicos** 🧩
  - El problema del productor-consumidor, filósofos cenando.

### 8. **Gestión de Entrada/Salida (E/S)** 🖨️

- **Dispositivos de E/S** 🖱️
  - Tipos: bloque, carácter, red.
- **Controladores de dispositivos** 🎮
  - Funciones y comunicación con el kernel.
- **Buffering y caching** 🗃️
  - Mejora del rendimiento.

---

## 🛠️ Herramientas y Prácticas Recomendadas

- **Entornos de simulación** 🖥️
  - QEMU, VirtualBox, VMware.
- **Lenguajes de programación** 💻
  - C (para system calls), Python (para scripts).
- **Comandos útiles en Linux** 🐧
  - `ps`, `top`, `gcc`, `strace`, `man`.

---

## 📖 Recursos Adicionales

- **Libros recomendados** 📚
  - "Operating System Concepts" de Silberschatz, Galvin y Gagne.
  - "Modern Operating Systems" de Andrew S. Tanenbaum.
- **Enlaces útiles** 🔗
  - Documentación oficial de Linux.
  - Tutoriales en línea sobre system calls y gestión de procesos.

---

## 🚀 ¡Comienza tu viaje en Sistemas Operativos!

Este repositorio es tu guía para entender los conceptos básicos y avanzados de los sistemas operativos. ¡No te rindas y sigue aprendiendo! 🌟
