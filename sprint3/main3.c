//with recursion
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void processTag (char* line, FILE * fwrite) {
    const char* rectags [10] = {"h1", "h2", "h3", "h4", "h5", "h6", "title", "p", "b", "strong"};
    char* endtag = "";
    char* newline = "";
    char newtag[1000];
    int count = 0;
    if (strncmp("<h1>", line, strlen("<h1>")) == 0) {
        endtag = "\\h1";
        for (int i = strlen("<h1>"); i < strlen(line); i++){
            if (line[i] == '<') {
                for (int j = i + 1; j < strlen(line); j++){
                    if (line[j] != '>') {
                        //TODO : fix concatenation
                        newtag[count++] = line[j];
                    } else {
                        newtag[count] = '\0';
                        printf("newtag: %s\n", newtag);
                        if (strcmp(newtag, endtag) == 0){
                            fputc('\n', fwrite);
                        } else {
                            int c = 0;
                            while (c < strlen(line)) {
                                newline[c] = line[(i)+c];
                                c++;
                            }
                            printf("newline: %s\n", newline);
                            for (int i = 0; i < 10; i++){
                                if (strcmp(newtag, rectags[i])){
                                    processTag(newline, fwrite);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
                break;
            } else {
                newline = line;
                //processTag(newline);
            }
            //printf("%c", line[i]);
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
    } else if (strncmp("<p>", line, strlen("<p>")) == 0) {
        //printf("%s", line);       -> this line was not commented in my submission
        for (int i = strlen("<p>"); i < strlen(line); i++){
            newline = "";
            if(line[i] == '<'){
                //fputc('\n', fwrite);
                int c = 0;
                while (c < strlen(line)) {
                    newline[c] = line[(i)+c];
                    c++;
                }
                processTag(newline, fwrite);
                break;
            }
            //printf("%c", line[i]);
            fputc(line[i], fwrite);
        }
        //fputc('\n', fwrite);

    } else if ((line[0] != '<' && strlen(line) > 1)){
        fprintf(fwrite, "%s", line);
    } else if (strncmp("<unr>", line, strlen("<unr>")) == 0){
        //unrecognized tag
        return;
    }
}

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
        if (line[0] != '<' && strlen(line) > 1){
            fprintf(fwrite, "%s", line);
        } else {
            processTag(line, fwrite);
        }
    }
}



