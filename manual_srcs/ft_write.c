#include <unistd.h>
#include <stdio.h>
#include <string.h>

ssize_t ft_write(int fd, const void *buf, size_t count);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./manual_tests/ft_write [test string]\n");
        return 1;
    }

    ssize_t ret = ft_write(1, argv[1], strlen(argv[1])); // Write to stdout
    ft_write(1, "\n", 1); // Add newline after the output

    if (ret < 0) {
        perror("ft_write error");
        return 1;
    }

    printf("ft_write wrote %zd bytes\n", ret);
    return 0;
}
