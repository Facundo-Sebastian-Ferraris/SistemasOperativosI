/* shell.c  -  shell */

#include "shprototypes.h"
#include <xinu.h>

/************************************************************************/
/* Table of Xinu shell commands and the function associated with each	*/
/************************************************************************/
const struct cmdent cmdtab[] = {
    {"argecho", TRUE, xsh_argecho},            // 0
    {"arp", FALSE, xsh_arp},                   // 1
    {"cat", FALSE, xsh_cat},                   // 2
    {"clear", TRUE, xsh_clear},                // 3
    {"date", FALSE, xsh_date},                 // 4
    {"devdump", FALSE, xsh_devdump},           // 5
    {"echo", FALSE, xsh_echo},                 // 6
    {"exit", TRUE, xsh_exit},                  // 7
    {"help", FALSE, xsh_help},                 // 8
    {"kill", TRUE, xsh_kill},                  // 9
    {"memdump", FALSE, xsh_memdump},           // 10
    {"memstat", FALSE, xsh_memstat},           // 11
    {"netinfo", FALSE, xsh_netinfo},           // 12
    {"ping", FALSE, xsh_ping},                 // 13
    {"ps", FALSE, xsh_ps},                     // 14
    {"sleep", FALSE, xsh_sleep},               // 15
    {"udp", FALSE, xsh_udpdump},               // 16
    {"udpecho", FALSE, xsh_udpecho},           // 17
    {"udpeserver", FALSE, xsh_udpeserver},     // 18
    {"uptime", FALSE, xsh_uptime},             // 19
    {"?", FALSE, xsh_help},                    // 20
    {"hm", FALSE, xsh_ahorcado},               // 21
    {"programita", FALSE, xsh_mi_programa},    // 22
    {"procesos", FALSE, xsh_intro_procesos},   // 23
    {"procesos2", FALSE, xsh_intro_procesos2}, // 24
    {"procesos3", FALSE, xsh_intro_procesos3}, // 25
    {"primos", FALSE, xsh_primos},             // 26

};

uint32 ncmd = sizeof(cmdtab) / sizeof(struct cmdent);
