#ifndef ANSI_H
#define ANSI_H

// --- Limpieza de pantalla/línea ---
#define aCLEAR "\033[2J"   // Borra toda la pantalla
#define aCLINE "\033[2K"   // Borra la línea actual
#define aCLEND "\033[K"    // Borra desde el cursor hasta el fin de línea
#define aCLSTART "\033[1K" // Borra desde el cursor hasta el inicio de línea

// --- Movimiento básico del cursor (sin argumentos) ---
#define aUP "\033[A"          // Mueve el cursor arriba 1 línea
#define aDOWN "\033[B"        // Mueve el cursor abajo 1 línea
#define aRIGHT "\033[C"       // Mueve el cursor a la derecha 1 columna
#define aLEFT "\033[D"        // Mueve el cursor a la izquierda 1 columna
#define aLINE_START "\033[1G" // Mueve el cursor al principio
// --- Movimiento del cursor con argumentos (ej: aUP(5)) ---
#define aUP(n) "\033[" #n "A"
#define aDOWN(n) "\033[" #n "B"
#define aRIGHT(n) "\033[" #n "C"
#define aLEFT(n) "\033[" #n "D"

// --- Posicionamiento absoluto ---
#define aHOME "\033[H"                           // Mueve el cursor a (0,0)
#define aPOS(row, col) "\033[" #row ";" #col "H" // Ej: aaPOS(5,3)

// --- Guardar/Restaurar posición del cursor ---
#define aSAVE "\033[s" // Guarda la posición actual
#define aLOAD "\033[u" // Restaura la posición guardada

// --- Atributos de texto (opcional) ---
#define TEXT_RESET "\033[0m" // Reinicia formato (color, negrita, etc.)
#define TEXT_BOLD "\033[1m"  // Texto en negrita

#endif // ANSI_H