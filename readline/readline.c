#include "../minishell.h"

int main()
{
	char *line;
	t_token *tok;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break;
		if (*line)
			add_history(line);
		tok = torknizer(line);
		exec(tok->word);
		free(line);
	}
	exit(0);
}