#include <ANSI.h>
#include <xinu.h>
// Prototipos

int longitudInt(int a[]);
int setValorFila(int dir, int cantidad, int *a[]);

xsh_NIM() {
    int filas[] = {1, 3, 5, 7};
    kprintf(aCLEAR);

    renderArray(filas, 5, 5);
}

int longitudInt(int a[]) { return (sizeof(a) / sizeof(a[0])); }

int setValorFila(int dir, int cantidad, int *a[]) {
    int exito =
        (dir <= (longitudInt(a) - 1) && dir >= 0) && (cantidad > 0 && cantidad <= a[dir]);
    if (exito) {
        a[dir] -= cantidad;
    }
    return exito;
}

int renderArray(int a[], int x, int y) {
    for (int dir = 0; dir < longitudInt(a); dir++) {
        for (int veces = 0; veces < a[dir]; veces++) {
            aPOS(x + veces, y + dir);
            kprintf("🔴");
        }
    }

    return 1;
}
