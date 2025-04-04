#include <xinu.h>

void medir_stack(void *stack_base, uint32 stack_size)
{
    uint32 *ptr = (uint32 *)stack_base;
    uint32 bytes_usados = 0;

    // Recorrer el stack desde la base hasta el tope
    for (uint32 i = 0; i < stack_size / sizeof(uint32); i++)
    {
        if (ptr[i] != 0xDEADBEEF)
        {
            bytes_usados = stack_size - (i * sizeof(uint32));
            break;
        }
    }

    kprintf("Stack usado: %u bytes (de %u)\n", bytes_usados, stack_size);
}