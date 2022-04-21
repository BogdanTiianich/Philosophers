/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbecki <hbecki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:51:30 by hbecki            #+#    #+#             */
/*   Updated: 2022/04/21 21:48:34 by hbecki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int static	ft_atoi_help(const char *s, int *ngtv, int *i)
{
	int	a;

	*i = 0;
	*ngtv = 0;
	while (((s[*i] == 32) || (s[*i] == 9) || ((s[*i] >= 10) \
	&& (s[*i] <= 13))) && (s[*i] != '\0'))
		(*i)++;
	if (((s[*i] == '-') || (s[*i] == '+')) && (s[*i] != '\0'))
	{
		if (s[*i] == '-')
			(*ngtv)++;
		(*i)++;
	}
	a = *i + *ngtv - *i;
	return (a);
}

int	ft_atoi(const char *s)
{
	int	i;
	int	result;
	int	ngtv;
	int	count;

	result = 0;
	count = 0;
	ngtv = ft_atoi_help(s, &ngtv, &i);
	while (((s[i] >= '0') && (s[i] <= '9')) && (s[i] != '\0'))
	{
		count++;
		result = result * 10 + s[i] - '0';
		i++;
	}
	if (count >= 19)
		return (-1 * (1 - ngtv));
	if (ngtv % 2 != 0)
		result *= -1;
	return (result);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	if (s == NULL || fd < 0)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_free(void **pointer)
{
	if (*pointer != NULL)
	{
		free(*pointer);
		*pointer = NULL;
	}
}

long	ft_time_diff_from_now_ms(t_timeval t1)
{
	long		diff;
	t_timeval	t2;

	gettimeofday(&t2, NULL);
	diff = (t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec);
	return (diff);
}

long	ft_time_from_start(t_timeval t)
{
	return (ft_time_diff_from_now_ms(t) / 1000);
}

void	ft_errors(t_rules *rules)
{
	write(2, "got in error function\n", 22);
	ft_putstr_fd(strerror(errno), 2);
	// ft_free(&rules);
	exit(1);
}

t_rules	*init_rules(int argc, char **argv)
{
	t_rules		*rules;
	t_timeval	time;

	rules = (t_rules *)malloc(sizeof(t_rules));
	if (rules == NULL)
	{
		ft_errors(rules);
	}
	rules->number_of_phils = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	gettimeofday(&time, NULL);
	rules->start_time = time;
	if (argc == 6)
		rules->im_full_times = ft_atoi(argv[5]);
	else
		rules->im_full_times = -1;
	return (rules);
}

// int	waiting_for_forks(t_data data)
// {
// 	int	flag;

// 	flag = 0;
// 	while (1)
// 	{
// 		if (ft_check_if_dead(data) == 1)
// 			return (1);
// 		if ((*data.avail_forks)[data.philos->forks_i_need[0]] == 1 && (*data.avail_forks)\
// 		[data.philos->forks_i_need[1]] == 1)
// 		{
// 			pthread_mutex_lock(data.mutex);
// 			if ((*data.avail_forks)[data.philos->forks_i_need[0]] == 1 && (*data.avail_forks)\
// 			[data.philos->forks_i_need[1]] == 1)
// 				break ;
// 			else
// 				pthread_mutex_unlock(data.mutex);
// 		}
// 		if (flag == 0)
// 		{
// 			printf("%lu  %lu is thinking\n", ft_time_from_start(data.rules->start_time), data.philos->number);
// 			flag = 1;
// 		}
			
// 	}
// 	return (0);
// }

int ft_check_if_dead(t_data data)
{
	if (ft_time_diff_from_now_ms(data.philos->last_dinner_time) \
	>= data.rules->time_to_die)
	{
		printf("%lu  %lu died\n", \
	ft_time_from_start(data.rules->start_time), data.philos->number);
		return (1);
	}
	else
		return (0);
}

int ft_philo_eating(t_data data)
{
	t_timeval	start_eating_time;
	t_timeval	finished_eating_time;

	gettimeofday(&start_eating_time, NULL);
	printf("%lu  %lu is eating\n", \
	ft_time_from_start(data.rules->start_time), data.philos->number);
	while (ft_time_diff_from_now_ms(start_eating_time) < \
	data.rules->time_to_eat)
	{
		if (ft_check_if_dead(data) == 1)
			return (1);
	}
	gettimeofday(&finished_eating_time, NULL);
	data.philos->last_dinner_time = finished_eating_time;
	return (0);
}

int	ft_philo_sleeping(t_data data)
{
	t_timeval	start_sleeping_time;

	gettimeofday(&start_sleeping_time, NULL);
	printf("%lu  %lu is sleeping\n", \
	ft_time_from_start(data.rules->start_time), data.philos->number);
	while (ft_time_diff_from_now_ms(start_sleeping_time) < \
	data.rules->time_to_sleep)
	{	
		if (ft_check_if_dead(data) == 1)
			return (1);
	}
	return (0);
}
int	ft_start_dinning(t_data data)
{
	int	life_and_death;
	
	// if (waiting_for_forks(data) == 1)
	// 	return (1);
	sem_wait(data.semaphore);
	printf("%lu  %lu has taken fork\n", \
	ft_time_from_start(data.rules->start_time), data.philos->number);
	
	// pthread_mutex_unlock(data.mutex);
	life_and_death = ft_philo_eating(data);
	sem_post(data.semaphore);

	if (life_and_death == 1)
		return (1);
	return (0);
}

void*	philos_life(void *data)
{
	int	life_and_death;
	int	quantity_of_dinners;

	quantity_of_dinners = 0;
	while (1)
	{
		life_and_death = ft_start_dinning(*(t_data *)data);
		if (life_and_death == 1)
			return (1);
		quantity_of_dinners++;
		// printf("%lu th philosopher has ate %lu times\n", \
		// (*(t_data *)data).philos->number, quantity_of_dinners);
		if (quantity_of_dinners >= (*(t_data *)data).rules->im_full_times)
			break ;
		life_and_death = ft_philo_sleeping(*(t_data *)data);
		if (life_and_death == 1)
			return (1);
		if ((*(t_data *)data).rules->im_full_times == -1)
			break ;
	}
}

// void	ft_define_forks_i_need(t_philos *philos, int number_of_philos)
// {
// 	t_vars	vars;

// 	if (philos->number == 0)
// 		philos->forks_i_need[0] = number_of_philos - 1;
// 	else
// 		philos->forks_i_need[0] = philos->number - 1;
// 	philos->forks_i_need[1] = philos->number;
// }

void	ft_run_game(t_data **data, pthread_t *threads, t_rules *rules, int **avail_forks)
{
	t_vars			vars;
	t_timeval		curr;
	pthread_mutex_t	mutex;

	vars.i = 0;
	pthread_mutex_init(&mutex, NULL);
	while (vars.i < rules->number_of_phils)
	{
		data[vars.i] = (t_data *)malloc(sizeof(t_data));
		if (data[vars.i] == NULL)
		{
			ft_errors(rules);
		}
		// (*data[vars.i]).avail_forks = avail_forks;
		(*data[vars.i]).rules = rules;
		// (*data[vars.i]).mutex = &mutex;
		(*data[vars.i]).philos = (t_philos *)malloc(sizeof(t_philos));
		if ((*data[vars.i]).philos == NULL)
		{
			ft_errors(rules);
		}
		gettimeofday(&curr, NULL);
		(*data[vars.i]).philos->number = vars.i;
		(*data[vars.i]).philos->last_dinner_time = curr;
		(*data[vars.i]).philos->alive = 1;

		// pthread_create(&threads[vars.i], NULL, &philos_life, data[vars.i]);
		vars.i++;
	}
	vars.i = 0;
	while (vars.i < rules->number_of_phils)
	{
		pthread_join(threads[vars.i], NULL);
		vars.i++;
	}
}

void	ft_fork_test(sem_t *semaphore, t_rules *rules, int **idss)
{
	int	i;
	int	id;
	int	*ids;

	i = 0;
	ids = (int *)malloc(sizeof(int) * rules->number_of_phils);
	while (i < rules->number_of_phils)
	{
		id = fork();
		if (id == 0)
		{
			sem_wait(semaphore);
			printf("process number %d is waiting\n", getpid());
			sleep(2);
			sem_post(semaphore);
			exit (1);
;		}
		ids[i] = id;
		i++;
	}
	*idss = ids;
}

int	ft_waiter(int num_of_processes, int *ids)
{
	int	i;

	i = 0;
	while (i < num_of_processes)
	{
		if (waitpid(ids[i], NULL, 0) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules		*rules;
	pthread_t	*threads;
	t_data		**data;
	t_vars		vars;
	int			*avail_forks;
	sem_t		*semaphore;
	int			*ids;

	
	if (argc < 5 || argc > 6)
	{
		printf("Invalid number of args\n");
		return (1);
	}
	rules = NULL;
	rules = init_rules(argc, argv);
	if (rules == NULL)
	{
		ft_errors(rules);
	}
	sem_unlink(SEMAPHORE_NAME);
	semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, 0666, rules->number_of_phils / 2);
	if (semaphore == SEM_FAILED)
	{
		printf("Semfailed %d\n", rules->number_of_phils);
		exit(1);
	}
	threads = (pthread_t *)malloc(sizeof(pthread_t) * \
	(rules->number_of_phils));
	if (threads == NULL)
	{
		ft_errors(rules);
	}
	data = (t_data **)malloc(sizeof(t_data) * (rules->number_of_phils + 1));
	if (data == NULL)
	{
		ft_errors(rules);
	}
	avail_forks = (int *)malloc(sizeof(int) * rules->number_of_phils);
	if (avail_forks == NULL)
	{
		ft_errors(rules);
	}
	vars.i = 0;
	while (vars.i < rules->number_of_phils)
	{
		avail_forks[vars.i] = 1;
		vars.i++;
	}
	data[rules->number_of_phils] = NULL;
	// ft_run_game(data, threads, rules, &avail_forks);
	ft_fork_test(semaphore, rules, &ids);
	
	ft_waiter(rules->number_of_phils, ids);

	// sem_close(semaphore);
	printf("finished\n");
	
	return (0);
}
