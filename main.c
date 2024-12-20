#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
// #include <limits.h>

size_t ft_strlen(const char *str);
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);

#define BUFFER_SIZE 2048
#define MAX_PRINT_LEN 100

int main() {
    const char *test_cases[] = {
        "Hello, World!",
        "0",
        "000\0",
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

        printf("%sTest case %d:%s\n", BOLD, i + 1, RESET);
        // printf("  Input string: \"%s%s%s\"\n", BOLD, str, RESET);
        
        // Result check
        if (custom_len != std_len) {
            success = false;
            printf("%s%s@ test failed%s\n", BOLD, RED, RESET);
            printf("  \t%s+%zu%s\n", YELLOW, std_len, RESET);
            printf("  \t%s-%zu%s\n", RED, custom_len, RESET);
        } else {
            printf("%s%s@ Success%s\n", BOLD, BRIGHT_GREEN, RESET);
        }
        printf("\n");

        i++;
    }
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);
    i = 0;
    

// - STRCPY --------------------------------------------------------------------------
    printf("\n%sstrcpy_\n%s", BOLD, RESET);
    i = 0;
    success = true;

    while (test_cases[i]) {
        const char *src = test_cases[i];
        char *custom_dest = malloc(sizeof(char) * (strlen(src) + 1));
        char *std_dest = malloc(sizeof(char) * (strlen(src) + 1));

        ft_strcpy(custom_dest, src);
        strcpy(std_dest, src);
        printf("%s%sTest case %d:%s\n", RESET, BOLD, i + 1, RESET);

        if (strcmp(custom_dest, std_dest) != 0) {
            success = false;
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
        
        free(custom_dest);
        free(std_dest);

        printf("\n");
        i++;
    }

    // Print overall test result
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);


// - STRCMP --------------------------------------------------------------------------
    printf("\n%sstrcmp_\n%s", BOLD, RESET);
    i = 0;
    success = true;

    while (test_cases[i]) {
        const char *str1 = test_cases[i];
        const char *str2 = test_cases[(i + 1) % (sizeof(test_cases) / sizeof(test_cases[0]) - 1)];

        printf("%sTest case %d:%s\n", BOLD, i + 1, RESET);

        // 1. Test same string comparison
        int custom_result_same = ft_strcmp(str1, str1);
        int std_result_same = strcmp(str1, str1);

        if (custom_result_same != std_result_same) {
            success = false;
            printf("%s%s@ Same string test failed%s\n", BOLD, RED, RESET);
            // printf("  str1: \"%s\"\n", str1);
            // printf("  str2: \"%s\"\n", str1);
            printf("  \t%s+ %d%s\n", YELLOW, std_result_same, RESET);
            printf("  \t%s- %d%s\n", RED, custom_result_same, RESET);
        } else {
            printf("%s%s@ Same string test passed%s\n", BOLD, BRIGHT_GREEN, RESET);
        }

        // 2. Test different string comparison
        int custom_result_diff = ft_strcmp(str1, str2);
        int std_result_diff = strcmp(str1, str2);

        if (custom_result_diff != std_result_diff) {
            success = false;
            printf("%s%s@ Different string test failed%s\n", BOLD, RED, RESET);
            // printf("  str1: \"%s\"\n", str1);
            // printf("  str2: \"%s\"\n", str2);
            printf("  \t%s+ %d%s\n", YELLOW, std_result_diff, RESET);
            printf("  \t%s- %d%s\n", RED, custom_result_diff, RESET);
        } else {
            printf("%s%s@ Different string test passed%s\n", BOLD, BRIGHT_GREEN, RESET);
        }

        printf("\n");
        i++;
    }

    // Print overall test result
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);

// - WRITE --------------------------------------------------------------------------
    printf("\n%swrite_\n%s", BOLD, RESET);
    i = 0;
    success = true;

    // Define test cases for invalid file descriptors
    const int invalid_fds[] = {-1, 9999}; // -1 is an invalid fd; 9999 is likely not a valid open fd

    // Open a file descriptor for writing test cases
    int fd = open("ft_write_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Test normal cases
    while (test_cases[i]) {
        const char *msg = test_cases[i];

        printf("%sTest case %d:%s\n", BOLD, i + 1, RESET);
        write(fd, "+ ", 2);
        ssize_t std_result = write(fd, msg, strlen(msg));
        write(fd, "\n- ", 3);
        ssize_t custom_result = ft_write(fd, msg, strlen(msg));
        write(fd, "\n\n", 2);

        if (custom_result != std_result) {
            success = false;
            printf("%s%s@ Test failed%s\n", BOLD, RED, RESET);
            printf("  \t%s+ %ld%s\n", YELLOW, std_result, RESET);
            printf("  \t%s- %ld%s\n", RED, custom_result, RESET);
        } else {
            printf("%s%s@ Success%s\n\n", BOLD, BRIGHT_GREEN, RESET);
        }
        i++;
    }

    // Test cases for invalid file descriptors
    for (size_t j = 0; j < sizeof(invalid_fds) / sizeof(invalid_fds[0]); j++) {
        printf("%sTest case for invalid fd %d:%s\n", BOLD, invalid_fds[j], RESET);
        ssize_t custom_result = ft_write(invalid_fds[j], "Testing error handling", 21); // Attempt to write

        if (custom_result == -1) {
            printf("%s@ Success: Correctly handled invalid fd%s\n", BOLD, RESET);
        } else {
            success = false;
            printf("%s@ Failure: Expected -1, got %ld%s\n", BOLD, custom_result, RESET);
        }
    }

    // Test with a closed file descriptor
    int fd_closed = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    close(fd_closed); // Close the file descriptor
    printf("%sTest case for closed fd:%s\n", BOLD, RESET);
    ssize_t custom_result = ft_write(fd_closed, "This should fail", 15); // Attempt to write after closing

    if (custom_result == -1) {
        printf("%s@ Success: Correctly handled closed fd%s\n", BOLD, RESET);
    } else {
        success = false;
        printf("%s@ Failure: Expected -1, got %ld%s\n", BOLD, custom_result, RESET);
    }

    // Clean up
    close(fd);
    printf("%sif you need more detail, check 'ft_write_output.txt'%s\n", YELLOW, RESET);

    // Print overall test result
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);

    i = 0;

    

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
            success = false;
            printf("%s%s@ Test failed for file: %s%s\n", BOLD, RED, f, RESET);
            printf("  \t%s+ Standard: %ld bytes%s\n", YELLOW, std_result, RESET);
            printf("  \t%s- Custom  : %ld bytes%s\n\n", RED, custom_result, RESET);
        } 
        else 
            printf("%s%s@ Success for file: %s%s\n\n", BOLD, BRIGHT_GREEN, f, RESET);
        i++;
    }
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);

    

// - STRDUP --------------------------------------------------------------------------
    printf("\n%sstrdup_\n%s", BOLD, RESET);
    i = 0;
    success = true;

    while (test_cases[i]) {
        char *src = (char *)test_cases[i];
        char *ft_d = ft_strdup(src);
        char *std_d = strdup(src);

        printf("%s%sTest case %d:%s\n", RESET, BOLD, i + 1, RESET);

        if (strcmp(ft_d, std_d) != 0) {
            success = false;
            printf("%s%s@ Test failed%s\n", BOLD, RED, RESET);
            printf("  \t%s+ \"%.*s%s\"\n", 
                YELLOW, MAX_PRINT_LEN, std_d, 
                strlen(std_d) > MAX_PRINT_LEN ? "..." : "");
            printf("  \t%s- \"%.*s%s\"\n", 
                RED, MAX_PRINT_LEN, ft_d, 
                strlen(ft_d) > MAX_PRINT_LEN ? "..." : "");
        } else {
            printf("%s%s@ Success%s\n", BOLD, BRIGHT_GREEN, RESET);
        }
        free(ft_d);
        free(std_d);
        printf("\n");
        i++;
    }

    // Print overall test result
    if (success)
        printf("%s%s>>>>>>>>>>>>>>> SUCCESS <<<<<<<<<<<<<<<%s\n", BOLD, GREEN, RESET);
    else
        printf("%s%s>>>>>>>>>>>>>>> FAILURE <<<<<<<<<<<<<<<%s\n", BOLD, RED, RESET);


}
