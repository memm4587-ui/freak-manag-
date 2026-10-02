#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

// функция сверху дабы мейн мог ее юзать
void cmd_cd(const char *path) {
    if (chdir(path) == 0) {
        printf("Перешли в: %s\n", path);
    } else {
        // Выведет красивую системную ошибку, если путь неверный
        perror("meow failed"); 
    }
}

int main(void) {
    // 1. запустились
    bool running = true;
    char input[256];
    char cwd[1024]; // Буфер для хранения пути текущей папки

    printf("Welcome on my Freak Manager!\n");
    printf("Type 'help' for commands, 'quit' to exit.\n\n");

    // 2. Главный цикл
    while (running) {
        // Для удобства: показываем, где мы сейчас находимся перед >
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("[%s] > ", cwd);
        } else {
            printf("> ");
        }

        // ридинг инпута
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Убираем \n в конце, если есть
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        // 3. Обработка команд (логика)
        if (strcmp(input, "quit") == 0 || strcmp(input, "exit") == 0) 
        {
            running = false;          
            continue;                 
        }
        else if (strcmp(input, "help") == 0) 
        {
            printf("Commands:\n");
            printf("  help      - show this help\n");
            printf("  clear     - clear screen\n");
            printf("  hello     - print a greeting\n");
            printf("  meow <path> - change directory\n"); // Добавили в хелп
            printf("  quit      - exit program\n");
        }
        else if (strcmp(input, "clear") == 0) 
        {
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
        else if (strcmp(input, "hello") == 0) 
        {
            printf("Hello, user!\n");
        }
        else if (strlen(input) == 0) {
            continue;
        }
        else if (strcmp(input, "freak") == 0) 
        {
           printf("yea bro, I'm a freak =)\n");
        }
        // --- Исправил ебучку---
        // Проверяем, начинается ли ввод с meow 
        else if (strncmp(input, "meow ", 3) == 0) 
        {
            // Берем адрес начала строки инпут и сдвигаем указатель на 3 символа вперед.
            const char *path = input + 3;  
            cmd_cd(path);
        }

        else
        {
            printf("Unknown command: %s\n", input);
        }
    }

    // 5. байбай
    printf("Bye!\n");
    return 0;
}

