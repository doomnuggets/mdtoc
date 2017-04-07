#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "lib/constants.h"
#include "lib/title.h"

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    if(argc > 2)
    {
        printf("Usage: %s <markdown file>\n", argv[0]);
        return 1;
    }

    FILE *fp = NULL;
    if(argc == 1)
    {
        fp = stdin;
    }
    else
    {
        if(is_regular_file(argv[1]) != 1)
        {
            printf("Usage: %s <markdown file>\n", argv[0]);
            return 1;
        }
        fp = fopen(argv[1], "r");
    }

    if(fp == NULL)
    {
        printf("Failed to open file: %s\n", strerror(errno));
        return 1;
    }

    struct Title *first_title = NULL;
    struct Title *previous_title = NULL;
    int in_code_block = 0;
    while(feof(fp) == 0)
    {
        wchar_t current_line[MAX_LINE] = {L'\0'};
        wchar_t *current_line_ptr = current_line;
        while(fgetws(current_line, MAX_LINE, fp) != NULL)
        {
            current_line[wcslen(current_line)-1] = L'\0';
            if(wcsstr(current_line, L"```") != NULL)
            {
                if(in_code_block)
                    in_code_block = 0;
                else
                    in_code_block = 1;
            }
            int title_level = count_title_level(current_line_ptr);
            if(title_level == 0)
            {
                continue;
            }

            wchar_t *title = extract_title(current_line_ptr);
            if(title == NULL)
            {
                continue;
            }
            else if(in_code_block)
            {
                continue;
            }
            wchar_t *anchor = calloc(MAX_ANCHOR, sizeof(wchar_t));
            to_anchor(title, anchor);

            if(first_title == NULL)
            {
                first_title = create_title(NULL, title_level, title, anchor);
                previous_title = first_title;
            }
            else
            {
                previous_title = create_title(previous_title, title_level, title, anchor);
            }

            unique_anchor(first_title, previous_title);
            free(anchor);
            memset(current_line, L'\0', MAX_LINE);
        }
    }

    if(first_title != NULL)
    {
        print_toc(first_title);
    }

    free_titles(first_title);
    fclose(fp);
    return 0;
}
