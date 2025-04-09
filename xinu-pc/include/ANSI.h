#ifndef ANSI_H
#define ANSI_H

#include <xinu.h> // Para kprintf

/* ==================== */
/*  LIMPIEZA DE PANTALLA */
/* ==================== */
#define aCLEAR "\033[2J"   // Borra toda la pantalla
#define aCLINE "\033[2K"   // Borra la línea actual
#define aCLEND "\033[K"    // Borra desde cursor hasta fin de línea
#define aCLSTART "\033[1K" // Borra desde cursor hasta inicio de línea

/* ======================== */
/*  MOVIMIENTO DEL CURSOR   */
/* ======================== */
// Básico (sin argumentos)
#define aLINE_START "\033[1G" // Mueve cursor al inicio de línea

// Funciones con parámetros (implementación inline)
static inline void aUP(int n) { kprintf("\033[%dA", n); }
static inline void aDOWN(int n) { kprintf("\033[%dB", n); }
static inline void aRIGHT(int n) { kprintf("\033[%dC", n); }
static inline void aLEFT(int n) { kprintf("\033[%dD", n); }

// Posicionamiento absoluto
static inline void aPOS(int row, int col) { kprintf("\033[%d;%dH", row, col); }
#define aHOME "\033[H" // Mueve cursor a (0,0)

/* ========================= */
/*  ESTADO DEL CURSOR        */
/* ========================= */
#define aSAVE "\033[s" // Guarda posición actual
#define aLOAD "\033[u" // Restaura posición guardada

/* ==================== */
/*  ATRIBUTOS DE TEXTO  */
/* ==================== */
#define TEXT_RESET "\033[0m"  // Reinicia formato
#define TEXT_BOLD "\033[1m"   // Texto en negrita
#define TEXT_RED "\033[31m"   // Texto en rojo
#define TEXT_GREEN "\033[32m" // Texto en verde
// Puedes añadir más colores según necesites

#endif // ANSI_H