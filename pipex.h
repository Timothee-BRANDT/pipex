#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h> // remove at end

int		ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**get_all_path(char **envp);
char	**ft_split(const char *str, char c);
char	*get_correct_cmd(char **path, char **cmd);
char	*join_cmd(char *path, char *cmd);
char	*ft_strjoin(char *s1, char *s2);
void	free_tab(char **tab);

#endif
