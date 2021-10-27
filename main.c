#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
    setbuf(stdout, 0);
    lista_agenda *lst;

    lst = cria_lista(4, 4);
    menu(lst);

    printf("\n");
    free(lst);
    return 0;
}

