#include <proj.h>

int prac_21_main(Arena* arena, String_View file)
{
    (void)arena;

    int decrypt_mode = { 0 };
    int key          = { 0 };

    SV_SCAN(file, 2, "%d %d", &decrypt_mode, &key);

    if (decrypt_mode) {
        key = 26 - key;
    }

    // CEASER CIPHER
    for (uint64_t i = 0; i < file.len; i++) {
        if      (file.data[i] == ' ' || file.data[i] == '\n')   putchar(file.data[i]);
        else if (file.data[i] >= 'a' && file.data[i] <= 'z')    putchar(((file.data[i] - 'a' + key) % 26) + 'a');
        else if (file.data[i] >= 'A' && file.data[i] <= 'Z')    putchar(((file.data[i] - 'A' + key) % 26) + 'A');
        else                                                    assert(0 && "ONLY ALPHABETS EXPECTED!");
    }

    putchar('\n');
    return 0;
}
