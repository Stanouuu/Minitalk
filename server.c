/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:22:17 by sbarrage          #+#    #+#             */
/*   Updated: 2022/11/15 16:03:33 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

char	*str;

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
	char *tmp;

	tmp = ft_strjoin(str, nbr);
	free(str);
	return (tmp);
}

void	action(int num, siginfo_t	*info, void *content)
{
	if (content)
		(void)content;

	// ft_printf("%d\n", info->si_pid);
	// sleep(1);

	if (num == SIGUSR1 && !str)
	{
		str	= malloc(sizeof(char *));
		str[0] = '\0';
	}
	else
	{
		if (ft_strlen(str) == 8)
		{
			ft_printf("%s\n", str);
			ft_printf("%c", bitoi(str));
			free(str);
			str	= malloc(sizeof(char *));
			str[0] = '\0';
		}
		if (num == SIGUSR2)
			str = newstr(str, "1");
		if (num == SIGUSR1)
			str = newstr(str, "0");
	}
	if (ft_strncmp(str, "00000000", 8) == 0)
	{
		free(str);
		str = NULL;
		kill(info->si_pid, SIGUSR2);
		return ;
	}
	kill(info->si_pid, SIGUSR1);
	// write(1, "h", 1);
	// sleep(1);
}

int	main(void)
{
	struct	sigaction sa;
	
	str = NULL;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &action;

	ft_printf("%i\n", getpid()); 
	while (1)
	{
		if (str)
			ft_printf("%s", str);
		sigaction(SIGUSR1,  &sa, NULL);
		sigaction(SIGUSR2,  &sa, NULL);
	}
}




