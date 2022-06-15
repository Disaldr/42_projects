/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmumm <kmumm@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:02:43 by kmumm             #+#    #+#             */
/*   Updated: 2022/06/14 15:47:47 by kmumm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "errno.h"

void	ps_error(int flag, t_pipex *pipex)
{
	char	*errors[20];

	errors[0] = "Error: wrong number of input arguments\n";
	errors[1] = "Struct";
	errors[2] = "Fork";
	errors[3] = "Error: parse error\n";
	errors[4] = "Pipe";
	errors[5] = "Execve";
	errors[6] = "File1";
	errors[7] = "File2";
	errors[8] = "Error: command not found\n";
	errors[9] = "Error: command not found\n";
	if (flag == 0 || flag == 3 || flag == 8)
		ft_putstr_fd(errors[flag], 2);
	if (flag == 2 || flag == 4 || flag == 1 || flag == 5 || flag == 6)
		perror(errors[flag]);
	if (flag == 8)
		exit(127);
	if (pipex)
		free(pipex);
	exit(1);
}

static void	process1(t_pipex *pipex)
{
	dup2(pipex->file1, 0);
	dup2(pipex->tube[1], 1);
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	close(pipex->file1);
	close(pipex->file2);
	execve(pipex->cmd1[0], pipex->cmd1, NULL);
}

static void	process2(t_pipex *pipex)
{
	dup2(pipex->tube[0], 0);
	dup2(pipex->file2, 1);
	close(pipex->tube[0]);
	close(pipex->tube[1]);
	close(pipex->file1);
	close(pipex->file2);
	execve(pipex->cmd2[0], pipex->cmd2, NULL);
}

static void	exec_cmds(t_pipex *pipex)
{
	int	pid[2];
	int	status[2];

	pid[0] = fork();
	if (pid[0] == -1)
		ps_error(2, pipex);
	if (pid[0] == 0)
		process1(pipex);
	pid[1] = fork();
	if (pid[1] == -1)
		ps_error(2, pipex);
	if (pid[1] == 0)
		process2(pipex);
	close (pipex->tube[0]);
	close (pipex->tube[1]);
	close (pipex->file1);
	close (pipex->file2);
	waitpid(pid[1], &status[1], 0);
	waitpid(pid[0], &status[0], 0);
	if (status[0] == -1 || status[1] == -1)
		ps_error(5, pipex);
}

int	main(int argc, char *argv[], char *envr[])
{
	t_pipex	*pipex;
	char	*err;

	if (argc != 5)
		ps_error(0, NULL);
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		ps_error(1, NULL);
	pipex->argv = argv;
	err = parse_pipex(pipex, envr);
	if (err)
		ps_error(3, pipex);
	if (pipe(pipex->tube) == -1)
		ps_error(4, pipex);
	exec_cmds(pipex);
	ft_free_split(pipex->cmd1);
	ft_free_split(pipex->cmd2);
	free(pipex);
	return (0);
}
