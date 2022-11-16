/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:22:14 by sbarrage          #+#    #+#             */
/*   Updated: 2022/11/16 16:41:38 by sbarrage         ###   ########.fr       */
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

t_bin	*g_bin;

char	*atob(char c)
{
	char			*str;
	unsigned char	bit;
	int				i;

	i = 0;
	bit = 1 << (8 - 1);
	str = malloc(sizeof(char) * 9);
	if (!str)
		return (NULL);
	while (bit)
	{
		if (c & bit)
			str[i] = '1';
		else
			str[i] = '0';
		i++;
		bit >>= 1;
	}
	str[i] = 0;
	return (str);
}

void	ft_case_two(int num)
{
	if (num == SIGUSR2)
	{
		if (g_bin->bnr[g_bin->j] == '0')
		{
			write(1, "0", 1);
			kill(ft_atoi(g_bin->pid), SIGUSR1);
		}
		else if (g_bin->bnr[g_bin->j] == '1')
		{
			write(1, "1", 1);
			kill(ft_atoi(g_bin->pid), SIGUSR2);
		}
	}
}

void	action(int num, siginfo_t	*info, void *content)
{
	if (num == SIGUSR1)
	{
		free(g_bin->txt);
		g_bin->txt = NULL;
		return ;
	}
	if (g_bin->bnr && g_bin->bnr[g_bin->j] == '\0')
	{
		free(g_bin->bnr);
		g_bin->bnr = NULL;
	}
	if (!g_bin->bnr)
	{
		g_bin->bnr = atob(g_bin->txt[g_bin->i]);
		g_bin->i++;
		if (g_bin->bnr == NULL)
		{
			action(SIGUSR1, info, content);
			return ;
		}
		g_bin->j = 0;
	}
	ft_case_two(num);
	g_bin->j++;
}

void	initialise_g_bin(char **argv)
{
	g_bin = malloc(sizeof(t_bin));
	g_bin->txt = ft_strdup(argv[2]);
	g_bin->pid = ft_strdup(argv[1]);
	g_bin->bnr = NULL;
	g_bin->i = 0;
	g_bin->j = 0;
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3)
	{
		write(0, "Mauvais Nombre D'Arguments\n", 27);
		return (0);
	}
	initialise_g_bin(argv);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &action;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	kill(ft_atoi(g_bin->pid), SIGUSR2);
	while (g_bin->txt)
	{	
	}
	g_bin->i = 0;
	g_bin->j = 0;
	free(g_bin->bnr);
	free (g_bin->pid);
	free (g_bin);
}
