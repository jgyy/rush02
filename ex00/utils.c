/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegoh <jegoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:08:48 by jegoh             #+#    #+#             */
/*   Updated: 2024/10/12 10:32:32 by jegoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <ctype.h>
#include <string.h>
#include <limits.h>

char *trim(char *str) {
    char *end;

    while(isspace((unsigned char)*str)) str++;

    if(*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    end[1] = '\0';

    return str;
}

unsigned long long str_to_ull(const char *str) {
    unsigned long long result = 0;
    unsigned long long max_div_10 = ULLONG_MAX / 10;
    unsigned long long max_mod_10 = ULLONG_MAX % 10;
    while (*str) {
        if (*str < '0' || *str > '9') return 0;
        unsigned int digit = *str - '0';
        if (result > max_div_10 || (result == max_div_10 && digit > max_mod_10)) {
            return ULLONG_MAX;
        }
        result = result * 10 + digit;
        str++;
    }
    return result;
}
