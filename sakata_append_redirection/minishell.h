/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:28:10 by user              #+#    #+#             */
/*   Updated: 2023/02/03 22:59:05 by user             ###   ########.fr       */
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

typedef enum e_node_kind t_node_kind;
typedef struct s_node t_node;

enum e_node_kind{
    ND_SIMPLE_CMD,
};

struct s_node {
    t_token *args;
    t_node_kind kind_node;
    t_node *next;
};

typedef enum e_token_kind t_token_kind;

struct s_token {
    char *word;
    t_token_kind kind;
    t_token *next;
};

t_token *torknizer(char *line);
int interpret(char *line, char **cmd_arg);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	**ft_split(char const *s, char c);
void exec(char *input);
int abusolute_path(char *line);
bool    is_metacharactert(char c);
void expand(t_node *tok);
t_token *new_token(char *word, t_token_kind kind);
t_node *parse(t_token *tok);

#endif