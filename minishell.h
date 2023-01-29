/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:28:10 by user              #+#    #+#             */
/*   Updated: 2023/01/29 16:39:27 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minishell_h
# define minishell_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct s_token t_token;

enum e_token_kind {
    TK_WORD,
    TK_RESERVED,
    TK_OP,
    TK_EOF,
};
typedef enum e_token_kind t_token_kind;

struct s_token {
    char *word;
    t_token_kind kind;
    t_token *next;
};

#endif