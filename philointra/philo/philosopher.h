/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rencarna <rencarna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 15:52:36 by russelenc         #+#    #+#             */
/*   Updated: 2023/09/07 14:17:33 by rencarna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		philo_thread;
	int				id;
	int				max_meals;
	int				l_fork;
	int				r_fork;
	long int		last_eat;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				nb_meals;
	int				dead;
	int				finished;
	t_philo			*philos;
	long int		time_die;
	long int		time_eat;
	long int		time_sleep;
	long int		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eat_status;
	pthread_mutex_t	round;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	died;
}	t_data;

//		ERROR		//
void		ft_exit(t_data *data);
int			ft_error(char *str, t_data *data);
int			check_arg(char **av);

t_data		*init_struct(int ac, char **av);
int			ft_strcmp(char *s1, char *s2);

//		philo life		// 
long int	timefonction(void);
void		ft_sleep(long int ms);
void		eating(t_philo *philo, t_data *data);

//		utils		//
long int	ft_atoi(const char *str);
int			ft_isdigit(int c);
void		*init_data(t_data *data, int ac, char **av);

//	thread routine checker	// 
void		*philo_routine(void *pointerarg);
int			check_meals(t_data *data);
void		prompt(char *str, t_philo *philo);
void		onephilo(long int time_die);
int			check_death(t_data *data);
void		promptded(char *str, t_philo *philo);
int			is_dead(t_philo *philo);
#endif