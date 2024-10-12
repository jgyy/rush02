/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegoh <jegoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:08:12 by jegoh             #+#    #+#             */
/*   Updated: 2024/10/12 10:12:52 by jegoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_H
#define RUSH_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_DICT_SIZE 1000
#define MAX_LINE_LENGTH 256

typedef struct {
    unsigned long long number;
    char *word;
} DictEntry;

int load_dictionary(const char *filename, DictEntry *dict, int *dict_size);

char *convert_number(unsigned long long number, DictEntry *dict, int dict_size);

char *trim(char *str);
unsigned long long str_to_ull(const char *str);
void free_dictionary(DictEntry *dict, int dict_size);

#endif
