#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 1. Yaddaş sızması: malloc var, free yoxdur */
void leak(void) {
    char *p = malloc(100);
    strcpy(p, "salam");
    printf("%s\n", p);
}

/* 2. Use-after-free: azad edilmiş yaddaşa müraciət */
void uaf(void) {
    int *p = malloc(sizeof(int));
    *p = 5;
    free(p);
    printf("%d\n", *p);
}

/* 3. Massiv sərhədindən kənara yazılma: a[5] mövcud deyil */
void overflow(void) {
    int a[5];
    for (int i = 0; i <= 5; i++)
        a[i] = i;
    printf("%d\n", a[0]);
}

/* 4. İlkin qiymət verilməmiş yaddaşın oxunması */
void uninit(void) {
    int *p = malloc(sizeof(int));
    if (*p > 10)
        printf("boyuk\n");
    else
        printf("kicik\n");
    free(p);
}

int main(int argc, char **argv) {
    int m = argc > 1 ? atoi(argv[1]) : 0;
    if (m == 1) leak();
    else if (m == 2) uaf();
    else if (m == 3) overflow();
    else if (m == 4) uninit();
    else printf("istifade: ./vuln 1|2|3|4\n");
    return 0;
}
