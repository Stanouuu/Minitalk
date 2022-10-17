/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbarrage <sbarrage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:22:14 by sbarrage          #+#    #+#             */
/*   Updated: 2022/10/17 15:32:42 by sbarrage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

char	**bin;

char	*atob(int c)
{
	char	*str;
	int		i;
	int		j;

	i = c;
	j = 0;
	ft_printf("%c\n", c);
	if (c == '\0')
	{
		write(1, "this chracter is a '0'", 22);
		return("00000000");
	}
	str = malloc(sizeof(char) * 8);
	while (j < 8)
		str[j++] = '0';
	str[j] = '\0';
	j = 1;
	while (i > 0)
	{
		i = i / 2;
		j++;
	}
	ft_printf("%d\n", j);
	while (j > 0)
	{
		// ft_printf("%d\n", j);
		str[j] = c % 2 + '0';
		j--;
		c = c / 2;
	}
	ft_printf("%s\n", str);
	ft_printf("%d\n", ft_strlen(str));
	// ft_printf("%s\n", str);
	return (str);
}

void	action(int num)
{
	ft_printf("%c\n", *bin[0]);
	// if (bin[0] == "\0")
	// 	bin[0] = atob(*bin[1]);
	if (num)
	{
		if (*bin[0] == '0')
			kill(ft_atoi(bin[2]), SIGUSR1);
		else
			kill(ft_atoi(bin[2]), SIGUSR2);
		bin[0]++;
	}
	// else
	// {
	// 	free(bin[0]);
	// 	bin[0] = NULL;
	// }
	
}

int	main(int argc, char **argv)
{
	struct	sigaction sa;

	bin = malloc(sizeof(char *) * 4);
	bin[1] = argv[2];
	bin[2] = argv[1];
	bin[3] = NULL;



	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_handler = &action;



	if (argc != 3)
		write(0, "Mauvais Nombre D'Arguments\n", 27);


	bin[0] = atob(*bin[1]);
	bin[1]++;
	kill(ft_atoi(bin[2]), 60);

	while (bin[1])
	{
		bin[0] = atob(*bin[1]);
		bin[1]++;
		while (bin[0])
		{
			sigaction(SIGUSR1,  &sa, NULL);
			sigaction(SIGUSR2,  &sa, NULL);
			// if (!bin[0])
			// {
			// 	free(bin[1]);
			// 	free(bin[2]);
			// 	free(bin);
			// 	return (0);
			// }
		}
		free(bin[0]);
	}
}

