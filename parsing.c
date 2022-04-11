#include "pipex.h"

char	**get_all_path(char **envp)
{
	int	i;
	char **result;

	i = 0;
	while(envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	result = ft_split(envp[i] + 5, ':');
	return (result);
}

char	*get_correct_cmd(char **path, char **cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd[0]);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		//free(cmd_path);
		i++;
	}
	return (NULL);
}
