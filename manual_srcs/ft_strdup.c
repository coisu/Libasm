#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *ft_strdup(const char *s);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./manual_tests/ft_strdup [test string]\n");
        return 1;
    }

    char *dup = ft_strdup(argv[1]);
    if (!dup) {
        perror("ft_strdup error");
        return 1;
    }

    printf("Original string: '%s'\n", argv[1]);
    printf("Duplicated string: '%s'\n", dup);
    free(dup);
    return 0;
}
