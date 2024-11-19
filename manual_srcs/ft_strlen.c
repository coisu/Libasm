#include <stdio.h>
#include <string.h>

size_t ft_strlen(const char *str);

int main(int argc, char **argv) {
    if (argc != 2)
    {
        printf("Usage: .test_strlen.o [test string]\n");
        return 1;
    }
    
    size_t length = ft_strlen((const char *)argv[1]);
    printf("Length of string '%s': %zu\n", argv[1], length);
    
    return 0;
}