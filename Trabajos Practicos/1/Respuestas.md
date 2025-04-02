# [**Resultados TP 1 🖥️✨**](./README.md#-trabajo-practico-1-trabajando-con-xinu)

_Alumno:_ [Facundo Ferraris [FAI-3810]](https://github.com/Facundo-Sebastian-Ferraris/SistemasOperativosI)

## [**1. Primeros pasos con XINU**](./README.md#-ejercicio-1-primeros-pasos-con-xinu)

### **🔧 Componentes principales del sistema Xinu:**

Basándonos en el [árbol de archivos de XINU](./XinuTree.txt), podemos encontrar:

1. **⚙️ Núcleo (Kernel)**  
   - 🏗️ Gestión de procesos (`create.c`, `kill.c`).  
   - ⏳ Planificación (`resched.c`).  
   - 🔒 Sincronización (`semaphore.c`).  
   - ⚡ Interrupciones (`intr.S`).  
   - 🧠 Memoria (`meminit.c`).  

2. **📂 Sistema de archivos**  
   - 💾 **Local** (`lfs*`).  
   - 🌐 **Remoto** (`rfs*`).  
   - 🚀 **RAM disk** (`ram*.c`).  

3. **🌐 Redes**  
   - 📶 **Tarjeta de red Intel 82545EM** (`eth*.c`).  
   - 🕸️ **Protocolos**: ARP, IP, UDP (`arp.c`, `ip.c`).  
   - 📡 **DHCP & DNS** (`dhcp.c`, `dns.c`).  

4. **🐚 Shell y comandos**  
   - 💻 Intérprete (`shell.c`).  
   - 📜 Comandos (`xsh_*.c` como `xsh_ping`, `xsh_arp`).  

5. **📚 Bibliotecas estándar**  
   - 📝 Funciones de C (`str*.c`, `printf.c`).  

---

### **🖥️ Periféricos soportados:**

| **Periférico**         | **Drivers/Archivos** |  
|----------------------  |----------------------|  
| **Consola/VGA** 🖥️     | `vga.c`, `text_on_vga.c` |  
| **Teclado** ⌨️          | `kbd*.c` |  
| **Mouse** 🐭            | `mice*.c` |  
| **Red (Ethernet)** 🌐   | `eth*.c`, `e1000e.h` |  
| **RAM Disk** 💾         | `ram*.c` |  
| **PCI** 🔌              | `pci.c` |  
| **Reloj (RTC)** ⏰     | `clk*.c` |  

---

### **🔍 Observaciones extra:**

- **Arquitectura**: El código está orientado a x86 (ejemplo: `i386.c`, `start.S`)
- **Arranque MultiBoot**: Soporte para arranque via GRUB (`multiboot.h`) 🚀
- **Modo protegido**: Manejo de interrupciones y contexto de CPU (`ctxsw.S`, `intr.S`)🛡️  

---

### **Acceso al puerto serial de XINU** 🖥️🔌  

QEMU ofrece la opción de mostrar las pestañas de secciones, entre ellas está `serial0`. Haciendo clic en ella o usando `Ctrl + Alt + 3`, podrás acceder al **shell del sistema**.  

---

### **Visualización de Procesos** 📊👀  

Para ver los procesos en ejecución, usa el comando `ps` (**Process Status**). Este muestra una lista de todos los procesos activos, incluyendo sus **IDs, estados, prioridades** y más detalles.  

🔹 **Ejemplo de salida:**

```bash
Pid Name             State Prio Ppid Stack Base Stack Ptr  Stack Size
--- ---------------- ----- ---- ---- ---------- ---------- ----------
  0 prnull           ready    0    0 0x005FDFFC 0x00146284     8192
  1 rdsproc          susp   200    0 0x005FBFFC 0x005FBFC8    16384
  3 Main process     recv    20    2 0x005E7FFC 0x005E7F64    65536
  4 shell            recv    50    3 0x005F7FFC 0x005F7C7C     8192
 11 ps               curr    20    4 0x005F5FFC 0x005F5FC4     8192

```

#### **🔍 Explicación clave del resultado anterior:**

1. **PID (Process ID)**: Identificador único del proceso.  
   - `0` (`prnull`): Proceso especial (nulo/inactivo).  
   - `1` (`rdsproc`): Proceso relacionado con **disco remoto** (suspendido).  
   - `3` (`Main process`): Proceso principal (en estado `recv`, esperando mensajes).  
   - `4` (`shell`): ¡El shell de Xinu! (también en `recv`).  
   - `11` (`ps`): **Proceso actual** (el que se ejecutó).  

2. **Estados (`State`)**:  
   - `ready` ⏳🚀: Listo para ejecutarse.  
   - `susp` 🛑💤: Suspendido (ejemplo: `rdsproc`).  
   - `recv` ✉️🤔: Esperando recibir un mensaje (como el `Main process` y el `shell`).  
   - `curr` ⚡🔥: En ejecución actual (`ps`).  

3. **Prioridad (`Prio`)**:  
   - Mayor número = Mayor prioridad (ejemplo: `rdsproc` tiene `200`).  

4. **PPID (Parent PID)**:  
   - El `shell` (PID `4`) fue creado por el `Main process` (PID `3`).  
   - El comando `ps` (PID `11`) fue lanzado desde el `shell` (PID `4`).  

5. **Stack (Pila)**:  
   - Direcciones de memoria y tamaño asignado a cada proceso.  

---

#### **🚀 ¿Qué podemos concluir?**  

- El **`shell`** (PID `4`) es el proceso interactivo que usas para ejecutar comandos.  
- El **`Main process`** (PID `3`) parece ser el núcleo del sistema, esperando eventos.  
- **`rdsproc`** (PID `1`) está suspendido, posiblemente relacionado con el sistema de archivos remoto (`rds`).  
- **`ps`** se ejecutó correctamente y terminó (por eso ya no aparece en `curr` si lo vuelves a listar).  

---

#### **💡 Comandos útiles para profundizar:**  

- **`kill <PID>`**: Terminar un proceso (ejemplo: `kill 1` para cerrar `rdsproc`).  
- **`memstat`**: Ver uso de memoria (si hay fugas en procesos).  

## [🎨 Ejercicio 2: Modificación de la Pantalla Principal en Xinu 🖥️](./README.md#-ejercicio-2-modificación-de-xinu)

En el directorio `system` encontramos el archivo `main.c`, el cual contiene instrucciones básicas como:  

- Pintar la pantalla de amarillo (`paint_screen()`) 🟨  
- Imprimir texto en la pantalla VGA usando `print_text_on_vga(x, y, s)`, donde:  
  - `x` = posición horizontal  
  - `y` = posición vertical (aumenta hacia abajo)  
  - `s` = texto a mostrar  

### 🛠️ Modificaciones realizadas  

#### 1. **Fondo con Degradado** 🌈

Se modificó `paint_screen()` para que genere un **degradado suave** desde negro hasta un color personalizado, en lugar de un fondo plano.  

#### 2. **Texto en Blanco** ⚪

El color del texto se cambió a **blanco** para garantizar un buen contraste con el fondo oscuro del degradado.  

#### 3. **ASCII Art + Datos del Alumno** 🎨📝

En [`main.c`](../../xinu-pc/system/main.c), se agregó una función `printWallpaper()` que muestra:  

- **Arte ASCII** (diseños creados con caracteres).  
- **Nombre y legajo del alumno** en un formato visualmente atractivo.  

#### 🎨 **Manejo de Colores Simplificado**

Para facilitar el trabajo con colores, se incluyó la librería **[colores.h](../../xinu-pc/include/colores.h)**, que contiene:  

- **Constantes predefinidas** en formato hexadecimal (ej: `COLOR_ROJO = 0xFFFF0000`).  
- **Funciones útiles**:  
  - `ARGB(a, r, g, b)` → Genera un color personalizado en formato **ARGB**.  
  - `GET_A(color)`, `GET_R(color)`, `GET_G(color)`, `GET_B(color)` → Extraen componentes del color.  

🔹 **Formato ARGB**:

- **A** (Alpha - Transparencia)  
- **R** (Rojo)  
- **G** (Verde)  
- **B** (Azul)  

### 🚀 Visualizacion de la imagen

![xinuScreen](./XinuScreenSample.png)
