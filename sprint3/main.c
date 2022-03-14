#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
    // Ensures that 2 command-line arguments are supplied.
    if (argc < 3) {
        fprintf(stderr, "usage: %s <filename> <action>\n", argv[0]);
        return 1;
    }
    FILE *fread;
    FILE *fwrite;
    fread = fopen(argv[1], "r");
    fwrite = fopen(argv[2], "w");
    if (fread == NULL || fwrite == NULL) {
        fprintf(stderr, "File open failure");
        return 0;
    }
    char line[256];
    //%[^\n]
    while (fgets(line, 256, fread) != NULL) {
        //fprintf(fwrite, "%s", line);
        char c;
        if (line[0] != '<' && strlen(line) > 1){
            fprintf(fwrite, "%s", line);
        } else if (strncmp("<title>", line, strlen("<title>")) == 0) {
            //printf("%s", line);           -> this line was not commented in my submission
            for (int i = strlen("<title>"); i < strlen(line); i++) {
                if (line[i] == '<') {
                    fputc('\n', fwrite);
                    break;
                }
                printf("%c", line[i]);
                fputc(line[i], fwrite);
            }
            //fputc('\n', fwrite);
        } else if (strncmp("<h1>", line, strlen("<h1>")) == 0) {
            //printf("%s", line);          -> this line was not commented in my submission
            for (int i = strlen("<h1>"); i < strlen(line); i++){
                if(line[i] == '<'){
                    fputc('\n', fwrite);
                    break;
                }
                printf("%c", line[i]);
                fputc(line[i], fwrite);
            }
            //fputc('\n', fwrite);
        } else if (strncmp("<h2>", line, strlen("<h2>")) == 0) {
            //printf("%s", line);         -> this line was not commented in my submission
            for (int i = strlen("<h2>"); i < strlen(line); i++){
                if(line[i] == '<'){
                    fputc('\n', fwrite);
                    break;
                }
                //printf("%c", line[i]);
                fputc(line[i], fwrite);
            }
            //fputc('\n', fwrite);
        } else if (strncmp("<h3>", line, strlen("<h3>")) == 0){
            //printf("%s", line);        -> this line was not commented in my submission
            for (int i = strlen("<h3>"); i < strlen(line); i++){
                if(line[i] == '<'){
                    fputc('\n', fwrite);
                    break;
                }
                printf("%c", line[i]);
                fputc(line[i], fwrite);
            }
            //fputc('\n', fwrite);
        } else if (strncmp("<h4>", line, strlen("<h4>")) == 0){
            //printf("%s", line);         -> this line was not commented in my submission
            for (int i = strlen("<h4>"); i < strlen(line); i++){
                if(line[i] == '<'){
                    fputc('\n', fwrite);
                    break;
                }
                printf("%c", line[i]);
                fputc(line[i], fwrite);
            }
            //fputc('\n', fwrite);
        } else if (strncmp("<h5>", line, strlen("<h5>")) == 0){
            //printf("%s", line);         -> this line was not commented in my submission
            for (int i = strlen("<h5>"); i < strlen(line); i++){
                if(line[i] == '<'){
                    fputc('\n', fwrite);
                    break;
                }
                printf("%c", line[i]);
                fputc(line[i], fwrite);
            }
            //fputc('\n', fwrite);
        } else if (strncmp("<h6>", line, strlen("<h6>")) == 0){
            //printf("%s", line);        -> this line was not commented in my submission
            for (int i = strlen("<h6>"); i < strlen(line); i++){
                if(line[i] == '<'){
                    fputc('\n', fwrite);
                    break;
                }
                printf("%c", line[i]);
                fputc(line[i], fwrite);
            }
            //fputc('\n', fwrite);
        } else if (strncmp("<p>", line, strlen("<p>")) == 0){
            //printf("%s", line);       -> this line was not commented in my submission
            for (int i = strlen("<p>"); i < strlen(line); i++){
                if(line[i] == '<'){
                    fputc('\n', fwrite);
                    break;
                }
                printf("%c", line[i]);
                fputc(line[i], fwrite);
            }
            //fputc('\n', fwrite);
        }
    }

    return 0;


}
