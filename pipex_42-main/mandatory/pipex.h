/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmumm <kmumm@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:14:39 by cdarrell          #+#    #+#             */
/*   Updated: 2022/06/14 14:06:33 by kmumm            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/include/libft.h"

typedef struct s_pipex
{
	char	**argv;
	int		tube[2];
	int		file1;
	int		file2;
	char	**cmd1;
	char	**cmd2;
	int		execve_status[2];
}t_pipex;

char	*parse_pipex(t_pipex *pipex, char **envr);
void	ps_error(int flag, t_pipex *pipex);

#endif
