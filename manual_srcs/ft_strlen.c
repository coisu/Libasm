#include <stdio.h>
#include <string.h>
#include "manual_tests.h"


size_t ft_strlen(const char *str);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./manual_tests/ft_strlen [test string]\n");
        return 1;
    }

    size_t ft_result = ft_strlen(argv[1]);
    size_t std_result = strlen(argv[1]);

    printf("%s@ %s%s\n", YELLOW, argv[1], RESET);
    printf("+ %zu\n", std_result);
    printf("%s@ %s%s\n", YELLOW, argv[1], RESET);
    printf("- %zu\n", ft_result);


    if (ft_result == std_result) {
        printf("%s>> Success%s\n", GREEN, RESET);
    } else {
        printf("%s>> Failure%s\n", RED, RESET);
    }

    return 0;
}
