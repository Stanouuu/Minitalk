/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:22:14 by sbarrage          #+#    #+#             */
/*   Updated: 2022/11/15 15:50:31 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"


typedef struct s_bin
{
	char	*pid;
	char	*txt;
	char	*bnr;
	int		i;
	int		j;
}	t_bin;

t_bin	*bin;

char	*atob(int c)
{
	char	*str;
	int		i;
	int		j;

	i = c;
	j = 0;
	// ft_printf("%c\n", c);
	if (c == '\0')
		return ("00000000");
	str = malloc(sizeof(char) * 8);
	if (!str)
		return (NULL);
	while (j < 8)
		str[j++] = '0';
	str[j] = '\0';
	j = 1;
	while (i > 0)
	{
		i = i / 2;
		j++;
	}
	j = 7;
	// ft_printf("%d\n", j);
	while (j > 0)
	{
		// ft_printf("%d\n", j);
		str[j] = c % 2 + '0';
		j--;
		c = c / 2;
	}
	ft_printf("%s\n", str);
	return (str);
}

void	action(int num)
{
	if (num == SIGUSR2)
	{
		bin->txt = NULL;
		return ;
	}
	if (bin->bnr && bin->bnr[bin->j] == '\0')
	{
		free(bin->bnr);
		bin->bnr = NULL;
	}
	if (!bin->bnr)
	{
		bin->bnr = atob(bin->txt[bin->i]);
		bin->i++;
		if (bin->bnr == NULL)
		{
			action(SIGUSR2);
			return ;
		}
		bin->j = 0;
	}
	if (num == SIGUSR1)
	{
		// ft_printf("%c\n", bin->bnr[bin->j]);

		if (bin->bnr[bin->j] == '0')
			kill(ft_atoi(bin->pid), SIGUSR1);
		else if (bin->bnr[bin->j] == '1')
			kill(ft_atoi(bin->pid), SIGUSR2);
	}
	bin->j++;
}

int	main(int argc, char **argv)
{
	struct	sigaction sa;

	bin = malloc(sizeof(t_bin));

	bin->txt = ft_strdup(argv[2]);
	bin->pid = ft_strdup(argv[1]);
	bin->bnr = NULL;
	bin->i = 0;
	bin->j = 0;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_handler = &action;


	if (argc != 3)
		write(0, "Mauvais Nombre D'Arguments\n", 27);

	sigaction(SIGUSR1,  &sa, NULL);
	sigaction(SIGUSR2,  &sa, NULL);
	kill(ft_atoi(bin->pid), SIGUSR1);
	while (bin->txt)
	{
		
	}
	bin->i = 0;
	bin->j = 0;
	// free (bin->pid);
	// free (bin);
	sleep(1);
}

