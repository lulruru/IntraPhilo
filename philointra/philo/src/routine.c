/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:20:18 by russelenc         #+#    #+#             */
/*   Updated: 2023/09/06 17:00:22 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

int	is_dead(t_philo *philo)
{
	int	res;

	pthread_mutex_lock(&(philo->data->died));
	res = philo->data->dead;
	pthread_mutex_unlock(&(philo->data->died));
	return (res);
}

int	check_death(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = data->philos;
	while (++i < data->nb_philo)
	{
		pthread_mutex_lock(&(data->eat_status[i]));
		if ((timefonction() - philo[i].last_eat) > data->time_die)
		{
			pthread_mutex_unlock(&(data->eat_status[i]));
			pthread_mutex_lock(&(data->died));
			data->dead = 1;
			pthread_mutex_unlock(&(data->died));
			pthread_mutex_lock(&(data->write_lock));
			promptded("died", philo);
			pthread_mutex_unlock(&(data->write_lock));
			return (1);
		}
		pthread_mutex_unlock(&(data->eat_status[i]));
	}
	return (check_meals(data));
}

int	check_meals(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(data->round));
	if (data->finished == data->nb_philo)
		i = 1;
	pthread_mutex_unlock(&(data->round));
	return (i);
}	

void	*philo_routine(void *pointer_arg)
{
	t_philo	*philo_pointer;
	t_data	*data;

	philo_pointer = (t_philo *)pointer_arg;
	data = (t_data *)philo_pointer->data;
	pthread_mutex_lock(&(data->write_lock));
	pthread_mutex_unlock(&(data->write_lock));
	if (philo_pointer->id % 2 == 0)
		ft_sleep(data->time_eat / 2);
	while (!is_dead(philo_pointer))
	{
		eating(philo_pointer, data);
		if (check_meals(data))
			return (NULL);
		prompt("is sleeping", philo_pointer);
		ft_sleep(philo_pointer->data->time_sleep);
		prompt("is thinking", philo_pointer);
	}
	return (NULL);
}
