#ifndef PROJ
#define PROJ

#include <Utils/cmd_line.h>
#include <Utils/files.h>
#include <stdio.h>

#define COLOR_WHITE_ "\033[47m"
#define COLOR_BLACK_ "\033[40m"
#define COLOR_RED___ "\033[41m"
#define COLOR_GREEN_ "\033[42m"
#define COLOR_YELLOW "\033[43m"
#define COLOR_BLUE__ "\033[44m"
#define COLOR_RESET_ "\033[0m "

#define CLEAR_SCREEN "\033[2J "
#define CURSOR_RESET "\033[H  "

int prac_1_main(Arena* arena, String_View file);
int prac_11_main(Arena* arena, String_View file);
int prac_21_main(Arena* arena, String_View file);

#endif
