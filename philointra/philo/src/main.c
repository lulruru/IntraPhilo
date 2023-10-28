/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:45:35 by rencarna          #+#    #+#             */
/*   Updated: 2023/09/07 14:03:35 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosopher.h"

long int	timefonction(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 + now.tv_usec / 1000));
}

void	ft_sleep(long int ms)
{
	long int	time ;

	time = timefonction();
	while (timefonction() - time < ms)
		usleep(200);
}

void	onephilo(long int time_die)
{
	printf("0\t1 has taken a fork\n");
	ft_sleep(time_die);
	printf("%lu\t1 died\n", time_die);
}

void	ft_philo(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&(data->write_lock));
	while (++i < data->nb_philo)
	{
		data->philos->last_eat = timefonction();
		if (pthread_create(&data->philos[i].philo_thread, NULL, \
			&philo_routine, (void *)&data->philos[i]))
			return ;
	}
	data->start_time = timefonction();
	pthread_mutex_unlock(&(data->write_lock));
	usleep((data->time_die) * 1000);
	while (check_death(data) == 0)
		usleep(5000);
	i = -1;
	while (++i < data->nb_philo)
		if (pthread_join(data->philos[i].philo_thread, NULL))
			return ;
	return ;
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (1);
	data = NULL;
	if (check_arg(av))
	{
		if (ft_atoi(av[1]) == 0)
			return (printf("Error Need a philo\n"));
		if (ft_atoi(av[1]) == 1)
			return (onephilo(ft_atoi(av[2])), 1);
		data = init_struct(ac, av);
		ft_philo(data);
		ft_exit(data);
	}
	return (0);
}
