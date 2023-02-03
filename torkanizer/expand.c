#include "../minishell.h"

static void fatal_error(const char *msg) __attribute__((noreturn));

static void    fatal_error(const char *msg)
{
    dprintf(STDERR_FILENO, "Fatal Error: %s", msg);
    exit(1);
}

void append_char(char **s, char c)
{
    size_t  size;
    char    *new;

	size = 2;
	if (*s)
		size += strlen(*s);
	new = malloc(size);
	if (new == NULL)
		fatal_error("malloc");
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	quote_removal(t_token *tok)
{
	char *new_word;
	char *p;

	if (tok == NULL || tok->kind != TK_WORD || tok->word == NULL)
		return ;
	p = tok->word;
	new_word = NULL;
	while (*p && !is_metacharactert(*p))
	{
		if (*p == '\'')
		{
			p++;
			while (*p != '\'')
			{
				if (*p == '\0')
					fatal_error("single quote\n");
				append_char(&new_word, *p++);
			}
			p++;
		}
		else
			append_char(&new_word, *p++);
	}
	free(tok->word);
	tok->word = new_word;
	quote_removal(tok->next);
}

void expand(t_token *tok)
{
	quote_removal(tok);
}