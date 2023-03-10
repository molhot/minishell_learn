#include "../minishell.h"

int main()
{
	char	*line;
	t_token	*tok;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break;
		if (*line)
			add_history(line);
		if (line[0] == '/' || line[0] == '.')
			abusolute_path(line);
		else
		{
			tok = torknizer(line);
			expand(tok);
			exec(tok->word);
		}
		free(line);
	}
	exit(0);
}