#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 1. Düzəliş: istifadədən sonra free() */
void leak(void) {
    char *p = malloc(100);
    if (p == NULL) return;
    strcpy(p, "salam");
    printf("%s\n", p);
    free(p);
}

/* 2. Düzəliş: əvvəl istifadə, sonra free(), sonra NULL */
void uaf(void) {
    int *p = malloc(sizeof(int));
    if (p == NULL) return;
    *p = 5;
    printf("%d\n", *p);
    free(p);
    p = NULL;
}

/* 3. Düzəliş: dövr sərhədi massivin ölçüsündən hesablanır */
void overflow(void) {
    int a[5];
    for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
        a[i] = (int)i;
    printf("%d\n", a[0]);
}

/* 4. Düzəliş: calloc yaddaşı sıfırla doldurur */
void uninit(void) {
    int *p = calloc(1, sizeof(int));
    if (p == NULL) return;
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
