#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *line1 = "Welcome on Freak Machine!";
    const char *line2 = "Waiting for your command...";

    printf("%s\n", line1);
    printf("%s\n", line2);
    printf("> ");

    char input[100];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        #ifdef __linux__
            system("clear");
        #endif
    }

    return 0;
}
