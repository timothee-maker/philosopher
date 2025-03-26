/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnolent <tnolent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:28:08 by tnolent           #+#    #+#             */
/*   Updated: 2025/03/20 11:09:13 by tnolent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#define TIMES_TO_COUNT 21000
void *thread_routine(void *data);

int main(void)
{
 pthread_t tid1;
 pthread_t tid2;
 t_counter counter;
 
 counter.count = 0;
 pthread_mutex_init(&counter.count_mutex, NULL);
 printf("Main: Expected count is %s%u%s\n", GREEN,
     2 * TIMES_TO_COUNT, NORMAL);
 pthread_create(&tid1, NULL, thread_routine, &counter);
 printf("Main: Created first thread [%ld]\n", tid1);
 pthread_create(&tid2, NULL, thread_routine, &counter);
 printf("Main: Created second thread [%ld]\n", tid2);
 pthread_join(tid1, NULL);
 printf("Main: Joined first thread [%ld]\n", tid1);
 pthread_join(tid2, NULL);
 printf("Main: Joined second thread [%ld]\n", tid2);
 if (counter.count != (2 * TIMES_TO_COUNT))
  printf("%sMain: ERROR ! Total count is %u%s\n",
     RED, counter.count, NORMAL);
 else
  printf("%sMain: OK. Total count is %u%s\n",
     GREEN, counter.count, NORMAL);
 pthread_mutex_destroy(&counter.count_mutex);
 return (0);
}

void *thread_routine(void *data)
{
    pthread_t tid;
    t_counter *counter;

    unsigned int i; 
    tid = pthread_self();
    counter = (t_counter *)data;
    pthread_mutex_lock(&counter->count_mutex);
    printf("%sThread [%ld]: Count at thread start = %u.%s\n",
     YELLOW, tid, counter->count, NORMAL);
    pthread_mutex_unlock(&counter->count_mutex);
    i = 0;
    while (i < TIMES_TO_COUNT)
    {
     pthread_mutex_lock(&counter->count_mutex);
     counter->count++;
    //  usleep(10);
     pthread_mutex_unlock(&counter->count_mutex);
     i++;
    }
    pthread_mutex_lock(&counter->count_mutex);
    printf("%sThread [%ld]: Final count = %u.%s\n",
     BYELLOW, tid, counter->count, NORMAL);
    pthread_mutex_unlock(&counter->count_mutex);
    return (NULL);
}
