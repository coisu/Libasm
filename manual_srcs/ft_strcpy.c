#include <stdio.h>
#include <string.h>

char *ft_strcpy(char *dst, const char *src);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./manual_tests/ft_strcpy [test string]\n");
        return 1;
    }

    char buffer[1024]; // Ensure the buffer is large enough
    ft_strcpy(buffer, argv[1]);

    printf("Original string: '%s'\n", argv[1]);
    printf("Copied string: '%s'\n", buffer);
    return 0;
}
