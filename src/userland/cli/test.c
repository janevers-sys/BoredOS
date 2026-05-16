#include <stdio.h>
#include <string.h>
#include <syscall.h>

int main(void) {
    char *paths[] = { "/bin", "/usr/bin" };
    int path_count = 2;
    char input[] = "re"; // pretend user typed "re"

    FAT32_FileInfo entries[128];

    for (int p = 0; p < path_count; p++) {
        int count = sys_list(paths[p], entries, 128);
        for (int i = 0; i < count; i++) {
            if (entries[i].is_directory) {
                continue;
            }
            char name[256];
            strncpy(name, entries[i].name, sizeof(name));

            // strip .elf
            int len = strlen(name);
            if (len > 4 && strcmp(name + len - 4, ".elf") == 0)
                name[len - 4] = 0;

            // check if starts with input
            if (strncmp(name, input, strlen(input)) == 0) {
                printf("found: %s\n", name);
            }
        }
    }

    return 0;
}