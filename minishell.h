/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <sakata19991214@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:28:10 by user              #+#    #+#             */
/*   Updated: 2023/01/30 17:12:58 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef minishell_h
# define minishell_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <assert.h>
#include <readline/readline.h>
#include <readline/history.h>

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

t_token *torknizer(char *line);
int interpret(char *line, char **cmd_arg);
size_t	strlcat(char *dst, const char *src, size_t dstsize);
size_t	strlcpy(char *dst, const char *src, size_t size);
char	**ft_split(char const *s, char c);
void exec(char *input);

#endif