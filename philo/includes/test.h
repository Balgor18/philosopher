/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:19:13 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/11 17:19:38 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// struct pthread
// {
// 	struct machdep_pthread	machdep_data;
// 	enum pthread_state		state;
// 	pthread_attr_t			attr;

// 	/* Signal interface */
// 	sigset_t				sigmask;
// 	sigset_t				sigpending;

// 	/* Time until timeout */
// 	struct timespec			wakeup_time;

// 	/* Cleanup handlers Link List */
// 	struct pthread_cleanup 	*cleanup;

// 	/* Join queue for waiting threads */
// 	struct pthread_queue	join_queue;

// 	/* Queue thread is waiting on, (mutexes, cond. etc.) */
// 	struct pthread_queue	*queue;

// 	/*
// 	 * Thread implementations are just multiple queue type implemenations,
// 	 * Below are the various link lists currently necessary
// 	 * It is possible for a thread to be on multiple, or even all the
// 	 * queues at once, much care must be taken during queue manipulation.
// 	 *
// 	 * The pthread structure must be locked before you can even look at
// 	 * the link lists.
// 	 */

// 	struct pthread			*pll;		/* ALL threads, in any state */
// 	/* struct pthread		*rll;		 Current run queue, before resced */
// 	struct pthread			*sll;		/* For sleeping threads */
// 	struct pthread			*next;		/* Standard for mutexes, etc ... */
// 	/* struct pthread			*fd_next;	 For kernel fd operations */

// 	int						fd;			/* Used when thread waiting on fd

// 	semaphore				lock;

// 	/* Data that doesn't need to be locked */
// 	void 					*ret;
// 	int						error;
// 	const void				**specific_data;
// };

// typedef struct pthread *		pthread_t;
