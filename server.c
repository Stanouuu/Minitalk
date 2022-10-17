/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:22:17 by sbarrage          #+#    #+#             */
/*   Updated: 2022/10/17 14:20:22 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

char	*str;

void	action(int num, siginfo_t	*info, void *content)
{
	// while (i < 7
	ft_printf("here %d\n", info->si_pid);
	if (content)
		(void)content;
	// ft_printf("%s", pid);

	if (ft_strlen(str) == 7)
	{
		free(str);
		str	= malloc(sizeof(char *));
		str[0] = '\0';  
		write(1, "\n", 1);
	}
	ft_printf("num : %d\n", ft_strlen(str));
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

	ft_printf("%s\n", str);
}

int	main(void)
{
	struct	sigaction sa;
	
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = &action;

	ft_printf("%i\n", getpid());
	str	= malloc(sizeof(char *));
	str[0] = '\0';  
	while (1)
	{
		// sleep(1);
		sigaction(SIGUSR1,  &sa, NULL);
		sigaction(60,  &sa, NULL);
		sigaction(SIGUSR2,  &sa, NULL);
		// ft_printf("%s here\n", str);
	}
}

// int	itohex(char *str, char *hex)
// {
// 	int	res;
// 	int	i;
// 	int	j;

// 	i = 2;
// 	res = 0;
// 	while (str[i])
// 	{
// 		j = 0;
// 		while (hex[j])
// 		{
// 			if (hex[j] == str[i] || ft_toupper(hex[j]) == str[i])
// 				res = res * 16 + j;
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (res);
// }
