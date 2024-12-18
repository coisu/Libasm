#include <stdio.h>
#include <string.h>
#include "manual_tests.h"


int ft_strcmp(const char *s1, const char *s2);

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: ./manual_tests/ft_strcmp [string1] [string2]\n");
        return 1;
    }

    int ft_result = ft_strcmp(argv[1], argv[2]);
    int std_result = strcmp(argv[1], argv[2]);

    printf("%s@ %s \n@ %s%s\n+ %d\n", YELLOW, argv[1], argv[2], RESET, ft_result);
    printf("%s@ %s \n@ %s%s\n- %d\n", YELLOW, argv[1], argv[2], RESET, std_result);

    if ((ft_result == 0 && std_result == 0) || (ft_result < 0 && std_result < 0) || (ft_result > 0 && std_result > 0)) {
        printf("%s>> Success%s\n", GREEN, RESET);
    } else {
        printf("%s>> Failure%s\n", RED, RESET);
    }

    return 0;
}
