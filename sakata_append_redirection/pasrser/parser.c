#include "../minishell.h"

static void fatal_error(const char *msg) __attribute__((noreturn));

static void    fatal_error(const char *msg)
{
    dprintf(STDERR_FILENO, "Fatal Error: %s", msg);
    exit(1);
}

bool    at_eof(t_token *tok)
{
    return (tok->kind == TK_EOF);
}

t_node *new_node(t_node_kind kind)
{
    t_node *node;

    node = calloc(1, sizeof(*node));
    if (node == NULL)
        fatal_error("calloc\n");
    node->kind_node = kind;
    return (node);
}

t_token *tokdup(t_token *tok)
{
    char *word;

    word = strdup(tok->word);
    if (word == NULL)
        fatal_error("strdup\n");
    return (new_token(word, tok->kind));
}

void append_tok(t_token **tokens, t_token *tok)
{
    if (*tokens == NULL)
    {
        *tokens = tok;
        return ;
    }
    append_tok(&(*tokens)->next, tok);
}

t_node *parse(t_token *tok)
{
    t_node *node;

    node = new_node(ND_SIMPLE_CMD);
    while (tok && !at_eof(tok))
    {
        if (tok->kind == TK_WORD)
            append_tok(&node->args, tokdup(tok));
        else
            printf("Implement parser");
        tok = tok->next;
    }
    return (node);
}