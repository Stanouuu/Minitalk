/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:22:17 by sbarrage          #+#    #+#             */
/*   Updated: 2022/11/16 16:53:56 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

char	*g_str;

int	bitoi(char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = res * 2 + (str[i] - '0');
		i++;
	}
	return (res);
}

char	*newstr(char *str, char *nbr)
{
	char	*tmp;

	tmp = ft_strjoin(str, nbr);
	free(str);
	return (tmp);
}

void	ft_other_option(int num)
{
	if (ft_strlen(g_str) == 8)
	{
		ft_printf("%c", bitoi(g_str));
		free(g_str);
		g_str = malloc(sizeof(char *));
		g_str[0] = '\0';
	}
	if (num == SIGUSR2)
		g_str = newstr(g_str, "1");
	if (num == SIGUSR1)
		g_str = newstr(g_str, "0");
}

void	action(int num, siginfo_t	*info, void *content)
{
	if (content)
		(void)content;
	if (num == SIGUSR2 && !g_str)
	{
		g_str = malloc(sizeof(char *));
		g_str[0] = '\0';
	}
	else
	{
		ft_other_option(num);
	}
	if (ft_strncmp(g_str, "00000000", 8) == 0)
	{
		write(1, "\n", 1);
		free(g_str);
		g_str = NULL;
		kill(info->si_pid, SIGUSR1);
		return ;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	g_str = NULL;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &action;
	ft_printf("%i\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
}
