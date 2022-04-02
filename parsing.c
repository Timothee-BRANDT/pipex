#include "pipex.h"

char	**get_path(char **envp)
{
	int	i;
	char **result;

	i = 0;
	while(envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	result = ft_split(envp[i] + 5, ':');
	return (result);
}
