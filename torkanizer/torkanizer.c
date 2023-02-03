#include "../minishell.h"

static void fatal_error(const char *msg) __attribute__((noreturn));

static void    fatal_error(const char *msg)
{
    dprintf(STDERR_FILENO, "Fatal Error: %s", msg);
    exit(1);
}

bool    is_metacharactert(char c)
{
    return (c && strchr("|&;()<>\t\n", c));
}

bool startswith(const char *s, const char *keyword)
{
	return (memcmp(s, keyword, strlen(keyword)) == 0);
}

bool is_word(const char *s)
{
	return (*s && !is_metacharactert(*s));
}

t_token *new_token(char *word, t_token_kind kind)
{
	t_token *tok;

	tok = calloc(1, sizeof(*tok));
	if (tok == NULL)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

t_token *word(char **rest, char *line)
{
    const char *start = line;
    char *word;

    while (*line != '\0' && !is_metacharactert(*line))
	{
        line++;
		if (*line == '\'')
		{
			line++;
			while (*line != '\'')
			{
				if (*line == '\0')
					fatal_error("single quote\n"); //singlequote is not closed
				line++;
			}
			line++;
		}
		else
			line++;
	}
    word = strndup(start, line - start);
    if (word == NULL)
        fatal_error("strndup");
    *rest = line;
    return (new_token(word, TK_WORD));
}

bool	is_operator(const char *s)
{
	static char *const operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t	i = 0;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(s, operators[i]))
			return (true);
		i++;
	}
	return (false);
}

t_token *operator(char **rest, char *line)
{
	static char *const operators[] = {"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t i = 0;
	char *op;

	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	fatal_error("Unexpected operator");
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	*rest = line;
	return (false);
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
            fatal_error("Unexpected Token");
    }
    tok->next = new_token(NULL, TK_EOF);
    return (head.next);
}
