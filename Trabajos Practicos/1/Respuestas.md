# Resultados TP 1 🖥️✨

_Alumno:_ [Facundo Ferraris [FAI-3810]](https://github.com/Facundo-Sebastian-Ferraris/SistemasOperativosI)

## 1. Primeros pasos con XINU

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

### **Acceso al puerto serial de XINU**

QEMU ofrece la opcion de mostrar las pestañas de secciones, entre ellas esta `serial0` que haciendo click, o haciendo `ctrl + alt + 3`, podremos acceder al shell del sistema.

---

### **1. ¿Cuántos procesos hay en ejecución? ¿Cómo lo obtuvo?**

Para visualizar los procesos en ejecucion existe el comando ps (Proccess Status), el cual muestra una lista de todos los procesos activos, sus IDs, estados, prioridades y otros detalles. En este caso obtuvimos lo siguiente:

```bash
Pid Name             State Prio Ppid Stack Base Stack Ptr  Stack Size
--- ---------------- ----- ---- ---- ---------- ---------- ----------
  0 prnull           ready    0    0 0x005FDFFC 0x00146284     8192
  1 rdsproc          susp   200    0 0x005FBFFC 0x005FBFC8    16384
  3 Main process     recv    20    2 0x005E7FFC 0x005E7F64    65536
  4 shell            recv    50    3 0x005F7FFC 0x005F7C7C     8192
 11 ps               curr    20    4 0x005F5FFC 0x005F5FC4     8192

```

A continuacion, vamos a analizar la salida para entender qué está pasando:  

### **🔍 Explicación clave:**

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

### **🚀 ¿Qué podemos concluir?**  

- El **`shell`** (PID `4`) es el proceso interactivo que usas para ejecutar comandos.  
- El **`Main process`** (PID `3`) parece ser el núcleo del sistema, esperando eventos.  
- **`rdsproc`** (PID `1`) está suspendido, posiblemente relacionado con el sistema de archivos remoto (`rds`).  
- **`ps`** se ejecutó correctamente y terminó (por eso ya no aparece en `curr` si lo vuelves a listar).  

---

### **💡 Comandos útiles para profundizar:**  

- **`kill <PID>`**: Terminar un proceso (ejemplo: `kill 1` para cerrar `rdsproc`).  
- **`memstat`**: Ver uso de memoria (si hay fugas en procesos).  
