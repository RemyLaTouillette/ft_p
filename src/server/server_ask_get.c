/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_ask_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghilbert <ghilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 17:38:07 by tlepeche          #+#    #+#             */
/*   Updated: 2015/05/17 22:03:18 by vpailhe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			is_dir(char *path)
{
	if (!chdir(path))
	{
		ft_putstr("DOSSIER");
		chdir("..");
	}
	else
		ft_putstr("WRONG REQUEST");
}

int				 ask_get(char **av, int fd)
{
	char		buff[255];
	char		tmp;
	int			tar_fd;
	int			ret;
	struct stat st;

	if (av[1])
	{
		if ((tar_fd = open(av[1], O_RDONLY)) != -1)
		{
			fstat(tar_fd, &st);
			while ((ret = read(tar_fd, buff, 255)) > 0)
			{
				send(fd, buff, ret, 0);
				recv(fd, &tmp, 1, 0);
			}
			send(fd, "\0", 1, 0);
			close(tar_fd);
			return (1);
		}
//		else
//			is_dir(av[1]);
		send(fd, "\0", 1, 0);
		return (0);
	}
	return (0);
}
