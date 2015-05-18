#include "libnetwork.h"

int					is_dir(char *path)
{
	int				is_dir;

	is_dir = 0;
	if (chdir(path) != -1)
	{
		chdir("..");
		is_dir = 1;
	}
	return (is_dir);
}

int					send_dir(char **path, int socket)
{
	char			*tmp;
	DIR				*d;
	struct dirent	*s;
	char			*tmp_path[3];
	char			buff[1024];

	(void)path;
	send(socket, "dir", 4, 0);
	recv(socket, &tmp, 1, 0);
	d = opendir(path[1]);
	tmp_path[0] = ft_strdup(path[0]);
	tmp_path[2] = NULL;
	while ((s = readdir(d)))
	{
		tmp_path[1] = ft_strdup(s->d_name);
		ft_putendl(s->d_name);
//		send_file(tmp_path, socket);
		send(socket, s->d_name, s->d_namlen, 0);
		free(tmp_path[1]);
		recv(socket, buff, 10, 0);
	}
	send(socket,"", 1, 0);
	return (1);
}

int					send_unique_file(char **path, int socket)
{
	char			buff[255];
	char			tmp;
	int				fd;
	int				ret;
	struct stat		st;
	char			*size;

	if (path[1])
	{
		if ((fd = open(path[1], O_RDONLY)) != -1)
		{
			fstat(fd, &st);
			size = ft_itoa(st.st_size);
			ft_putendl(size);
			send(socket, "file", 5, 0);
			recv(socket, &tmp, 1, 0);
			send(socket, size, ft_strlen(size), 0);
			recv(socket, &tmp, 1, 0);
			while ((ret = read(fd, buff, 255)) > 0)
			{
				send(socket, buff, ret, 0);
				recv(socket, &tmp, 1, 0);
			}
			close(fd);
			return (1);
		}
	}
	return (0);
}

int					send_file(char **path, int socket)
{
	if (!is_dir(path[1]))
		return (send_unique_file(path, socket));
	else
		return (send_dir(path, socket));
	return (0);
}
