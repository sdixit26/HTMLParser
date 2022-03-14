#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void processTag (char* line, FILE * fwrite) {
    const char* rectags [61] = {"<h1>", "<h2>", "<h3>", "<h4>", "<h5>", "<h6>", "<title>", "<p>", "<b>", "<strong>",
                                "</h1>", "</h2>", "</h3>", "</h4>", "</h5>", "</h6>", "</title>", "</p>", "</b>", "</strong>",
                                "<li>", "</li>", "</ul>", "<ul>", "<ol>", "</ol>", "<i>", "</i>", "<em>", "/<em>",
                                "<small>", "</small>", "<code>", "</code>", "<pre>", "</pre>", "<sub>", "</sub>", "<sup>", "</sup>",
                                "<a>", "</a>", "<label>", "</label>", "<abbr>", "</abbr>", "<q>", "</q>", "<blockquote>", "</blockquote>",
                                "<div>", "</div>", "<cite>", "</cite>", "<section>", "</section>", "<html>", "</html>", "<body>", "</body>",
                                "<!DOCTYPE html>"};
    const char* recatt [30] = {"<h1 title=\"", "<h2 title=\"", "<h3 title=\"", "<h4 title=\"", "<h5 title=\"",
                               "<h6 title=\"", "<title title=\"", "<p title=\"", "<b title=\"", "<strong title=\"",
                               "<li title=\"", "<ul title=\"", "<ol title=\"", "<i title=\"", "<em title=\"",
                               "<small title=\"", "<code title=\"", "<pre title=\"", "<sub title=\"", "<sup title=\"",
                               "<a title=\"", "<label title=\"", "<abbr title=\"", "<q title=\"", "<blockquote title=\"",
                               "<div title=\"", "<cite title=\"", "<section title=\"", "<html title=\"", "<body title=\""};
    int recognized = 0;
    for (int i = 0; i < strlen(line); i++){
        recognized = 0;
        if (line[i] == '<') {
            //recognized tags
            for (int j = 0; j < 61; j++) {
               if (strncmp(&line[i], rectags[j], strlen(rectags[j])) == 0) {
                  recognized = 1;
                  for (int k = i; k < strlen(rectags[j]) + i; k++) {
                      line[k] = 7; //unprintable char
                  }
                  break;
               }
            }

            for (int n = 0; n < 30; n++){
                if (strncmp(&line[i], recatt[n], strlen(recatt[n])) == 0) {
                    recognized = 1;
                    for (int k = i; k < strlen(recatt[n]) + i; k++) {
                        line[k] = 7; //unprintable char
                    }
                    for (int q = 0; q < strlen(line) + i; q++) {
                        if (line[q] == '\"') {
                            line[q] = ' ';
                        }
                        if (line[q] == '>') {
                            line[q] = 7;
                            break;
                        }
                    }
                    break;
                }
            }
            //find <br
            char* br = "<br>";
            for (int x = 0; x < strlen(line); x++){
                if (strncmp(&line[i], br, strlen(br)) == 0) {
                    for (int k = i; k < strlen(br) + i; k++) {
                        line[k] = 7; //unprintable char
                    }
                }
            }

        }
    }

    for(int l = 0; l < strlen(line); l++) {
        if (line[l] != 7) {
            fputc(line[l], fwrite);
        }
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
        if(strlen(line) > 0) {
            processTag(line, fwrite);
        }
    }
    fclose(fwrite);
}

