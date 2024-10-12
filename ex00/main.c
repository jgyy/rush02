/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegoh <jegoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:08:18 by jegoh             #+#    #+#             */
/*   Updated: 2024/10/12 10:32:21 by jegoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    DictEntry dict[MAX_DICT_SIZE];
    int dict_size = 0;
    const char *dict_file = "numbers.dict";
    unsigned long long number;

    fprintf(stderr, "Debug: Program started\n");
    fprintf(stderr, "Debug: argc = %d\n", argc);

    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Debug: Invalid number of arguments\n");
        printf("Error\n");
        return 1;
    }

    if (argc == 3) {
        dict_file = argv[1];
        number = str_to_ull(argv[2]);
    } else {
        number = str_to_ull(argv[1]);
    }

    fprintf(stderr, "Debug: Input number: %llu\n", number);

    if (number == 0 && strcmp(argv[argc - 1], "0") != 0) {
        fprintf(stderr, "Debug: Invalid input (not a positive number or zero)\n");
        printf("Error\n");
        return 1;
    }

    if (number == ULLONG_MAX && strcmp(argv[argc - 1], "18446744073709551615") != 0) {
        fprintf(stderr, "Debug: Number too large\n");
        printf("Error\n");
        return 1;
    }

    fprintf(stderr, "Debug: Loading dictionary: %s\n", dict_file);
    if (!load_dictionary(dict_file, dict, &dict_size)) {
        fprintf(stderr, "Debug: Failed to load dictionary\n");
        printf("Dict Error\n");
        return 1;
    }
    fprintf(stderr, "Debug: Dictionary loaded. Size: %d\n", dict_size);

    fprintf(stderr, "Debug: First 5 dictionary entries:\n");
    for (int i = 0; i < 5 && i < dict_size; i++) {
        fprintf(stderr, "Debug:   %llu: %s\n", dict[i].number, dict[i].word);
    }

    fprintf(stderr, "Debug: Converting number: %llu\n", number);
    char *result = convert_number(number, dict, dict_size);
    if (result) {
        fprintf(stderr, "Debug: Conversion successful. Result: %s\n", result);
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Debug: Conversion failed\n");
        printf("Dict Error\n");
    }

    free_dictionary(dict, dict_size);
    fprintf(stderr, "Debug: Program finished\n");
    return 0;
}
