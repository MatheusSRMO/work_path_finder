#include <stdio.h>
#include <stdlib.h>

int main() {
    
    int m, n;
    FILE* file = fopen("maze.txt", "r");
    fscanf(file, "%d %d", &m, &n);

    fclose(file);
    return 0;
}
