#include "../minishell.h"

int main()
{
	char	*line;
	t_token	*tok;
	t_node *node;

	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL || line[0] == 0)
			break;
		if (*line)
			add_history(line);
		if (line[0] == '/' || line[0] == '.')
			abusolute_path(line);
		else
		{
			tok = torknizer(line);
			node = parse(tok);
			expand(node);
			exec(node->args->word);
		}
		free(line);
	}
	exit(0);
}