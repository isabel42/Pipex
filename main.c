/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 19:49:04 by itovar-n          #+#    #+#             */
/*   Updated: 2023/03/09 10:41:47 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "pipex.h"


int main(int argc, char **argv)
{
	char *flags1[] = {"-la", NULL};
	char *flags2[] = {"-l", NULL};
	int p1[2]; // c -> p
	if(pipe(p1) == -1)
		return 1;
	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		//Child process 1
		dup2(p1[1], STDOUT_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve("/bin/ls", flags1, NULL);
	}
	int pid2 = fork();
	if (pid2 < 0)
		return 2;
	if (pid2 == 0)
	{
		//Child process 2
		dup2(p1[0], STDIN_FILENO);
		close(p1[0]);
		close(p1[1]);
		execve("/bin/wc", flags2, NULL);
	}
	close(p1[0]);
	close(p1[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return 0;
} 

// int main()
// {
// 	int p1[2]; // c -> p
// 	int p2[2]; // p -> c
// 	pipe(p1);
// 	pipe(p2);
// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		//Child process
// 		close(p1[0]);
// 		close(p2[1]);
// 		int x;
// 		read(p2[0], &x, sizeof(x));
// 		printf("Received %d\n", x);
// 		x *= 4;
// 		write(p1[0], &x, sizeof(x));
// 		printf("Wrote %d\n", x);
// 		close(p1[1]);
// 		close(p2[0]);	
// 	}
// 	else
// 	{
// 		//Parent process
// 		close(p1[1]);
// 		close(p2[0]);
// 		int x = 4;
// 		write(p2[1], &x, sizeof(x));
// 		printf("Wrote %d\n", x);
// 		x *= 4;
// 		read(p1[0], &x, sizeof(x));
// 		printf("Result is %d\n", x);
// 		close(p1[0]);
// 		close(p2[1]);
// 		wait (NULL);	
// 	}
// } 
