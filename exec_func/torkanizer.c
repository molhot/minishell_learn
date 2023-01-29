#include "../minishell.h"

bool    is_metacharactert(char c)
{
    return (c && strchr("|&;()<>\t\n", c));
}



t_token *word(char **rest, char *line)
{
    const char *start = line;
    char *word;

    while (*line != '\0' && !is_metacharactert(*line))
        line++;
    word = strndup(start, line - start);
    if (word == NULL)
        fatal_error("strndup");
    *rest = line;
    return (net_token(word, TK_WORD));
}

t_token *torknizer(char *line)
{
    t_token head;
    t_token *tok;

    head.next = NULL;
    tok = &head;
    while (*line)
    {
        if (consume_blank(&line, line))
            continue ;
        else if (is_operator(line))
            tok = tok->next = operator(&line, line);
        else if (is_word(line))
            tok = tok->next = word(&line, line);
        else
            assert_error("Unexpected Token");
    }
    tok->next = new_token(NULL, TK_EOF);
    return (head.next);
}