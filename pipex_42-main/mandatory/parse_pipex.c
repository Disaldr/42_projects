/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmumm <kmumm@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 22:06:44 by kmumm             #+#    #+#             */
/*   Updated: 2022/06/13 20:58:42 by kmumm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_path(char **envr)
{
	char	**path;
	int		i;

	path = ((void *)0);
	i = -1;
	while (envr[++i])
	{
		if (ft_strnstr(envr[i], "PATH=", ft_strlen(envr[i])))
		{
			path = ft_split(envr[i] + ft_strlen("PATH="), ':');
			return (path);
		}
	}
	return (NULL);
}

static char	*find_cmd(char **path, char *tmp_cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], tmp_cmd);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK) == 0)
			return (tmp);
		else
			free(tmp);
	}
	return (NULL);
}

static char	**get_cmd(char *cmd_string, char **envr)
{
	char	**path;
	char	**cmd;
	char	*tmp_cmd;
	char	*tmp;

	path = get_path(envr);
	if (!path)
		return (NULL);
	cmd = ft_split(cmd_string, ' ');
	if (!cmd)
		return (NULL);
	tmp_cmd = ft_strjoin("/", *cmd);
	if (!tmp_cmd)
		return (NULL);
	tmp = *cmd;
	*cmd = find_cmd(path, tmp_cmd);
	if (!cmd)
	{
		free(tmp_cmd);
		return (NULL);
	}
	free(tmp);
	free(tmp_cmd);
	ft_free_split(path);
	return (cmd);
}

char	*parse_pipex(t_pipex *pipex, char **envr)
{
	pipex->file1 = open(pipex->argv[1], O_RDONLY);
	if (pipex->file1 < 0)
		ps_error(6, pipex);
	pipex->file2 = open(pipex->argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->file2 < 0)
		ps_error(7, pipex);
	pipex->cmd1 = get_cmd(pipex->argv[2], envr);
	if (!*(pipex->cmd1))
		ps_error(8, pipex);
	pipex->cmd2 = get_cmd(pipex->argv[3], envr);
	if (!*(pipex->cmd2))
	{
		free(pipex->cmd1);
		ps_error(8, pipex);
	}
	return (NULL);
}
