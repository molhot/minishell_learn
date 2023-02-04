#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <assert.h>
#include <readline/readline.h>
#include <readline/history.h>

static void fatal_error(const char *msg) __attribute__((noreturn));

static size_t	ft_strlen(const char *string_row)
{
	size_t	counter;

	counter = 0;
	while (*string_row != '\0')
	{
		counter = counter + 1;
		string_row = string_row + 1;
	}
	return (counter);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dstsize == 0)
		return (src_len);
	if (dst_len < dstsize)
	{
		i = 0;
		while (src[i] != '\0' && i + 1 < dstsize - dst_len)
		{
			dst[dst_len + i] = src[i];
			i = i + 1;
		}
		dst[dst_len + i] = '\0';
		return (src_len + dst_len);
	}
	return (src_len + dstsize);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*src_firstaddress;

	src_firstaddress = src;
	if (size == 0)
		return (ft_strlen(src));
	while ((size != 1) && (*src != '\0'))
	{
		*dst = (char)*src;
		dst = dst + 1;
		src = src + 1;
		size = size - 1;
	}
	*dst = '\0';
	return (ft_strlen(src_firstaddress));
}


static size_t	structure_in(const char *s, char c)
{
	int	individual_arrangementlength;

	individual_arrangementlength = 0;
	if (*s != '\0')
	{
		while ((*s) == c)
			s = s + 1;
		if (*s == '\0' && c != '\0')
			return (0);
		if (*s != '\0')
		{
			while ((*s) != c)
			{
				individual_arrangementlength = individual_arrangementlength + 1;
				s = s + 1;
				if (*s == '\0')
					break ;
			}
		}
	}
	return (individual_arrangementlength);
}

static size_t	secure_arrangement(const char (*s), char c)
{
	int		arrangement_row;
	int		counter_add;

	if (s == NULL || (*s == '\0' && c == '\0'))
		return (1);
	if (c == '\0')
		return (2);
	arrangement_row = 1;
	counter_add = 0;
	while (*s == c)
	{
		s = s + 1;
		counter_add = counter_add + 1;
	}
	while ((*s) != '\0')
	{
		if (*s != c && *(s + 1) == c)
			arrangement_row = arrangement_row + 1;
		s = s + 1;
		counter_add = counter_add + 1;
	}
	if (*(s - 1) != c && counter_add != 0)
		arrangement_row = arrangement_row + 1;
	return (arrangement_row);
}

static size_t	ft_insert_arrangement(char (*row), const char (*s), char c)
{
	int	counter_insert;

	counter_insert = 0;
	if (*s == '\0' && c == '\0')
	{
		*row = '\0';
		return (0);
	}
	while (((*(s + counter_insert)) == c) && (*(s + counter_insert)) != '\0')
		counter_insert = counter_insert + 1;
	if (*(s + counter_insert) == '\0')
	{
		row = NULL;
		return (counter_insert);
	}
	while (((*(s + counter_insert)) != c) && (*(s + counter_insert) != '\0'))
	{
		*row = *(s + counter_insert);
		row = row + 1;
		counter_insert = counter_insert + 1;
	}
	*(row) = '\0';
	return (counter_insert);
}

static char	**ft_free(int i, char (**arrangement))
{
	int	first;

	first = 0;
	while (first != i)
	{
		free(arrangement[first]);
		first = first + 1;
	}
	free(arrangement);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**arbox;
	size_t		i;
	size_t		mallocsize_arrange;
	size_t		structure;

	mallocsize_arrange = secure_arrangement(s, c);
	arbox = (char **)malloc(sizeof(char *) * mallocsize_arrange);
	if (!(arbox))
		return (NULL);
	i = 0;
	if (mallocsize_arrange != 1)
	{
		while (i != (mallocsize_arrange - 1))
		{
			structure = structure_in(s, c);
			arbox[i] = (char *)malloc(sizeof(char) * (structure + 1));
			if (!(arbox[i]))
				return (ft_free(i - 1, arbox));
			s = s + ft_insert_arrangement(arbox[i], s, c);
			i = i + 1;
		}
	}
	arbox[mallocsize_arrange - 1] = NULL;
	return (arbox);
}

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

int stash_fd(int fd)
{
    int stashfd;

    stashfd = fcntl(fd, F_DUPFD, 10);
    if (stash_fd < 0)
        fatal_error("fcntl\n");
    if (close(fd) < 0)
        fatal_error("close");
    return (stashfd);
}

void redirect(int targetfd, char *filename, char *command_line)
{
    int filefd;
    int stashed_targetfd;
    extern char **environ;
    char **command;

    filefd = open(filename, O_RDONLY, 0644);
    filefd = stash_fd(filefd);

    stashed_targetfd = stash_fd(targetfd);
    if (filefd != targetfd)
    {
        dup2(filefd, targetfd);
        close(filefd);
    }
    command = ft_split(command_line, ' ');
    execve(searchpath(command[0]), command, environ);
    dup2(stashed_targetfd, targetfd);
}

int main(int argc , char **argv)
{
    redirect(0, "test.txt", "cat");
}