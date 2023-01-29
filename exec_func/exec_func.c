#include "minishell.h"

void fatal_error(const char *msg) __attribute__((noreturn));

void    fatal_error(const char *msg)
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
    printf("PATH is > %s\n", value);
    printf("PATHMAX is %d\n", PATH_MAX);
    while (*value != '\0')
    {
        bzero(path, PATH_MAX);
        end = strchr(value, ':');
        if (end)
            strncpy(path, value, end - value);
        else
            strlcpy(path, value, PATH_MAX);
        strlcat(path, "/", PATH_MAX);
        strlcat(path, filename, PATH_MAX);
        printf("path is %s\n", path);
        if (access(path, X_OK) == 0)
        {
            char *dup;

            printf(">>access is OK");
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

int interpret(char *line)
{
    extern char **environ;
    char *argv[] = {line, NULL};
    pid_t pid;
    int wstatus;

    pid = fork();
    if (pid < 0)
        fatal_error("fork");
    else if (pid == 0)
    {
        execve("PWD", argv, environ);
        execve(searchpath(line), argv, environ);
        fatal_error("execve");
        return (1);
    }
    else
    {
        wait(&wstatus);
        return (WEXITSTATUS(wstatus));
    }
}

int main(int argc, char **argv)
{
    interpret(argv[1]);
}