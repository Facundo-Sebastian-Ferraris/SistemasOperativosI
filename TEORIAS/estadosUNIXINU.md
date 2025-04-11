---

### **Tabla Comparativa: Estados de Procesos en XINU vs UNIX**  

| **Aspecto**              | **XINU**                                                                 | **UNIX (Linux/BSD)**                                                                 |
|--------------------------|--------------------------------------------------------------------------|-------------------------------------------------------------------------------------|
| **Estados Principales**  | `PR_FREE`, `PR_CURR`, `PR_READY`, `PR_SLEEP`, `PR_SUSP`, `PR_RECV`, `PR_WAIT` | `TASK_RUNNING`, `TASK_INTERRUPTIBLE`, `TASK_UNINTERRUPTIBLE`, `TASK_STOPPED`, `TASK_ZOMBIE`, `TASK_DEAD` |
| **Creación**             | `create()` - Asigna entrada en la tabla de procesos.                     | `fork()`/`clone()` - Crea un nuevo proceso hijo.                                    |
| **Terminación**          | `kill(pid)` - Libera el proceso (estado → `PR_FREE`).                    | `exit()` - Termina el proceso (estado → `TASK_ZOMBIE` → `TASK_DEAD`).               |
| **Planificación**        | `resched()` - Cambia al siguiente proceso en cola Round-Robin.           | `schedule()` - Usa políticas como CFS (Completely Fair Scheduler).                 |
| **Bloqueo (I/O o Espera)** | `receive()` (mensajes), `wait()` (semáforos), `sleep()` (temporizador). | `wait()`, `read()` (en I/O bloqueante), `nanosleep()`.                             |
| **Despertar**            | `send(pid, msg)` (mensajes), `signal()` (semáforos), `wakeup()`.         | `wake_up()` (kernel), `kill(pid, SIGCONT)` (señales).                              |
| **Suspensión**           | `suspend(pid)` - Pasa a `PR_SUSP`.                                       | `kill(pid, SIGSTOP)` - Pasa a `TASK_STOPPED`.                                      |
| **Reanudación**          | `resume(pid)` - Vuelve a `PR_READY`.                                     | `kill(pid, SIGCONT)` - Vuelve a `TASK_RUNNING`.                                    |
| **Estados Inmunes a Ciertos Métodos** |                                                                 |                                                                                     |
| - **Proceso en `PR_SUSP`** | `suspend()` no tiene efecto.                                           | `SIGSTOP` no afecta si ya está en `TASK_STOPPED`.                                  |
| - **Proceso en `PR_SLEEP`** | `sleep()` no lo vuelve a dormir.                                       | `nanosleep()` no afecta si ya está dormido.                                        |
| - **Proceso en `PR_FREE`** | `kill()` no tiene efecto.                                               | `exit()` no afecta a un proceso ya en `TASK_DEAD`.                                 |
| - **Proceso en `PR_RECV`** | `receive()` no tiene efecto (ya espera mensaje).                       | `read()` en modo no bloqueante no duerme si no hay datos (`EAGAIN`).               |
| **Manejo de Zombies**    | No existe (proceso termina → `PR_FREE`).                                | `wait()`/`waitpid()` necesario para liberar recursos de procesos en `TASK_ZOMBIE`. |
| **Prioridades**          | Prioridades fijas (asignadas en `create()`).                            | Prioridades dinámicas (ej: nice, políticas de scheduler como CFS).                 |

---

### **Explicación Clave:**  

1. **Estados en XINU** son más simples y orientados a sistemas embebidos/educativos.  
   - No hay zombies ni jerarquías de procesos complejas.  
   - La planificación es Round-Robin con quantum fijo.  

2. **Estados en UNIX** son más complejos y orientados a sistemas generales.  
   - Incluye estados como `TASK_INTERRUPTIBLE` (espera con posibilidad de señales).  
   - Usa señales (`SIGSTOP`, `SIGCONT`) para suspender/reanudar.  
   - El scheduler es más avanzado (ej: CFS en Linux).  

3. **Funciones que no afectan a procesos en ciertos estados:**  
   - En ambos sistemas, intentar suspender un proceso ya suspendido (`PR_SUSP`/`TASK_STOPPED`) no tiene efecto.  
   - En UNIX, señales como `SIGKILL` pueden matar procesos en casi cualquier estado (excepto `TASK_UNINTERRUPTIBLE`).  

4. **Manejo de terminación:**  
   - Xinu libera el proceso inmediatamente con `kill()`.  
   - UNIX requiere que el padre haga `wait()` para limpiar zombies.  

---

### **Conclusión**  

- **XINU** es más simple y predecible, con menos estados y funciones directas.  
- **UNIX** es más robusto y flexible, con manejo de señales, jerarquías de procesos y schedulers complejos.  

Aquí tienes una **versión ampliada** de la tabla comparativa entre **XINU** y **UNIX**, ahora incluyendo **ejemplos de código** para cada caso, con explicaciones de constantes relevantes como `WNOHANG`, `WUNTRACED`, y cómo se usan en combinación con funciones como `waitpid()`.  

---

### **Tabla Comparativa: Estados de Procesos en XINU vs UNIX (con Ejemplos de Código)**  

| **Operación**          | **XINU** (Ejemplos)                                                                 | **UNIX/Linux** (Ejemplos)                                                                 |
|------------------------|------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------|
| **Crear un proceso**   | ```c                                                                               | ```c                                                                                     |
|                        | pid = create(func, stacksz, priority, name, args);                                | pid = fork();                                                                            |
|                        | ```                                                                                | if (pid == 0) { /*Código hijo*/ exit(0); }                                            |
|                        |                                                                                    | ```                                                                                      |
| **Terminar proceso**   | ```c                                                                               | ```c                                                                                     |
|                        | kill(pid);  // Estado → `PR_FREE`                                                 | exit(0);  // Estado → `TASK_ZOMBIE`                                                     |
|                        | ```                                                                                | ```                                                                                      |
| **Esperar terminación**| ```c                                                                               | ```c                                                                                     |
|                        | // No hay equivalente directo (Xinu no maneja zombies).                            | int status;                                                                              |
|                        |                                                                                    | waitpid(pid, &status, 0);  // Espera bloqueante                                          |
|                        |                                                                                    | waitpid(pid, &status, WNOHANG);  // No bloquea (retorna inmediato)                      |
|                        |                                                                                    | ```                                                                                      |
| **Suspender proceso**  | ```c                                                                               | ```c                                                                                     |
|                        | suspend(pid);  // Estado → `PR_SUSP`                                              | kill(pid, SIGSTOP);  // Estado → `TASK_STOPPED`                                         |
|                        | ```                                                                                | ```                                                                                      |
| **Reanudar proceso**   | ```c                                                                               | ```c                                                                                     |
|                        | resume(pid);  // Estado → `PR_READY`                                              | kill(pid, SIGCONT);  // Estado → `TASK_RUNNING`                                         |
|                        | ```                                                                                | ```                                                                                      |
| **Dormir proceso**     | ```c                                                                               | ```c                                                                                     |
|                        | sleep(1000);  // Duerme 1 seg (Estado → `PR_SLEEP`)                               | sleep(1);        // Segundos                                                             |
|                        | ```                                                                                | usleep(1000000); // Microsegundos                                                       |
|                        |                                                                                    | nanosleep({1, 0}, NULL);  // Nanosegundos                                               |
|                        |                                                                                    | ```                                                                                      |
| **Esperar señal/semáforo** | ```c                                                                           | ```c                                                                                     |
|                        | wait(sem);  // Estado → `PR_WAIT`                                                 | wait(NULL);      // Espera cualquier hijo                                               |
|                        | ```                                                                                | sem_wait(&sem);  // Espera en semáforo POSIX                                            |
|                        |                                                                                    | sigsuspend(&mask);  // Espera señal                                                     |
|                        |                                                                                    | ```                                                                                      |
| **Enviar señal/mensaje** | ```c                                                                             | ```c                                                                                     |
|                        | send(pid, msg);  // Despierta proceso en `PR_RECV`                                | kill(pid, SIGUSR1);  // Envía señal                                                     |
|                        | ```                                                                                | msgsnd(qid, &msg, sizeof(msg), 0);  // Envía mensaje IPC                                |
|                        |                                                                                    | ```                                                                                      |
| **Manejo de zombies**  | ```c                                                                               | ```c                                                                                     |
|                        | // No aplica (Xinu no tiene zombies).                                              | waitpid(pid, &status, WNOHANG);  // Opción no bloqueante                                |
|                        |                                                                                    | waitpid(-1, &status, WUNTRACED);  // También detecta hijos suspendidos (SIGSTOP)       |
|                        |                                                                                    | ```                                                                                      |

---

### **Explicación de Constantes y Casos Especiales en UNIX**  

#### **1. `waitpid()` y sus opciones:**  

- **`WNOHANG`**:  
  - Hace que `waitpid` retorne inmediatamente, incluso si el hijo no ha terminado.  
  - Útil para "preguntar" si un proceso hijo ya terminó sin bloquearse.  

  ```c
  pid_t pid = fork();
  if (pid == 0) exit(42);  // Hijo termina con código 42
  int status;
  pid_t ret = waitpid(pid, &status, WNOHANG);
  if (ret == 0) {
      printf("El hijo aún está en ejecución.\n");
  } else if (WIFEXITED(status)) {
      printf("El hijo terminó con código %d.\n", WEXITSTATUS(status));
  }
  ```

- **`WUNTRACED`**:  
  - Detecta hijos que fueron **suspendidos** (con `SIGSTOP`).  

  ```c
  pid_t pid = fork();
  if (pid == 0) while(1) pause();  // Hijo en bucle infinito
  kill(pid, SIGSTOP);  // Suspendemos el hijo
  int status;
  waitpid(pid, &status, WUNTRACED);
  if (WIFSTOPPED(status)) {
      printf("Hijo suspendido con señal %d.\n", WSTOPSIG(status));
  }
  ```

#### **2. Macros para analizar `status` (UNIX):**  

- **`WIFEXITED(status)`**: Verifica si el hijo terminó normalmente (con `exit`).  
- **`WEXITSTATUS(status)`**: Obtiene el código de salida del hijo.  
- **`WIFSIGNALED(status)`**: Verifica si el hijo fue terminado por una señal.  
- **`WTERMSIG(status)`**: Obtiene el número de la señal que terminó al hijo.  

#### **3. Ejemplo de `SIGCONT` y `SIGSTOP` (UNIX):**  

```c
pid_t pid = fork();
if (pid == 0) {
    while (1) {
        printf("Hijo ejecutando...\n");
        sleep(1);
    }
} else {
    sleep(2);
    kill(pid, SIGSTOP);  // Suspender hijo
    sleep(2);
    kill(pid, SIGCONT);  // Reanudar hijo
    sleep(2);
    kill(pid, SIGKILL);  // Terminar hijo
}
```

---

### **Diferencias Clave**  

1. **Jerarquía de procesos**:  
   - En UNIX, los procesos forman un árbol (padre-hijo). En Xinu, no hay jerarquía.  
2. **Señales vs. Funciones**:  
   - UNIX usa señales (`SIGSTOP`, `SIGCONT`), mientras que Xinu usa funciones directas (`suspend()`, `resume()`).  
3. **Zombies**:  
   - UNIX requiere `wait()` para limpiar zombies. Xinu libera recursos inmediatamente con `kill()`.  

---

### **Conclusión**  

- **XINU** es ideal para entender conceptos básicos de sistemas operativos (sin señales, zombies, o schedulers complejos).  
- **UNIX** es más potente pero requiere manejar detalles como señales, zombies, y opciones de `waitpid()`.  
