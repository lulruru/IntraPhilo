/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:02:21 by russelenc         #+#    #+#             */
/*   Updated: 2023/09/07 14:04:51 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	ft_free_mute(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&(data->eat_status[i]));
	pthread_mutex_destroy(&(data->died));
	pthread_mutex_destroy(&(data->write_lock));
	pthread_mutex_destroy(&(data->round));
}

void	ft_exit(t_data *data)
{
	ft_free_mute(data);
	free(data->eat_status);
	free(data->forks);
	free(data->philos);
	free(data);
}

int	ft_error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data != NULL)
		ft_exit(data);
	return (1);
}
