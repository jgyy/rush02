/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegoh <jegoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:08:41 by jegoh             #+#    #+#             */
/*   Updated: 2024/10/12 10:25:43 by jegoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256

int load_dictionary(const char *filename, DictEntry *dict, int *dict_size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Debug: Cannot open dictionary file: %s\n", filename);
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    *dict_size = 0;

    while (fgets(line, sizeof(line), file)) {
        char *colon = strchr(line, ':');
        if (colon == NULL) {
            fprintf(stderr, "Debug: Invalid line format: %s", line);
            continue;
        }

        *colon = '\0';
        char *number_str = trim(line);
        char *word = trim(colon + 1);

        char *newline = strchr(word, '\n');
        if (newline) *newline = '\0';

        if (strlen(number_str) == 0 || strlen(word) == 0) {
            fprintf(stderr, "Debug: Empty number or word: %s:%s\n", number_str, word);
            continue;
        }

        dict[*dict_size].number = str_to_ull(number_str);
        dict[*dict_size].word = strdup(word);

        fprintf(stderr, "Debug: Loaded entry: %llu -> %s\n", dict[*dict_size].number, dict[*dict_size].word);

        (*dict_size)++;

        if (*dict_size >= MAX_DICT_SIZE) {
            fprintf(stderr, "Debug: Dictionary size limit reached\n");
            break;
        }
    }

    fclose(file);
    fprintf(stderr, "Debug: Loaded %d entries from dictionary\n", *dict_size);
    return *dict_size > 0;
}

void free_dictionary(DictEntry *dict, int dict_size) {
    for (int i = 0; i < dict_size; i++) {
        free(dict[i].word);
    }
}
