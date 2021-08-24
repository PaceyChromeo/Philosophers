/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 13:08:00 by pjacob            #+#    #+#             */
/*   Updated: 2021/08/24 12:13:29 by pjacob           ###   ########.fr       */
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
	int				start;
	pthread_mutex_t	*fork;
}				t_param;

typedef struct s_philosophers
{
	t_param			*philo_p;
	int				philo_id;
	int				left_fork;
	int				right_fork;
	int				lf_status;
	int				rf_status;
	int				nb_eat;
	int				timestamp;
	int				died;
}				t_philos;

int		ft_atoi(const char *nptr);
void	taking_fork(t_philos *philo);
void	sleeping(t_philos *philo);
int		eating(t_philos *philo);
void	thinking(t_philos *philo);
int		philo_lives(t_philos *philo);
int		my_gettime(void);
int		milli_to_micro(int milli);
int		micro_to_milli(int micro);
int		timestamp(int start);

#endif
