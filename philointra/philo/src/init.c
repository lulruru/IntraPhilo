/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 17:18:26 by russelenc         #+#    #+#             */
/*   Updated: 2023/09/07 14:10:46 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->dead = 0;
	while (++i < data->nb_philo)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].l_fork = i;
		data->philos[i].r_fork = i + 1;
		if (i + 1 == data->nb_philo)
			data->philos[i].r_fork = 0;
		data->philos[i].max_meals = data->nb_meals;
		data->philos[i].last_eat = 0;
	}
}

void	*allocate_struct(t_data *data)
{
	int	i;

	i = -1;
	data->eat_status = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->eat_status)
		return (ft_error("Error malloc\n", data), NULL);
	while (++i < data->nb_philo)
		pthread_mutex_init(&(data->eat_status[i]), NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (ft_error("Error malloc\n", data), NULL);
	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
		return (ft_error("Error malloc\n", data), NULL);
	return (NULL);
}

void	*init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]);
	data->time_die = (long int)ft_atoi(av[2]);
	data->time_eat = (long int)ft_atoi(av[3]);
	data->time_sleep = (long int)ft_atoi(av[4]);
	if (ac == 6)
		data->nb_meals = ft_atoi(av[5]);
	else
		data->nb_meals = -1;
	if (data->nb_philo <= 0 || data->time_die < 0 \
		|| data->time_eat < 0 || data->time_sleep < 0)
		return (ft_error("error input", NULL), NULL);
	data->dead = 0;
	data->finished = 0;
	return (0);
}

void	*init_mute(t_data *data)
{
	pthread_mutex_init(&(data->died), NULL);
	pthread_mutex_init(&(data->write_lock), NULL);
	pthread_mutex_init(&(data->round), NULL);
	return (NULL);
}

t_data	*init_struct(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_error("Error allocating", data);
	init_data(data, ac, av);
	allocate_struct(data);
	init_mute(data);
	init_philos(data);
	return (data);
}
