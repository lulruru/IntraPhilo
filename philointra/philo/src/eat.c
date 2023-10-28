/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:15:49 by rencarna          #+#    #+#             */
/*   Updated: 2023/09/06 16:54:31 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	take_forks(t_philo *philo, t_data *data)
{
	if (philo->id == data->nb_philo)
		pthread_mutex_lock(&(philo->data->forks[philo->r_fork]));
	else
		pthread_mutex_lock(&(philo->data->forks[philo->l_fork]));
	prompt("has taken a fork", philo);
	if (philo->id == data->nb_philo)
		pthread_mutex_lock(&(philo->data->forks[philo->l_fork]));
	else
		pthread_mutex_lock(&(philo->data->forks[philo->r_fork]));
	prompt("has taken a fork", philo);
}

void	drop_forks(t_philo *philo, t_data *data)
{
	if (philo->id == data->nb_philo)
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
		pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->l_fork]));
		pthread_mutex_unlock(&(philo->data->forks[philo->r_fork]));
	}
}

void	eating(t_philo *philo, t_data *data)
{
	take_forks(philo, data);
	pthread_mutex_lock(&(data->eat_status[philo->id - 1]));
	philo->last_eat = timefonction();
	pthread_mutex_unlock(&(data->eat_status[philo->id - 1]));
	prompt("is eating", philo);
	ft_sleep(philo->data->time_eat);
	(philo->max_meals)--;
	drop_forks(philo, data);
	if (philo->max_meals == 0)
	{
		pthread_mutex_lock(&(data->round));
		(data->finished)++;
		pthread_mutex_unlock(&(data->round));
	}
}
