/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 13:08:00 by pjacob            #+#    #+#             */
/*   Updated: 2021/09/20 12:41:32 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/errno.h>
# include <pthread.h>
# include <stdio.h>

# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

typedef struct s_param
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	long			start_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
}				t_param;

typedef struct s_philosophers
{
	t_param	*philo_p;
	int		philo_id;
	int		left_fork;
	int		right_fork;
	int		nb_eat;
	int		dead;
	long	lastmeal;
}				t_philos;

int		ft_atoi(const char *nptr);
int		taking_fork(t_philos *philo);
int		eating(t_philos *philo);
int		sleeping(t_philos *philo);
int		thinking(t_philos *philo);
int		philo_lives(t_philos *philo);
long	my_gettime(void);
void	ft_usleep(int milli);
int		free_stuffs(t_philos *philos, t_param *p, pthread_t *thread);
void	*time_control(void *philos);

#endif
