#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

ssize_t ft_read(int fd, void *buf, size_t count);

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ./manual_tests/ft_read [test file path]\n");
        return 1;
    }

    char buffer[1024];
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    ssize_t ret = ft_read(fd, buffer, sizeof(buffer) - 1);
    if (ret < 0) {
        perror("ft_read error");
        close(fd);
        return 1;
    }

    buffer[ret] = '\0'; // Null-terminate the string
    printf("ft_read read %zd bytes:\n%s\n", ret, buffer);
    close(fd);
    return 0;
}
