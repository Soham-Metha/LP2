#define UTILS_CLI_IMPL
#define STRING_VIEW_IMPL
#define MEM_MANAGER_IMPL
#define UTILS_FILES_IMPL
#include <proj.h>

int main(int argc, char** argv)
{
    cli_flag_push("--prac", "Practical No. to be executed");
    cli_flag_push("-i", "input testcase file");
    cli_parse(&argc, &argv);

    String_View prac_no = cli_flag_get_val(STR("--prac"));
    String_View file_nm = cli_flag_get_val(STR("-i"));

    Arena arena         = { 0 };
    String_View file    = file_unwrap(arena_file_open_into_sv(&arena, file_nm.data));

    switch (sv_to_uint(&prac_no)) {
    case 1:
        return prac_1_main(&arena, file);
    case 11:
        return prac_11_main(&arena, file);
    case 21:
        return prac_21_main(&arena, file);
    }

    arena_free(&arena);
    return 0;
}
