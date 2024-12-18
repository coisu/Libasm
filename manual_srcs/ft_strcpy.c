#include <stdio.h>
#include <string.h>
#include "manual_tests.h"


char *ft_strcpy(char *dst, const char *src);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./manual_tests/ft_strcpy [test string]\n");
        return 1;
    }

    char ft_buffer[1024], std_buffer[1024];
    ft_strcpy(ft_buffer, argv[1]);
    strcpy(std_buffer, argv[1]);

    printf("%s@ %s%s\n", YELLOW, argv[1], RESET);
    printf("+ %s\n", std_buffer);
    printf("%s@ %s%s\n", YELLOW, argv[1], RESET);
    printf("- %s\n", ft_buffer);

    if (strcmp(ft_buffer, std_buffer) == 0) {
        printf("%s>> Success%s\n", GREEN, RESET);
    } else {
        printf("%s>> Failure%s\n", RED, RESET);
    }

    return 0;
}
