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

#ifndef ANSI_COLORS_H
#define ANSI_COLORS_H

/* Códigos ANSI para colores de texto */
#define ANSI_RESET "\033[0m"
#define ANSI_BLACK "\033[30m"
#define ANSI_RED "\033[31m"
#define ANSI_GREEN "\033[32m"
#define ANSI_YELLOW "\033[33m"
#define ANSI_BLUE "\033[34m"
#define ANSI_MAGENTA "\033[35m"
#define ANSI_CYAN "\033[36m"
#define ANSI_WHITE "\033[37m"
#define ANSI_DEFAULT "\033[39m"

/* Códigos ANSI para colores de fondo */
#define ANSI_BG_BLACK "\033[40m"
#define ANSI_BG_RED "\033[41m"
#define ANSI_BG_GREEN "\033[42m"
#define ANSI_BG_YELLOW "\033[43m"
#define ANSI_BG_BLUE "\033[44m"
#define ANSI_BG_MAGENTA "\033[45m"
#define ANSI_BG_CYAN "\033[46m"
#define ANSI_BG_WHITE "\033[47m"
#define ANSI_BG_DEFAULT "\033[49m"

/* Estilos de texto */
#define ANSI_BOLD "\033[1m"
#define ANSI_DIM "\033[2m"
#define ANSI_ITALIC "\033[3m"
#define ANSI_UNDERLINE "\033[4m"
#define ANSI_BLINK "\033[5m"
#define ANSI_REVERSE "\033[7m"
#define ANSI_HIDDEN "\033[8m"
#define ANSI_STRIKETHROUGH "\033[9m"

/* Versiones brillantes de los colores */
#define ANSI_BRIGHT_BLACK "\033[90m"
#define ANSI_BRIGHT_RED "\033[91m"
#define ANSI_BRIGHT_GREEN "\033[92m"
#define ANSI_BRIGHT_YELLOW "\033[93m"
#define ANSI_BRIGHT_BLUE "\033[94m"
#define ANSI_BRIGHT_MAGENTA "\033[95m"
#define ANSI_BRIGHT_CYAN "\033[96m"
#define ANSI_BRIGHT_WHITE "\033[97m"

/* Versiones brillantes de los fondos */
#define ANSI_BG_BRIGHT_BLACK "\033[100m"
#define ANSI_BG_BRIGHT_RED "\033[101m"
#define ANSI_BG_BRIGHT_GREEN "\033[102m"
#define ANSI_BG_BRIGHT_YELLOW "\033[103m"
#define ANSI_BG_BRIGHT_BLUE "\033[104m"
#define ANSI_BG_BRIGHT_MAGENTA "\033[105m"
#define ANSI_BG_BRIGHT_CYAN "\033[106m"
#define ANSI_BG_BRIGHT_WHITE "\033[107m"

/* Macros útiles para combinar colores */
#define SET_COLOR(fg, bg) "\033[" #fg ";" #bg "m"
#define SET_FG_COLOR(color) "\033[" #color "m"
#define SET_BG_COLOR(color) "\033[" #color "m"

/* Ejemplos de uso:
   printf(ANSI_RED ANSI_BG_YELLOW "Texto rojo sobre fondo amarillo" ANSI_RESET);
   printf(ANSI_BRIGHT_CYAN ANSI_BG_BLUE "Texto cian brillante sobre fondo azul"
   ANSI_RESET);
*/

#endif // ANSI_COLORS_H