
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/ed/deque.h"

typedef struct
{
    int x, y;
} Celula;

Celula *celula_create(int x, int y)
{
    Celula *c = malloc(sizeof(Celula));
    c->x = x;
    c->y = y;
    return c;
}

void celula_free(Celula *c)
{
    free(c);
}

void celula_print(void *c)
{   
    Celula *cel = (Celula*) c;
    printf("(%d, %d)", cel->x, cel->y);
}

int main()
{
    int i, n, x, y;
    char cmd[10];
    Deque *d = deque_create();

    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        scanf("\n%s", cmd);

        if (!strcmp(cmd, "PUSH_BACK"))
        {
            scanf("%d %d", &x, &y);
            printf("PUSH_BACK: %d %d\n", x, y);
            deque_push_back(d, celula_create(x, y));
            print_deque(d, celula_print);
        }
        else if (!strcmp(cmd, "PUSH_FRONT"))
        {
            scanf("%d %d", &x, &y);
            printf("PUSH_FRONT: %d %d\n", x, y);
            deque_push_front(d, celula_create(x, y));
            print_deque(d, celula_print);
        }
        else if (!strcmp(cmd, "POP_BACK"))
        {
            printf("POP_BACK: ");
            Celula *c = deque_pop_back(d);
            printf("%d %d\n", c->x, c->y);
            print_deque(d, celula_print);
            celula_free(c);
        }
        else if (!strcmp(cmd, "POP_FRONT"))
        {
            printf("POP_FRONT: ");
            Celula *c = deque_pop_front(d);
            printf("%d %d\n", c->x, c->y);
            print_deque(d, celula_print);
            celula_free(c);
        }
    }

    deque_destroy(d);
    return 0;
}
