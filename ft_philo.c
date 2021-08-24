/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 13:15:06 by pjacob            #+#    #+#             */
/*   Updated: 2021/08/24 12:14:24 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static void	*philo_life(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	while (philo_lives(philo))
	{
		taking_fork(philo);
		if (!eating(philo))
			return (NULL);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

static void	lch_thd(t_philos *philos, t_param *p, pthread_t *thread, int i)
{
	pthread_mutex_init(&p->fork[i], NULL);
	pthread_mutex_unlock(&p->fork[i]);
	philos[i].philo_id = i;
	philos[i].right_fork = i + 1;
	if (i == 0)
		philos[i].left_fork = p->nb_philo;
	else
		philos[i].left_fork = i;
	philos->lf_status = 0;
	philos->rf_status = 0;
	philos->died = 0;
	philos[i].nb_eat = p->max_eat;
	p->start = my_gettime();
	philos[i].philo_p = p;
	pthread_create(&thread[i], NULL, philo_life, &philos[i]);
}

static void	lch_join_dest(t_philos *philos, t_param *p, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < p->nb_philo)
		lch_thd(philos, p, &thread[i], i);
	i = -1;
	while (++i < p->nb_philo)
	{
		pthread_join(thread[i], NULL);
		printf("philo[%d]->max_eat : %d\n", philos[i].philo_id + 1, philos[i].nb_eat);
		if (philos[i].nb_eat == 0)
			pthread_detach(thread[i]);
	}
	i = -1;
	while (++i < p->nb_philo)
		pthread_mutex_destroy(&p->fork[i]);
	free(p->fork);
	free(philos);
	free(thread);
}

static void	create_thread(t_param *param)
{
	t_philos	*philos;
	pthread_t	*thread;

	philos = malloc(sizeof(*philos) * param->nb_philo);
	if (!philos)
		return ;
	thread = malloc(sizeof(pthread_t) * param->nb_philo);
	if (!thread)
		return ;
	param->fork = malloc(sizeof(pthread_mutex_t) * param->nb_philo);
	if (!param->fork)
		return ;
	lch_join_dest(philos, param, thread);
}

int	main(int ac, char **av)
{
	t_param			param;

	if (ac == 5 || ac == 6)
	{
		param.nb_philo = ft_atoi(av[1]);
		param.time_to_die = milli_to_micro(ft_atoi(av[2]));
		param.time_to_eat = milli_to_micro(ft_atoi(av[3]));
		param.time_to_sleep = milli_to_micro(ft_atoi(av[4]));
		if (ac == 6)
			param.max_eat = ft_atoi(av[5]);
		else
			param.max_eat = 0;
		create_thread(&param);
	}
	return (0);
}
