/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjacob <pjacob@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 13:15:06 by pjacob            #+#    #+#             */
/*   Updated: 2021/08/25 15:46:28 by pjacob           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static void	*philo_life(void *philos)
{
	t_philos	*philo;

	philo = (t_philos *)philos;
	if (philo->philo_id % 2)
		usleep(2000);
	while (philo_lives(philo))
	{
		if (taking_fork(philo) == 0)
			return (NULL);
		if (eating(philo) == 0)
			return (NULL);
		if (sleeping(philo) == 0)
			return (NULL);
		if (thinking(philo) == 0)
			return (NULL);
	}
	return (NULL);
}

static void	init_thd(t_philos *philos, t_param *p, int i)
{
	philos[i].philo_id = i + 1;
	philos[i].right_fork = (i + 1) % p->nb_philo;
	philos[i].left_fork = i;
	philos[i].nb_eat = p->max_eat;
	p->start = my_gettime();
	philos[i].lastmeal = p->start;
	philos->dead = 0;
	philos[i].philo_p = p;
}

static int	lch_join_dest(t_philos *philos, t_param *p, pthread_t *thread)
{
	int	i;

	i = -1;
	while (++i < p->nb_philo)
		pthread_mutex_init(&p->fork[i], NULL);
	i = -1;
	while (++i < p->nb_philo)
		init_thd(philos, p, i);
	i = -1;
	while (++i < p->nb_philo)
		pthread_create(&thread[i], NULL, philo_life, &philos[i]);
	i = -1;
	while (++i < p->nb_philo)
	{
		pthread_join(thread[i], NULL);
		if (philos[i].nb_eat == 0)
			pthread_detach(thread[i]);
		printf("Philo %d dead : %d\n", philos->philo_id, philos->dead);
		if (philos[i].dead)
		{
			i = -1;
			while (++i < p->nb_philo)
				pthread_detach(thread[i]);		
			return (free_stuffs(philos, p, thread));
		}
	}
	return (free_stuffs(philos, p, thread));
}

static int	create_thread(t_param *param)
{
	t_philos	*philos;
	pthread_t	*thread;

	philos = malloc(sizeof(*philos) * param->nb_philo);
	if (!philos)
		return (0);
	thread = malloc(sizeof(pthread_t) * param->nb_philo);
	if (!thread)
		return (0);
	param->fork = malloc(sizeof(pthread_mutex_t) * param->nb_philo);
	if (!param->fork)
		return (0);
	lch_join_dest(philos, param, thread);
	return (0);
}

int	main(int ac, char **av)
{
	t_param			param;

	if (ac == 5 || ac == 6)
	{
		param.nb_philo = ft_atoi(av[1]);
		param.time_to_die = ft_atoi(av[2]);
		param.time_to_eat = ft_atoi(av[3]);
		param.time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			param.max_eat = ft_atoi(av[5]);
		else
			param.max_eat = -1;
		create_thread(&param);
	}
	return (0);
}
