/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegoh <jegoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:08:30 by jegoh             #+#    #+#             */
/*   Updated: 2024/10/12 10:19:58 by jegoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <stdio.h>
#include <string.h>

static char *find_word(unsigned long long number, DictEntry *dict, int dict_size) {
    for (int i = 0; i < dict_size; i++) {
        if (dict[i].number == number) {
            return dict[i].word;
        }
    }
    return NULL;
}

static void append_string(char **result, const char *str) {
    if (*result && **result) strcat(*result, " ");
    strcat(*result, str);
}

static void convert_three_digits(unsigned long long number, DictEntry *dict, int dict_size, char **result) {
    unsigned long long hundreds = number / 100;
    unsigned long long tens = (number % 100) / 10;
    unsigned long long ones = number % 10;

    if (hundreds > 0) {
        append_string(result, find_word(hundreds, dict, dict_size));
        append_string(result, find_word(100, dict, dict_size));
    }

    if (tens == 1) {
        append_string(result, find_word(number % 100, dict, dict_size));
    } else {
        if (tens > 1) {
            append_string(result, find_word(tens * 10, dict, dict_size));
        }
        if (ones > 0 || (hundreds == 0 && tens == 0)) {
            append_string(result, find_word(ones, dict, dict_size));
        }
    }
}

char *convert_number(unsigned long long number, DictEntry *dict, int dict_size) {
    char *result = malloc(1000);
    if (!result) return NULL;
    *result = '\0';

    if (number == 0) {
        strcat(result, find_word(0, dict, dict_size));
        return result;
    }

    const unsigned long long billion = 1000000000;
    const unsigned long long million = 1000000;
    const unsigned long long thousand = 1000;

    if (number >= billion) {
        convert_three_digits(number / billion, dict, dict_size, &result);
        append_string(&result, find_word(billion, dict, dict_size));
        number %= billion;
    }

    if (number >= million) {
        convert_three_digits(number / million, dict, dict_size, &result);
        append_string(&result, find_word(million, dict, dict_size));
        number %= million;
    }

    if (number >= thousand) {
        convert_three_digits(number / thousand, dict, dict_size, &result);
        append_string(&result, find_word(thousand, dict, dict_size));
        number %= thousand;
    }

    if (number > 0) {
        convert_three_digits(number, dict, dict_size, &result);
    }

    return result;
}
