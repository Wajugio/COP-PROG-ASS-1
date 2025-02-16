#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        char input[256];
        printf("Enter text: ");
        if (fgets(input, sizeof(input), stdin)) {
            for (int i = 0; input[i] != '\0'; i++) {
                input[i] = toupper((unsigned char) input[i]);
            }
            printf("%s", input);
        }
    } else {
        for (int i = 1; i < argc; i++) {
            for (int j = 0; argv[i][j] != '\0'; j++) {
                argv[i][j] = toupper((unsigned char) argv[i][j]);
            }
            printf("%s ", argv[i]);
        }
        printf("\n");
    }
    return 0;
}
