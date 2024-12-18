#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "manual_tests.h"


ssize_t ft_write(int fd, const void *buf, size_t count);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./manual_tests/ft_write [test string]\n");
        return 1;
    }

    write(1, YELLOW, strlen(YELLOW));
    write(1, "@ ", 2);
    ssize_t std_result = write(1, argv[1], strlen(argv[1]));
    write(1, RESET, strlen(RESET));
    write(1, "\n", 1);
    printf("+ %zd\n", std_result);

    write(1, YELLOW, strlen(YELLOW));
    write(1, "@ ", 2);
    ssize_t ft_result = ft_write(1, argv[1], strlen(argv[1]));
    write(1, RESET, strlen(RESET));
    write(1, "\n", 1);
    printf("- %zd\n", ft_result);

    if (ft_result == std_result) {
        printf("%s>> Success%s\n", GREEN, RESET);
    } else {
        printf("%s>> Failure%s\n", RED, RESET);
    }

    return 0;
}
