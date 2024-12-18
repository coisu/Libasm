#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "manual_tests.h"


char *ft_strdup(const char *s);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./manual_tests/ft_strdup [test string]\n");
        return 1;
    }

    char *ft_result = ft_strdup(argv[1]);
    char *std_result = strdup(argv[1]);

    printf("%s@ %s%s\n", YELLOW, argv[1], RESET);
    printf("+ %s\n", std_result);
    printf("%s@ %s%s\n", YELLOW, argv[1], RESET);
    printf("- %s\n", ft_result);

    if (strcmp(ft_result, std_result) == 0) {
        printf("%s>> Success%s\n", GREEN, RESET);
    } else {
        printf("%s>> Failure%s\n", RED, RESET);
    }

    free(ft_result);
    free(std_result);
    return 0;
}
