#include <stdio.h>
#include <string.h>

int ft_strcmp(const char *s1, const char *s2);

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: ./manual_tests/ft_strcmp [string1] [string2]\n");
        return 1;
    }

    int result = ft_strcmp(argv[1], argv[2]);
    printf("ft_strcmp('%s', '%s') = %d\n", argv[1], argv[2], result);
    return 0;
}
