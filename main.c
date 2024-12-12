#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
// #include <limits.h>

size_t ft_strlen(const char *str);
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t read(int fd, void *buf, size_t count);

#define BUFFER_SIZE 2048
#define MAX_PRINT_LEN 100

int main() {
    const char *test_cases[] = {
        "Hello, World!",
        "0",
        "0",
        "",
        "1234567890",
        "A random string",
        "Spaces     ",
        "Special chars !@#$%^&*()",
        "\n",
        "Lorem ipsum dolor sit amet. Id doloribus culpa quo expedita galisum id natus expedita et eius accusamus est perferendis esse. Sit omnis consequatur aut tempore asperiores eos eveniet quos. Et perferendis esse hic aliquid cumque et beatae unde et molestiae explicabo est numquam quia et voluptatum iste. Sed enim quia nam possimus ipsa id molestiae voluptas ea similique libero ut architecto nisi in laboriosam veniam! Et consectetur placeat nam quam exercitationem ab consequatur optio id molestiae omnis et dolore commodi non voluptas earum non consequatur consequatur. Ea rerum ipsa non autem sunt non illum impedit quo enim voluptatibus qui eveniet voluptatibus. Qui sunt nisi et tempora alias et soluta similique qui labore obcaecati qui magnam placeat in ullam dolor ut quisquam galisum. Rem libero ducimus aut quas tempore vel dolor culpa.\n\nHic nulla veritatis et adipisci error ex fugit eaque. Est nesciunt itaque a facilis nisi eos animi obcaecati. Et fuga accusantium in laudantium mollitia eum reprehenderit enim qui voluptatem quae non dolorem internos. Qui quisquam error non dolor voluptas et quia molestias cum maiores vero et nostrum explicabo. Ut ducimus rerum et architecto facere est commodi exercitationem rem corporis neque in voluptates animi. Ab possimus consequatur id magni fugiat et delectus veniam qui iure sequi. Ut voluptate sequi eum obcaecati placeat non animi reiciendis eum molestiae totam. Et iure distinctio eos tempora tempora ea molestias omnis. Est harum tempore sed voluptas dolor et atque possimus aut autem doloremque. Est dolores excepturi ut molestiae quasi sed voluptatem praesentium? Non nostrum error qui quas nostrum sed doloremque quod.",
        NULL
    };

    const char *BOLD = "\033[1m";
    const char *RED = "\033[31m";
    const char *GREEN = "\033[32m";
    const char *YELLOW = "\033[33m";
    const char *RESET = "\033[0m";
    const char *BRIGHT_GREEN = "\033[2;32m"; 

    int i = 0;
    printf("\n\n");
    while (test_cases[i])
    {
        const char *str = test_cases[i++];
        printf("  Input string[%d]: \"%s%s%s\"\n", i, BOLD, str, RESET);
    }

// - STRLEN --------------------------------------------------------------------------
    printf("\n%sstrlen_\n%s", BOLD, RESET);
    i = 0;
    bool success = true;
    while (test_cases[i])
    {
        const char *str = test_cases[i];
        size_t custom_len = ft_strlen(str);
        size_t std_len = strlen(str);
        if (custom_len != std_len)
        {
            success = false;
            break;
        }
        i++;
    }
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);
    i = 0;
    while (test_cases[i])
    {
        const char *str = test_cases[i];
        size_t custom_len = ft_strlen(str);
        size_t std_len = strlen(str);

        // Print input string
        printf("%sTest case %d:%s\n", BOLD, i + 1, RESET);
        // printf("  Input string: \"%s%s%s\"\n", BOLD, str, RESET);

        // Result check
        if (custom_len != std_len) {
            printf("%s%s@ test failed%s\n", BOLD, RED, RESET);
            printf("  \t%s+%zu%s\n", YELLOW, std_len, RESET);  // Correct result
            printf("  \t%s-%zu%s\n", RED, custom_len, RESET); // Custom implementation result
        } else {
            printf("%s%s@ Success%s\n", BOLD, BRIGHT_GREEN, RESET);
        }
        printf("\n");

        i++;
    }

// - STRCPY --------------------------------------------------------------------------
    printf("\n%sstrcpy_\n%s", BOLD, RESET);
    i = 0;
    success = true;

    while (test_cases[i]) {
        const char *src = test_cases[i];
        char custom_dest[BUFFER_SIZE] = {0};
        char std_dest[BUFFER_SIZE] = {0};

        ft_strcpy(custom_dest, src);
        strcpy(std_dest, src);

        if (memcmp(custom_dest, std_dest, strlen(src) + 1) != 0) {
            success = false;
            break;
        }
        i++;
    }

    // Print overall test result
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);

    // Detailed test case results
    i = 0;
    while (test_cases[i]) {
        const char *src = test_cases[i];
        char custom_dest[BUFFER_SIZE] = {0};
        char std_dest[BUFFER_SIZE] = {0};

        ft_strcpy(custom_dest, src);
        strcpy(std_dest, src);
        printf("%s%sTest case %d:%s\n", RESET, BOLD, i + 1, RESET);

        if (memcmp(custom_dest, std_dest, strlen(src) + 1) != 0) {
            printf("%s%s@ Test failed%s\n", BOLD, RED, RESET);
            printf("  \t%s+ \"%.*s%s\"\n", 
                YELLOW, MAX_PRINT_LEN, std_dest, 
                strlen(std_dest) > MAX_PRINT_LEN ? "..." : "");
            printf("  \t%s- \"%.*s%s\"\n", 
                RED, MAX_PRINT_LEN, custom_dest, 
                strlen(custom_dest) > MAX_PRINT_LEN ? "..." : "");
        } else {
            printf("%s%s@ Success%s\n\n", BOLD, BRIGHT_GREEN, RESET);
        }

        // Debugging: Print ASCII values for more clarity
        // printf("  ASCII Comparison:\n");
        // for (size_t j = 0; j < strlen(src) + 1; ++j) {
        //     printf("  [%zu]: Expected=%02X Got=%02X\n", j, (unsigned char)std_dest[j], (unsigned char)custom_dest[j]);
        // }
        printf("\n");
        i++;
    }

// - STRCMP --------------------------------------------------------------------------
    printf("\n%sstrcmp_\n%s", BOLD, RESET);
    i = 0;
    success = true;
    
    while (test_cases[i + 1]) {
        const char *str1 = test_cases[i];
        const char *str2 = test_cases[(i + 1) % (sizeof(test_cases) / sizeof(test_cases[0]))];
        int custom_result = ft_strcmp(str1, str2);
        int std_result = strcmp(str1, str2);

        if (custom_result != std_result) {
            success = false;
            break;
        }
        i++;
    }

    // Print overall test result
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);

    // Detailed test case results
    i = 0;
    while (test_cases[i + 1]) {
        const char *str1 = test_cases[i];
        const char *str2 = test_cases[(i + 1) % (sizeof(test_cases) / sizeof(test_cases[0]))]; // 순환 비교
        int custom_result = ft_strcmp(str1, str2);
        int std_result = strcmp(str1, str2);

        printf("%sTest case %d:%s\n", BOLD, i + 1, RESET);
        // printf("  str1: \"%s\"\n", str1);
        // printf("  str2: \"%s\"\n", str2);

        if (custom_result != std_result) {
            printf("%s%s@ Test failed%s\n", BOLD, RED, RESET);
            printf("  \t%s+ %d%s\n", YELLOW, std_result, RESET);  // Correct result
            printf("  \t%s- %d%s\n", RED, custom_result, RESET); // Custom implementation result
        } else {
            printf("%s%s@ Success%s\n\n", BOLD, BRIGHT_GREEN, RESET);
        }
        i++;
    }

// - WRITE --------------------------------------------------------------------------
    printf("\n%swrite_\n%s", BOLD, RESET);
    i = 0;
    success = true;

    int fd = open("/dev/null", O_WRONLY); // Open /dev/null
    if (fd == -1) {
        return 1; // Handle error
    }
    while (test_cases[i]) {
        const char *msg = test_cases[i];
        ssize_t custom_result = ft_write(fd, msg, strlen(msg));
        ssize_t std_result = write(fd, msg, strlen(msg));

        if (custom_result != std_result) {
            success = false;
            break;
        }
        i++;
    }
    close(fd);
    // Print overall test result
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);

    i = 0;
    fd = open("ft_write_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    while (test_cases[i]) {
        const char *msg = test_cases[i];

        printf("%sTest case %d:%s\n", BOLD, i + 1, RESET);
        write(fd, "+ ", 2);
        ssize_t std_result = write(fd, msg, strlen(msg));
        write(fd, "\n- ", 3);
        ssize_t custom_result = ft_write(fd, msg, strlen(msg));
        write(fd, "\n\n", 2);

        if (custom_result != std_result) {
            printf("%s%s@ Test failed%s\n", BOLD, RED, RESET);
            // write(2, msg, strlen(msg));
            // write(2, "\n", 1);
            printf("  \t%s+ %ld%s\n", YELLOW, std_result, RESET);  // Correct result
            printf("  \t%s- %ld%s\n", RED, custom_result, RESET); // Custom implementation result
        } else {
            printf("%s%s@ Success%s\n\n", BOLD, BRIGHT_GREEN, RESET);
        }
        i++;
    }
    close(fd);
    printf("%sif you need more detail, check 'ft_write_outpit.txt'%s\n", YELLOW, RESET);


// - READ --------------------------------------------------------------------------
    printf("\n%sread_\n%s", BOLD, RESET);
    i = 0;
    success = true;

    const char *test_files[] = {
        "test1.txt",
        "test2.txt",
        "test3.txt",
        NULL
    };

    while (test_files[i])
    {
        const char *f = test_files[i];
        char *buf;
        size_t buf_size = 4096; // 0x100000000

        fd = open(f, O_RDONLY);
        if (fd == -1)
        {
            perror("Error opening file");
            i++;
            continue;
        }
        
        ssize_t custom_result = 0;
        ssize_t std_result = 0;

        while (buf_size > 0) 
        {
            buf = malloc(buf_size);
            if (!buf)
            {
                perror("Malloc failed");
                buf_size >>= 1;
                continue;
            }
            lseek(fd, 0, SEEK_SET);
            custom_result = ft_read(fd, buf, buf_size);
            lseek(fd, 0, SEEK_SET);
            std_result = read(fd, buf, buf_size);
            free(buf);
            if (custom_result == -1 || std_result == -1)
            {
                perror("Read failed");
                buf_size >>= 1;
            }
            else
                break;
        }
        close(fd);
        if (custom_result != std_result)
        {
            success = false;
            break;
        }
        i++;
    }
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);

    i = 0;
    while (test_files[i]) 
    {
    const char *f = test_files[i];
    char *buf;
    size_t buf_size = 4096; // 4 KB buffer size

    printf("%sTesting file: %s%s\n", BOLD, f, RESET);

    fd = open(f, O_RDONLY);
    if (fd == -1) 
    {
        perror("Error opening file");
        printf("%s%s@ Test failed: Unable to open file: %s%s\n", BOLD, RED, f, RESET);
        i++;
        continue;
    }

    ssize_t custom_result = 0;
    ssize_t std_result = 0;

    while (buf_size > 0) 
    {
        buf = malloc(buf_size);
        if (!buf) 
        {
            perror("Malloc failed");
            buf_size >>= 1;
            continue;
        }

        lseek(fd, 0, SEEK_SET);
        custom_result = ft_read(fd, buf, buf_size);
        lseek(fd, 0, SEEK_SET);
        std_result = read(fd, buf, buf_size);

        free(buf);

        if (custom_result == -1 || std_result == -1) 
        {
            perror("Read failed");
            buf_size >>= 1;
        } else 
            break;
    }

    close(fd);

    if (custom_result != std_result) 
    {
        printf("%s%s@ Test failed for file: %s%s\n", BOLD, RED, f, RESET);
        printf("  \t%s+ Standard: %ld bytes%s\n", YELLOW, std_result, RESET);
        printf("  \t%s- Custom: %ld bytes%s\n\n", RED, custom_result, RESET);
    } 
    else 
        printf("%s%s@ Success for file: %s%s\n\n", BOLD, BRIGHT_GREEN, f, RESET);
    i++;
}

// - STRDUP --------------------------------------------------------------------------
    printf("\n%sread_\n%s", BOLD, RESET);
    i = 0;
    success = true;

    const char *test_files[] = {
        "test1.txt",
        "test2.txt",
        "test3.txt",
        NULL
    };

    while (test_files[i])
    {
        const char *f = test_files[i];
        fd = open(f, O_RDONLY);
    }
}
