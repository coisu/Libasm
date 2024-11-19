#include <stdio.h>
#include <string.h>
#include <stdbool.h>

size_t ft_strlen(const char *str);
char *ft_strcpy(char *dest, const char *src);

#define BUFFER_SIZE 2048
#define MAX_PRINT_LEN 100

int main() {
    const char *test_cases[] = {
        "Hello, World!",
        "0",
        "",
        "Lorem ipsum dolor sit amet. Id doloribus culpa quo expedita galisum id natus expedita et eius accusamus est perferendis esse. Sit omnis consequatur aut tempore asperiores eos eveniet quos. Et perferendis esse hic aliquid cumque et beatae unde et molestiae explicabo est numquam quia et voluptatum iste. Sed enim quia nam possimus ipsa id molestiae voluptas ea similique libero ut architecto nisi in laboriosam veniam! Et consectetur placeat nam quam exercitationem ab consequatur optio id molestiae omnis et dolore commodi non voluptas earum non consequatur consequatur. Ea rerum ipsa non autem sunt non illum impedit quo enim voluptatibus qui eveniet voluptatibus. Qui sunt nisi et tempora alias et soluta similique qui labore obcaecati qui magnam placeat in ullam dolor ut quisquam galisum. Rem libero ducimus aut quas tempore vel dolor culpa.\n\nHic nulla veritatis et adipisci error ex fugit eaque. Est nesciunt itaque a facilis nisi eos animi obcaecati. Et fuga accusantium in laudantium mollitia eum reprehenderit enim qui voluptatem quae non dolorem internos. Qui quisquam error non dolor voluptas et quia molestias cum maiores vero et nostrum explicabo. Ut ducimus rerum et architecto facere est commodi exercitationem rem corporis neque in voluptates animi. Ab possimus consequatur id magni fugiat et delectus veniam qui iure sequi. Ut voluptate sequi eum obcaecati placeat non animi reiciendis eum molestiae totam. Et iure distinctio eos tempora tempora ea molestias omnis. Est harum tempore sed voluptas dolor et atque possimus aut autem doloremque. Est dolores excepturi ut molestiae quasi sed voluptatem praesentium? Non nostrum error qui quas nostrum sed doloremque quod.",
        "1234567890",
        "A random string",
        "Spaces     ",
        "Special chars !@#$%^&*()",
        "\n",
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

    return 0;
}
