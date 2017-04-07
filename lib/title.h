#ifndef TITLE_H
#define TITLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#include "constants.h"

struct Title
{
    int level;
    wchar_t *title;
    wchar_t *anchor;
    struct Title *next;
};

// Generates a new unique anchor.
void unique_anchor(struct Title *first_title, struct Title *new_title)
{
    wchar_t *tmp_anchor = calloc(MAX_ANCHOR, sizeof(wchar_t));
    wcsncpy(tmp_anchor, new_title->anchor, MAX_ANCHOR-1);
    struct Title *current_title = first_title;
    int is_unique = 0;
    int unique_id = 0;
    while(is_unique != 1)
    {
        while(current_title != NULL)
        {
            if(wcscmp(tmp_anchor, current_title->anchor) == 0 && current_title != new_title)
            {
                unique_id++;
                is_unique = 0;
                break;
            }
            else
            {
                is_unique = 1;
            }

            current_title = current_title->next;
        }

        if(is_unique == 0)
        {
            memset(tmp_anchor, '\0', MAX_LINE);
            swprintf(tmp_anchor, sizeof(wchar_t)*MAX_LINE-1, L"%ls-%d", new_title->anchor, unique_id);
        }
    }
    memset(new_title->anchor, '\0', MAX_LINE);
    wcsncpy(new_title->anchor, tmp_anchor, MAX_LINE-1);
    free(tmp_anchor);
}

// Builds a new title struct with the passed args.
struct Title *create_title(struct Title *previous, int indent_level, wchar_t *title, wchar_t *anchor)
{
    struct Title *t = malloc(sizeof(struct Title));
    t->level = indent_level;
    t->title = calloc(MAX_LINE, sizeof(wchar_t));
    t->anchor = calloc(MAX_LINE, sizeof(wchar_t));
    wcsncpy(t->title, title, MAX_LINE-1);
    wcsncpy(t->anchor, anchor, MAX_LINE-1);
    t->next = NULL;
    if(previous != NULL)
    {
        previous->next = t;
    }

    return t;
}

// Iterates over all titles in the linked list and frees all allocated resources.
void free_titles(struct Title *first_title)
{
    struct Title *current_title = first_title;
    while((current_title = first_title) != NULL)
    {
        first_title = first_title->next;
        free(current_title->title);
        free(current_title->anchor);
        free(current_title);
    }
}

/* This counts how many '#' are in front of the actual title. It is used to indent
 * the entry in the table of contents.
 */
int count_title_level(wchar_t *line)
{
    int title_level = 0;
    while(line[title_level] == '#' && title_level <= 6)
    {
        title_level++;
    }
    return title_level;
}

/* Extracts the actual title without the leading '#'. */
wchar_t *extract_title(wchar_t *line)
{
    int title_index = 0;
    while((line[title_index] == L'#' || line[title_index] == L' ') && line[title_index] != '\0')
    {
        title_index++;
    }

    return line+title_index;
}

/* Converts a title to a valid anchor. */
void to_anchor(wchar_t *title, wchar_t *anchor)
{
    int anchor_index = 1;
    anchor[0] = L'#';
    for(int i = 0; title[i] != L'\0'; i++)
    {
        if(anchor_index >= MAX_ANCHOR)
        {
            break;
        }

        if(title[i] < L'0' && title[i] != L' ')
            continue;
        else if(title[i] > L'9' && title[i] < L'A')
            continue;
        else if(title[i] > L'Z' && title[i] < L'a')
            continue;
        else if(title[i] > L'z' && title[i] < 192)
            continue;

        if(title[i] == L' ' || title[i] == L'_' || title[i] == L'-')
            anchor[anchor_index] = L'-';
        else
            anchor[anchor_index] = towlower(title[i]);

        anchor_index++;
    }
}

/* Prints the final table of contents. */
void print_toc(struct Title *first_title)
{
    struct Title *current_title = first_title;
    while(current_title != NULL)
    {
        // Indent the title if needed.
        for(int indent = 1; indent < current_title->level; indent++)
        {
            wprintf(L"  ");
        }

        wprintf(L"+ [%ls](%ls)\n", current_title->title, current_title->anchor);
        current_title = current_title->next;
    }
}

#endif /* TITLE_H */
