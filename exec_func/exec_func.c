#include "../minishell.h"

static void fatal_error(const char *msg) __attribute__((noreturn));

static void    fatal_error(const char *msg)
{
    dprintf(STDERR_FILENO, "Fatal Error: %s", msg);
    exit(1);
}

char *searchpath(const char *filename)
{
    char path[PATH_MAX];
    char *value;
    char *end;

    value = getenv("PATH");
    if (strlen(filename) > PATH_MAX)
        fatal_error("strlen");
    while (*value != '\0')
    {
        bzero(path, PATH_MAX);
        end = strchr(value, ':');
        if (end)
            strncpy(path, value, end - value);
        else
            ft_strlcpy(path, value, PATH_MAX);
        ft_strlcat(path, "/", PATH_MAX);
        ft_strlcat(path, filename, PATH_MAX);
        if (access(path, X_OK) == 0)
        {
            char *dup;

            dup = strdup(path);
            if (dup == NULL)
                fatal_error("strdup");
            return (dup);
        }
        if (end == NULL)
            return (NULL);
        value = end + 1;
    }
    return (NULL);
}

char **prepare_cmdargs(char **cmd_args_withcmd, int malloc_size)
{
	char **cmdargs;
	int	array_counter;
	int position;
	int args_len;

	array_counter = 0;
	position = 0;
	cmdargs = (char **)malloc(sizeof(char *) * (malloc_size + 1));
	while (cmd_args_withcmd[array_counter] != NULL)
	{
		args_len = strlen(cmd_args_withcmd[array_counter]);
		cmdargs[array_counter] = (char *)malloc(sizeof(char) * (args_len));
		while (position != args_len)
		{
			cmdargs[array_counter][position] = cmd_args_withcmd[array_counter][position];
			position++;
		}
		cmdargs[array_counter][position] = '\0';
		position = 0;
		array_counter++;
	}
	cmdargs[malloc_size] = NULL;
	return (cmdargs);
}

int interpret(char *line, char **cmd_arg)
{
    extern char **environ;
    char **argv;
    pid_t pid;
    int wstatus;
	size_t i;

	i = 0;
	while (cmd_arg[i] != NULL)
		i++;
	argv = prepare_cmdargs(cmd_arg, i);
    pid = fork();
    if (pid < 0)
        fatal_error("fork");
    else if (pid == 0)
    {
        execve(searchpath(line), argv, environ);
        fatal_error("execve\n");
        return (1);
    }
    else
    {
        wait(&wstatus);
        return (WEXITSTATUS(wstatus));
    }
}

int abusolute_path(char *line)
{
    char    **argv;
	char	**line_splited;
    int     i;
    pid_t pid;
	int wstatus;
	extern char **environ;

    i = 0;
	line_splited = ft_split(line, ' ');
    while (line_splited[i] != NULL)
		i++;
    argv = prepare_cmdargs(line_splited, i);
    pid = fork();
    if (pid < 0)
        fatal_error("fork");
    else if (pid == 0)
    {
        execve(argv[0], argv, environ);
        fatal_error("execve\n");
        return (1);
    }
    else
    {
        wait(&wstatus);
        return (WEXITSTATUS(wstatus));
    }
}

void exec(char *input)
{
	char **splited_line;

	splited_line = ft_split((const char *)input, ' ');
	interpret(splited_line[0], splited_line);
}
