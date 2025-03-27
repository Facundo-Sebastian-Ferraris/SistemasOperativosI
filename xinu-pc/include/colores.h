#ifndef COLORES_ARGB_H
#define COLORES_ARGB_H

#include <stdint.h> // Para uint32_t y uint8_t

/* Colores básicos en formato ARGB (0xAARRGGBB) */
#define COLOR_NEGRO 0xFF000000 // Opaco (alpha=0xFF)
#define COLOR_BLANCO 0xFFFFFFFF
#define COLOR_ROJO 0xFFFF0000
#define COLOR_VERDE 0xFF00FF00
#define COLOR_AZUL 0xFF0000FF
#define COLOR_AMARILLO 0xFFFFFF00
#define COLOR_MAGENTA 0xFFFF00FF
#define COLOR_CYAN 0xFF00FFFF
#define COLOR_GRIS 0xFF808080

/* Colores adicionales */
#define COLOR_NARANJA 0xFFFFA500
#define COLOR_ROSADO 0xFFFFC0CB
#define COLOR_VIOLETA 0xFF8A2BE2
#define COLOR_ESMERALDA 0xFF50C878

/* Macro para crear colores ARGB */
#define ARGB(a, r, g, b) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))

/* Macros para descomponer ARGB */
#define GET_A(color) (((color) >> 24) & 0xFF) // Alpha
#define GET_R(color) (((color) >> 16) & 0xFF) // Rojo
#define GET_G(color) (((color) >> 8) & 0xFF)  // Verde
#define GET_B(color) ((color) & 0xFF)         // Azul

/* Macro para cambiar solo el alpha */
#define SET_ALPHA(color, a) (((color) & 0x00FFFFFF) | ((a) << 24))

#endif // COLORES_ARGB_H