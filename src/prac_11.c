#include <proj.h>

int prac_11_main(Arena* arena, String_View file)
{
    (void)arena;

    printf("\n| CH | AND |  OR | XOR |");
    printf("\n|----|-----|-----|-----|");

    for (uint8_t i = 0; i < file.len; i++) {
        printf("\n| %2c | %3d | %3d | %3d |",
            file.data[i],
            file.data[i] & 127,
            file.data[i] | 127,
            file.data[i] ^ 127);
    }

    printf("\n|----|-----|-----|-----|\n");

    return 0;
}
