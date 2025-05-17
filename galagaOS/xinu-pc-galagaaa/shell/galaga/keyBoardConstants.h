#ifndef KEYBOARD_CONSTANTS
#define KEYBOARD_CONSTANTS
// Definiciones de teclas para un teclado QWERTY (flanco positivo)
// Valores hexadecimales asignados secuencialmente, con BUTTON_j = 0x24

// Teclas alfabéticas (a-z)
#define BUTTON_a 0x1e
#define BUTTON_b 0x30
#define BUTTON_c 0x2e
#define BUTTON_d 0x20
#define BUTTON_e 0x12
#define BUTTON_f 0x21
#define BUTTON_g 0x22
#define BUTTON_h 0x23
#define BUTTON_i 0x17
#define BUTTON_j 0x24 // Asignado según tu ejemplo
#define BUTTON_k 0x25
#define BUTTON_l 0x26
#define BUTTON_m 0x32
#define BUTTON_n 0x31
#define BUTTON_o 0x18
#define BUTTON_p 0x19
#define BUTTON_q 0x10
#define BUTTON_r 0x13
#define BUTTON_s 0x1f
#define BUTTON_t 0x14
#define BUTTON_u 0x16
#define BUTTON_v 0x2f
#define BUTTON_w 0x11
#define BUTTON_x 0x2d
#define BUTTON_y 0x15
#define BUTTON_z 0x2c

// Teclas numéricas (0-9)
#define BUTTON_0 0xb
#define BUTTON_1 0x2
#define BUTTON_2 0x3
#define BUTTON_3 0x4
#define BUTTON_4 0x5
#define BUTTON_5 0x6
#define BUTTON_6 0x7
#define BUTTON_7 0x8
#define BUTTON_8 0x9
#define BUTTON_9 0xa

// Teclas de función (F1-F12)
#define BUTTON_F1 0x3b
#define BUTTON_F2 0x3c
#define BUTTON_F3 0x3d
#define BUTTON_F4 0x3e
#define BUTTON_F5 0x3f
#define BUTTON_F6 0x40
#define BUTTON_F7 0x41
#define BUTTON_F8 0x42
#define BUTTON_F9 0x43
#define BUTTON_F10 0x44
#define BUTTON_F11 0x57
#define BUTTON_F12 0x58

// Teclas de control
#define BUTTON_LEFT_SHIFT 0x2a
#define BUTTON_RIGHT_SHIFT 0x36
#define BUTTON_CTRL 0x1d
#define BUTTON_ALT 0x35
#define BUTTON_CAPS_LOCK 0x3a

// Teclas de navegación
#define BUTTON_UP_ARROW 0x48
#define BUTTON_DOWN_ARROW 0x50
#define BUTTON_LEFT_ARROW 0x4b
#define BUTTON_RIGHT_ARROW 0x4d

// Teclas especiales
#define BUTTON_ENTER 0x1c
#define BUTTON_SPACE 0x39
#define BUTTON_TAB 0xf
#define BUTTON_BACKSPACE 0xe
#define BUTTON_ESCAPE 0x1

// Teclas de puntuación y símbolos
#define BUTTON_COMMA 0x33        // ,
#define BUTTON_PERIOD 0x34       // .
#define BUTTON_SLASH 0x35        // /
#define BUTTON_BACKSLASH 0x2b    // carry
#define BUTTON_SEMICOLON 0x27    // ;
#define BUTTON_QUOTE 0x28        // '
#define BUTTON_LEFT_BRACKET 0x1a // [
#define BUTTON_RIGHT_BRACKET 0x1b // ]
#define BUTTON_MINUS 0xc        // -
#define BUTTON_EQUALS 0xd       // =
#define BUTTON_BACKTICK 0x29    // `

#endif