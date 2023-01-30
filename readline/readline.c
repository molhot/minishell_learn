#include "../minishell.h"

int main()
{
	char *line;
	t_token *tok;
	t_token *f_tok;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break;
		if (*line)
			add_history(line);
		tok = torknizer(line);
		f_tok = tok;
		while (tok != NULL)
		{
			printf("tok's num is %s && type is %d\n", tok->word, tok->kind);
			tok = tok->next;
		}
		exec(f_tok->word);
		free(line);
	}
	exit(0);
}