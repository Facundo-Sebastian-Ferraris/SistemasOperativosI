# Ejercicio 2: Análisis de rendimiento y caché 🧠

## ¿Qué es la caché TLB de un procesador, qué contiene y para qué se utiliza? 📍

La **caché TLB (Translation Lookaside Buffer)** es una memoria caché especializada en el procesador que almacena traducciones recientes de direcciones virtuales a direcciones físicas para acelerar el proceso de traducción en sistemas con memoria virtual. 🚀

- **Contenido**:
  - Mapeos de direcciones virtuales a direcciones físicas. 📍
  - Cada entrada incluye:
    - Una dirección virtual (o parte de ella, como el número de página virtual). 🔢
    - La dirección física correspondiente. 🏠
    - Metadatos como permisos (lectura/escritura), bits de validez y, en algunos casos, información sobre el tamaño de la página (4 KB o 2 MB). 📏
- **Uso**:
  - Cuando un programa accede a una dirección de memoria virtual, el procesador consulta la TLB para obtener la dirección física. 🔍
  - Un "hit" en la TLB evita accesos a las tablas de páginas en memoria, que son más lentos. ✅
  - Un "miss" requiere una caminata por las tablas de páginas, generando un **TLB miss** que impacta el rendimiento. ❌
- **Relación con `perf`**:
  - `l1_dtlb_misses`: Fallos en la TLB de nivel 1 para datos. 📉
  - `ls_l1_d_tlb_miss.tlb_reload_4k_l2_miss` y `ls_l1_d_tlb_miss.tlb_reload_2m_l2_miss`: Recargas de TLB para páginas de 4 KB o 2 MB desde niveles superiores (L2 o memoria). 🔄

## ¿Qué es la caché de datos de un procesador? 💾

La **caché de datos** es una memoria rápida en el procesador que almacena copias de datos frecuentemente utilizados de la RAM para reducir la latencia de acceso. ⚡

- **Contenido**:
  - Bloques de datos (líneas de caché, típicamente 64 bytes) copiados desde la RAM. 📦
  - Cada línea incluye:
    - Los datos en sí. 📊
    - Una etiqueta que identifica la dirección de memoria. 🏷️
    - Metadatos como bits de validez, estado de coherencia y bits de suciedad. 🔧
- **Uso**:
  - Permite accesos rápidos a datos sin consultar la RAM. 🚀
  - Los `cache-misses` en `perf` indican que los datos no estaban en la caché, requiriendo accesos a niveles superiores (L2, L3) o RAM. 📉

## Análisis de los datos de `perf` y códigos 📊

Los datos de `perf` corresponden a tres programas (`sample1`, `sample2`, `sample3`) que reservan un bloque de memoria de `N * BSIZE` bytes (`240,000 * 4,096 = 983,040,000` bytes ≈ 937 MB) y lo recorren para escribir y verificar valores. Analizamos las preguntas con base en los datos y los códigos proporcionados. 🖥️

### Datos de `perf` 📈

- **sample1**:
  - Tiempo: 26.64 s ⏱️
  - `l1_dtlb_misses`: 601,573,063 📉
  - `ls_l1_d_tlb_miss.tlb_reload_4k_l2_miss`: 471,953,763 🔄
  - `ls_l1_d_tlb_miss.tlb_reload_2m_l2_miss`: 309,005 🔄
  - `cache-misses`: 1,118,111,307 📉
- **sample2**:
  - Tiempo: 7.61 s ⏱️
  - `l1_dtlb_misses`: 1,222,778 📉
  - `ls_l1_d_tlb_miss.tlb_reload_4k_l2_miss`: 689,068 🔄
  - `ls_l1_d_tlb_miss.tlb_reload_2m_l2_miss`: 11,140 🔄
  - `cache-misses`: 5,708,226 📉
- **sample3**:
  - Tiempo: 11.87 s ⏱️
  - `l1_dtlb_misses`: 246,136,024 📉
  - `ls_l1_d_tlb_miss.tlb_reload_4k_l2_miss`: 245,226,959 🔄
  - `ls_l1_d_tlb_miss.tlb_reload_2m_l2_miss`: 149,730 🔄
  - `cache-misses`: 265,851,205 📉

### ¿Qué versión tiene el peor rendimiento? ¿Encuentra una relación entre ese rendimiento con los fallos de caché y TLB reportados por perf? 📉

- **Peor rendimiento**: `sample1` (26.64 s) 😔
- **Análisis del código**:
  - **Recorrido de escritura**:

    ```c
    for (j=0; j<BSIZE; j++) {
        for (i=0; i<N; i++) {
            *(pp+i*BSIZE+j) = 2; // pp[i][j] = 2;
        }
    }
    ```

  - La memoria se recorre por columnas (`j` en el bucle externo, `i` en el interno), generando accesos no consecutivos con saltos de 4,096 bytes (`i*BSIZE`). 📏
  - **Impacto**:
    - **Baja localidad espacial**: Los accesos separados por 4 KB causan altos `cache-misses` (1,118M), ya que las líneas de caché (64 bytes) no se reutilizan. 🧠
    - **Baja localidad temporal**: Cada acceso puede requerir una nueva página (4 KB), saturando la TLB (`l1_dtlb_misses`: 601M). 📍
- **Relación**:
  - Los altos fallos TLB y de caché explican el tiempo elevado. Los accesos no consecutivos generan recargas frecuentes, aumentando la latencia. ⏳

### ¿Qué versión tiene el mejor rendimiento? Analice en grupo de qué manera el programa de mejor rendimiento recorre la memoria reservada 🏆

- **Mejor rendimiento**: `sample2` (7.61 s) 🎉
- **Análisis del código**:
  - **Recorrido de escritura**:

    ```c
    for (i=0; i<N; i++) {
        for (j=0; j<BSIZE; j++) {
            *(pp+i*BSIZE+j) = 2; // pp[i][j] = 2;
        }
    }
    ```

  - La memoria se recorre por filas (`i` en el bucle externo, `j` en el interno), con accesos **secuenciales** dentro de cada bloque de 4,096 bytes. 🚶
  - **Impacto**:
    - **Alta localidad espacial**: Accesos consecutivos (`j` incrementa en 1) llenan líneas de caché (64 bytes), reduciendo `cache-misses` (5.7M). 🧠
    - **Alta localidad temporal**: Cada bloque de 4 KB se procesa completamente, minimizando recargas de TLB (`l1_dtlb_misses`: 1.2M). 📍
    - El bajo `ls_l1_d_tlb_miss.tlb_reload_2m_l2_miss` (11K) sugiere posible uso de páginas grandes (2 MB). 📏
- **Conclusión**: `sample2` recorre la memoria secuencialmente, maximizando la reutilización de caché y TLB, lo que explica su mejor rendimiento. ✅

### ¿Qué diferencia existe en la manera de recorrer la memoria entre el programa de mejor rendimiento y el de rendimiento medio? Hipotetice o explique por qué razón el programa de mejor rendimiento supera al de rendimiento medio 🌟

- **Rendimiento medio**: `sample3` (11.87 s) ⚖️
- **Análisis del código**:
  - **Recorrido de escritura**:

    ```c
    for (k=0; k<BSIZE/SMALL; k++) {
        for (i=0; i<N; i++) {
            for (j=0; j<SMALL; j++) {
                *(pp+i*BSIZE+(SMALL*k+j)) = 2; // pp[i][SMALL*k+j] = 2;
            }
        }
    }
    ```

  - La memoria se recorre en bloques de 4 bytes (`SMALL`). Para cada `k`, se accede a todos los `i` (saltos de 4 KB) y `j` (0 a 3). 📏
  - **Impacto**:
    - **Localidad espacial moderada**: Accesos consecutivos dentro de 4 bytes, pero saltos de 4 KB entre filas causan más `cache-misses` (265M). 🧠
    - **Localidad temporal baja**: Accesos a la misma página se distribuyen en múltiples iteraciones de `k`, aumentando `l1_dtlb_misses` (246M). 📍
    - Uso predominante de páginas de 4 KB (`ls_l1_d_tlb_miss.tlb_reload_4k_l2_miss`: 245M). 📏

- **Diferencias con `sample2`**:
  - **sample2**: Recorre cada bloque de 4 KB secuencialmente, maximizando localidad. 🚶
  - **sample3**: Divide el recorrido en bloques de 4 bytes con saltos de 4 KB, rompiendo la localidad. 🏃
- **Razones del mejor rendimiento de `sample2`**:
  - **Localidad espacial**: Accede a direcciones consecutivas, llenando líneas de caché eficientemente. 🧠
  - **Localidad temporal**: Procesa un bloque completo, reutilizando entradas TLB. 📍
  - **Páginas grandes**: Menos recargas de TLB (`ls_l1_d_tlb_miss.tlb_reload_2m_l2_miss`: 11K). 📏
  - **sample3** alterna entre bloques de 4 KB, causando más fallos. 😕
- **Relación con `perf`**:
  - Los fallos de `sample3` (246M TLB, 265M caché) son ~200 veces mayores que los de `sample2` (1.2M TLB, 5.7M caché), explicando la diferencia de ~4 segundos. ⏳

### Diagrama de la memoria y la forma en que se recorre 🗺️

La memoria reservada (`pp`) es un arreglo de `N * BSIZE` bytes (937 MB), interpretado como una matriz de `N` filas (240,000) y `BSIZE` columnas (4,096 bytes). 📏

**Diagrama conceptual (texto)**:

```bash
Memoria reservada (pp):
[ Fila 0: [0, 1, ..., 4095] ][ Fila 1: [4096, 4097, ..., 8191] ] ... [ Fila N-1 ] 📦

Caché L1 (líneas de 64 bytes):
[ Línea 1 | Línea 2 | ... ] 🧠

TLB (entradas para páginas de 4 KB o 2 MB):
[ Página virtual 1 -> Física 1 ]
[ Página virtual 2 -> Física 2 ] 📍

Recorrido de memoria:
- sample2 (mejor rendimiento) 🏆:
  Secuencial por filas:
  [Fila 0: 0, 1, 2, ..., 4095] -> [Fila 1: 4096, 4097, ..., 8191] -> ... 🚶
  - Accesos consecutivos dentro de cada fila (4 KB).
  - Máxima localidad espacial: llena líneas de caché (64 bytes). 🧠
  - Mínimos fallos TLB: una página (4 KB) cubre una fila. 📍
  Ejemplo: for (i=0; i<N; i++) for (j=0; j<BSIZE; j++) pp[i*BSIZE+j] = 2;

- sample3 (rendimiento medio) ⚖️:
  Por bloques de 4 bytes con saltos de 4 KB:
  [Fila 0: 0,1,2,3] -> [Fila 1: 4096,4097,4098,4099] -> ... -> [Fila N-1] -> [Fila 0: 4,5,6,7] -> ... 🏃
  - Localidad espacial limitada: accesos consecutivos solo dentro de 4 bytes.
  - Saltos de 4 KB generan más fallos de caché y TLB. 📉
  Ejemplo: for (k=0; k<BSIZE/4; k++) for (i=0; i<N; i++) for (j=0; j<4; j++) pp[i*BSIZE+(4*k+j)] = 2;

- sample1 (peor rendimiento) 😔:
  Por columnas:
  [Fila 0: 0] -> [Fila 1: 4096] -> ... -> [Fila N-1] -> [Fila 0: 1] -> ... 🐢
  - Accesos no consecutivos (saltos de 4 KB).
  - Mínima localidad: altos fallos de caché y TLB. 📉
  Ejemplo: for (j=0; j<BSIZE; j++) for (i=0; i<N; i++) pp[i*BSIZE+j] = 2;
```

**Gráfico comparativo** (código Chart.js para visualizar fallos) 📊:

```javascript
{
  "type": "bar",
  "data": {
    "labels": ["sample1 😔", "sample2 🏆", "sample3 ⚖️"],
    "datasets": [
      {
        "label": "L1 DTLB Misses (millones) 📉",
        "data": [601.573, 1.223, 246.136],
        "backgroundColor": "rgba(255, 99, 132, 0.8)"
      },
      {
        "label": "Cache Misses (millones) 📉",
        "data": [1118.111, 5.708, 265.851],
        "backgroundColor": "rgba(54, 162, 235, 0.8)"
      }
    ]
  },
  "options": {
    "scales": {
      "y": {
        "beginAtZero": true,
        "title": {
          "display": true,
          "text": "Cantidad (millones)"
        }
      },
      "x": {
        "title": {
          "display": true,
          "text": "Programa"
        }
      }
    },
    "plugins": {
      "legend": {
        "display": true
      }
    }
  }
}
```

## Resumen 📝

- **Peor rendimiento**: `sample1` (26.64 s 😔) recorre por columnas, con saltos de 4 KB, causando altos `cache-misses` (1,118M) y `l1_dtlb_misses` (601M). 📉
- **Mejor rendimiento**: `sample2` (7.61 s 🏆) recorre por filas, con accesos secuenciales, minimizando `cache-misses` (5.7M) y `l1_dtlb_misses` (1.2M). 🚶
- **Rendimiento medio**: `sample3` (11.87 s ⚖️) usa bloques de 4 bytes con saltos de 4 KB, generando más fallos (`cache-misses`: 265M, `l1_dtlb_misses`: 246M). 🏃
- **Razones de la diferencia**: `sample2` supera a `sample3` por su recorrido secuencial, que maximiza localidad y aprovecha páginas grandes (2 MB). 🌟
