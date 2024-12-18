#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "manual_tests.h"


ssize_t ft_read(int fd, void *buf, size_t count);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./manual_tests/ft_read [test file path]\n");
        return 1;
    }

    char ft_buffer[1024], std_buffer[1024];
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    ssize_t ft_result = ft_read(fd, ft_buffer, sizeof(ft_buffer) - 1);
    ft_buffer[ft_result] = '\0';

    lseek(fd, 0, SEEK_SET); // Reset file offset

    ssize_t std_result = read(fd, std_buffer, sizeof(std_buffer) - 1);
    std_buffer[std_result] = '\0';

    close(fd);

    printf("%s@ %s%s\n+ %zd\n\n", YELLOW, std_buffer, RESET, std_result);
    printf("%s@ %s%s\n- %zd\n", YELLOW, ft_buffer, RESET, ft_result);

    if (ft_result == std_result && strcmp(ft_buffer, std_buffer) == 0) {
        printf("%s>> Success%s\n", GREEN, RESET);
    } else {
        printf("%s>> Failure%s\n", RED, RESET);
    }

    return 0;
}
