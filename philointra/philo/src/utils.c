/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:32:16 by russelenc         #+#    #+#             */
/*   Updated: 2023/09/07 14:13:13 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long int	ft_atoi(const char *str)
{
	long int	sign;
	long int	r;
	long int	i;

	sign = 0;
	i = 0;
	r = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - 48);
		i++;
	}
	if (sign % 2 == 1)
		return (-r);
	return (r);
}

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	check_arg(char **av)
{
	int	i;
	int	y;

	i = 1;
	while (av[i])
	{
		y = 0;
		while (av[i][y])
		{
			if (ft_isdigit(av[i][y]) == 0)
			{
				printf("Error : Argument is not a number\n");
				exit(0);
			}
			y++;
		}
		i++;
	}
	return (1);
}

void	prompt(char *str, t_philo *philo)
{
	long int	time_stamp;

	time_stamp = (timefonction() - philo->data->start_time);
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&(philo->data->write_lock));
	printf("%ld %d %s\n", time_stamp, philo->id, str);
	pthread_mutex_unlock(&(philo->data->write_lock));
}

void	promptded(char *str, t_philo *philo)
{
	long int	time;

	time = timefonction() - philo->data->start_time;
	printf("%ld %d %s\n", time, philo->id, str);
}
