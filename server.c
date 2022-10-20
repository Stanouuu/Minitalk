/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:22:17 by sbarrage          #+#    #+#             */
/*   Updated: 2022/10/20 16:56:39 by sbarrage         ###   ########.fr       */
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

void	action(int num, siginfo_t	*info, void *content)
{
	if (content)
		(void)content;
	if (num == 60)
	{
		if (str)
		{
			ft_printf("%c", bitoi(str));
			free(str);
		}
		str	= malloc(sizeof(char *));
		str[0] = '\0';
	}
	if (num == 12)
		str = ft_strjoin(str, "1");
	if (num == 10)
		str = ft_strjoin(str, "0");
	// if (!str)
	// {
	// 	write(0, "Error\n", 6);
	// 	exit (0);
	// }
	kill(info->si_pid, SIGUSR1);
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
		sigaction(SIGUSR1,  &sa, NULL);
		sigaction(60,  &sa, NULL);
		sigaction(61,  &sa, NULL);
		sigaction(SIGUSR2,  &sa, NULL);
	}
}




