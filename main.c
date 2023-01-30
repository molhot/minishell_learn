#include "minishell.h"

int main(int argc, char **argv)
{
	char *line;
	t_token *tok;
	//t_token *f_tok;

	printf("%d\n", argc);
	line = argv[1];
	tok = torknizer(line);
	//f_tok = tok;
	while (tok != NULL)
	{
		printf("tok's num is %s && type is %d\n", tok->word, tok->kind);
		tok = tok->next;
	}
	//exec(f_tok->word);
}
