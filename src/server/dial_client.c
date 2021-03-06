#include "server.h"


void	byte_reception(char **new_av, char *buf, int ret)
{
	ft_putstr("received ");
	ft_putnbr(ret);
	ft_putstr(" bytes: ");
	ft_putendl(buf);
	ft_free_tab(new_av);
}

int		display_prompt(char **new_av, int sock)
{
	char	*pwd;

	(void)new_av;
	pwd = ft_strjoin(pwd_handler(), " > ");
	send(sock, pwd, ft_strlen(pwd), 0);
	return (1);
}

void	dial_client(int cs)
{
	int		ret;
	int		bool;
	char	**new_av;
	char	buf[1024];
	t_fct	*list;
	t_fct	*tmp;
	int		ret_val;

	init(&list);
	while ((ret = recv(cs, buf, 1023, 0)) > 0)
	{
		tmp = list;
		buf[ret] = '\0';
		new_av = ft_strsplit_blank(buf);
		printf("av[0] = %s\n", new_av[0]);
		bool = 0;
		while (tmp != NULL)
		{
			if (new_av[0] && ft_strcmp(tmp->name, new_av[0]) == 0)
			{
				bool = 1;
				ret_val = tmp->ptr_funct(new_av, cs);
				break ;
			}
			tmp = tmp->next;
		}
		if (bool == 0)
			send(cs, "ERROR Command not found", 32, 0);
		byte_reception(new_av, buf, ret);
	}
}
