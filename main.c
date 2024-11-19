#include <stdio.h>
#include <string.h>
#include <stdbool.h>

size_t ft_strlen(const char *str);

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
    const char *RESET = "\033[0m"; 

// - STRLEN --------------------------------------------------------------------------
    printf("\n%sstrlen_\n%s", BOLD, RESET);
    int i = 0;
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
        printf("  Input string: \"%s%s%s\"\n", BOLD, str, RESET);

        // Result check
        if (custom_len != std_len) {
            printf("%s%s@ test failed%s\n", BOLD, RED, RESET);
            printf("  \t%s+%zu%s\n", RED, std_len, RESET);  // Correct result
            printf("  \t%s-%zu%s\n", RED, custom_len, RESET); // Custom implementation result
        } else {
            printf("%s%s@ Success: Results match.%s\n", BOLD, GREEN, RESET);
        }
        printf("\n");

        i++;
    }

// - STRCPY --------------------------------------------------------------------------

    return 0;
}
