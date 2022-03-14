#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAGS 92
#define ENTITIES 26

typedef struct tlvl{
    char * name;
    int lvl;
}tlvl_t;

typedef struct ent{
    char * name;
    char * replace;
}entity;

void checkFile(char*buffer, long size, char *outbuffer){ // sending outbuffer in case you have return something empty
    const char* level1tags [2] = {"<html>", "</html>"};
    const char* level2tags [4] = {"<body>", "</body>", "<title>", "</title>"};
    const char* level3tags [20] = {"<h1>", "<h2>", "<h3>", "<h4>", "<h5>", "<h6>", "<p>",
                                 "</h1>", "</h2>", "</h3>", "</h4>", "</h5>", "</h6>", "</p>",
                                 "</ul>", "<ul>", "<ol>", "</ol>", "<section>", "</section>" };
    const char* level4tags [36] = {"<li>", "</li>", "<b>", "</b>", "<i>", "</i>", "<strong>", "</strong>",
                                 "<em>", "</em>", "<small>", "</small>", "<code>", "</code>", "<pre>",
                                 "</pre>", "<sub>", "</sub>", "<sup>", "</sup>", "<a>", "</a>", "<label>",
                                 "</label>", "<abbr>", "</abbr>", "<q>", "</q>", "<blockquote>", "</blockquote>",
                                 "<div>", "</div>", "<cite>", "</cite>", "<addr>", "</addr>"};

}


void processTag (char* buffer, long size, char *outbuffer, FILE* fw) {
    tlvl_t rectags [TAGS] = {{"<html>", 100}, {"</html>", 101},{"<body>", 200},  {"</body>",201},
                             {"<title>", 202}, {"</title>", 203},{"<h1>", 300},{"</h1>", 301},
                             {"<h2>", 302}, {"</h2>", 303},{"<h3>", 304}, {"</h3>", 305},
                             {"<h4>", 306}, {"</h4>", 307},{"<h5>", 308}, {"</h5>", 309},
                             {"<h6>", 310}, {"</h6>", 311}, {"<section>", 312}, {"</section>", 313},
                             {"<p>", 314}, {"</p>", 315}, {"<ul>", 316},{"</ul>", 317},
                             {"<ol>", 318}, {"</ol>", 319}, {"<b>", 400}, {"</b>", 401},
                             {"<strong>", 402}, {"</strong>", 403}, {"<li>", 404}, {"</li>", 405},
                             {"<i>", 406}, {"</i>", 407}, {"<small>", 408}, {"</small>", 409},
                             {"<code>", 410}, {"</code>", 411}, {"<pre>", 412}, {"</pre>", 413},
                             {"<sub>", 414}, {"</sub>", 415}, {"<sup>", 416}, {"</sup>", 417},
                             {"<em>", 418}, {"</em>", 419}, {"<a>", 420}, {"</a>", 421},
                             {"<label>", 422}, {"</label>", 423}, {"<abbr>", 424}, {"</abbr>", 425},
                             {"<q>", 426}, {"</q>", 427}, {"<blockquote>", 428}, {"</blockquote>", 429},
                             {"<div>", 430}, {"</div>", 431}, {"<cite>", 432}, {"</cite>", 433},
                             {"<html title=\"", 100},{"<body title=\"", 200}, {"<title title=\"", 202}, {"<h1 title=\"", 300},
                             {"<h2 title=\"", 302}, {"<h3 title=\"", 304}, {"<h4 title=\"", 306},{"<h5 title=\"", 308},
                             {"<h6 title=\"", 310}, {"<section title=\"", 312}, {"<p title=\"", 314}, {"<ul title=\"", 316},
                             {"<ol title=\"",318}, {"<b title=\"", 400},{"<strong title=\"", 402}, {"<li title=\"", 404},
                             {"<i title=\"", 406},  {"<small title=\"", 408}, {"<code title=\"", 410}, {"<pre title=\"", 412},
                             {"<sub title=\"", 414}, {"<sup title=\"", 416},{"<em title=\"", 418}, {"<a title=\"", 420},
                             {"<label title=\"", 422}, {"<abbr title=\"", 424}, {"<q title=\"", 426}, {"<blockquote title=\"", 428},
                             {"<div title=\"", 430}, {"<cite title=\"", 432}};
    int i = 0, o=0;
    char *tmp = malloc(size + 1);
    int recognized;
    while(i < size) {
        recognized = 0;
        if (buffer[i] == '<') {
            for (int j = 0; j < TAGS; j++) {
                if (strncmp(&buffer[i], rectags[j].name, strlen(rectags[j].name)) == 0) { //recognized tags
                    i += strlen(rectags[j].name);
                    recognized = 1;
                    break;
                }
            }
            if (!recognized){
                //un-recognized tags
                // check if the the closing tag is present for this unknown tag
                int k = 0;
                tmp[k++] = buffer[i++];  //create end tag for unknown tag
                tmp[k++]='/';
                while((buffer[i] != '>') && (i < size)) {
                    tmp[k++] = buffer[i++];
                }
                tmp[k++] = buffer[i++]; // copy '>' to the closing token
                tmp[k] = '\0';
                if (NULL != strstr(&buffer[i], tmp)) { //end unknown end tag, skip until next tag
                    //skip until next '<'
                    while((buffer[i] != '<') && (i < size)) {
                        i++;
                    }
                }
            }
        } else {
            if (buffer[i] == '\"' && (i+1) < size && buffer[i+1] == '>') {
                i +=2;
                continue;
            }
            outbuffer[o++] = buffer[i++];
        }
    }
    free(tmp);
    outbuffer[o] = '\n';
    printf("%s", outbuffer);
}

/*
void processEntities (char *outbuffer, FILE* fw) {
    entity entities [ENTITIES] = {{"&nbsp;", " "}, {"&#160;", " "}, {"&lt;", "<"}, {"&#60;", "<"},
                                  {"&gt;", ">"}, {"&#62;", ">"}, {"&amp;", "&"}, {"&#38;", "&"},
                                  {"&quot;", "\""}, {"&#34;", "\""}, {"&apos;", "\'"}, {"&#39;", "\'"},
                                  {"&cent;", "cent"}, {"&#162;", "cent"}, {"&pound;", "pound"}, {"&#163;", "pound"},
                                  {"&yen;", "yen"}, {"&#165;", "euro"}, {"&#8364;", "euro"}, {"&copy;", "copyright"},
                                  {"&#169;", "copyright"}, {"&reg;", "trademark"}, {"&#174;", "trademark"}, {"&sect;", "section"},
                                  {"&#167;", "section"}};
    int i = 0;
    int recognized;
    while (i < size) {
        if (buffer[i] == '&') {
            for (int j = 0; j < ENTITIES; j++) {
                if (strncmp(&buffer[i], entities[j].name, strlen(entities[j].name)) == 0) { //recognized entity
                    //i += strlen(entities[j].replace);
                    for (int k = 0; k < strlen(entities[j].replace); k++) {
                        buffer[i] = (entities[j].replace)[k];
                    }
                    recognized = 1;
                    break;
                }
            }
            if (!recognized) {
                //continue til next white space
            }
        }
    }
}

*/

int main(int argc, const char *argv[]) {
    // Ensures that 2 command-line arguments are supplied.
    if (argc < 3) {
        fprintf(stderr, "usage: %s <filename> <action>\n", argv[0]);
        return 1;
    }
    FILE *fr;
    FILE *fw;
    fr = fopen(argv[1], "r");
    fw = fopen(argv[2], "w");
    if (fr == NULL || fw == NULL) {
        fprintf(stderr, "File open failure");
        return 0;
    }
    fseek(fr, 0, SEEK_END);
    long fsize = ftell(fr);
    fseek(fr, 0, SEEK_SET);  /* same as rewind(f); */
    char *buffer = malloc(fsize + 1);
    char *outbuffer = malloc(fsize + 1);
    fread((void *)buffer, 1, fsize, fr);
    buffer[fsize] = '\0';
    //printf("%s\n",buffer);
    fclose(fr);
    processTag(buffer, fsize, outbuffer, fw);


    //fputs(outbuffer, fw);
    //fflush(fw);
    free(buffer);
    free(outbuffer);

    fclose(fw);

}
