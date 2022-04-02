#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h> // remove at end
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int		ft_strlen(char *str);
char	**get_path(char **envp);
char	**ft_split(const char *str, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
