/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 20:57:50 by mfunyu            #+#    #+#             */
/*   Updated: 2021/01/04 14:11:53 by mfunyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** check_functions:
** 	variadic functions (all very similar)
** 	after third arguments, accpet parameters to pass to the function
** 	using va_list, apply all arguments as a parameter to the function
** 	NULL is used for terminating to read arguments
*/

void	check_read(FILE *fd, ssize_t (*func)(int, void *, size_t), ...)
{
	va_list	ap;
	int		testnbr;
	char	*param;
	char	*buff;
	int		ret;
	int		fildes;
	int		byte;

	testnbr = 0;
	va_start(ap, func);
	while ((param = va_arg(ap, char *)))
	{
		buff = (char *)calloc(40, 1);
		// open a file
		fildes = open(param, O_RDONLY);
		byte = va_arg(ap, int);
		ret = (*func)(fildes, buff, byte);
		buff[byte] = '\0';
		// check return values
		fprintf(fd, "[read%d]: %d | \"%s\"\n", ++testnbr, ret, buff);
		close(fildes);
		free(buff);
		buff = NULL;
	}
	va_end(ap);
}

void	run_check_read(FILE **fd, char *argv1, char *argv2)
{
	ssize_t	(*rea[2])(int, void *, size_t);
	rea[0] = ft_read;
	rea[1] = read;

	for (int i = 0; i < 2 + STDOUT; i++)
	{
		fprintf(fd[i], "\n====== read ========\n");
		check_read(fd[i], rea[i % 2],
			// add filenames and bytes here
			argv1, atoi(argv2),
			"ft_read.s", 20,
			"ft_read.s", 1,
			"ft_strcmp.s", 0,
			"main.c", 10,
			"DNE", 20,
			TERMINATE);
	}
}

void	check_write(int std, FILE *fd, ssize_t (*func)(int, const void *, size_t), ...)
{
	va_list	ap;
	char	*param;
	ssize_t	ret;
	int		testnbr;

	testnbr = 0;
	va_start(ap, func);
	if (!std)
		write(fd->_file, "====== write ======\n", 20);
	while ((param = va_arg(ap, char *)))
	{
		// write to each files
		if (!std)
			write(fd->_file, "[write]: \"", 10);
		else
			write(fd->_file, "\"", 1);
		ret = (*func)(fd->_file, param, strlen(param));
		write(fd->_file, "\"\n", 2);
		fprintf(fd, "[write%d]: %ld\n", ++testnbr, ret);
		// check return values
	}
	va_end(ap);
}

void	run_check_write(FILE **fd, char *argv1)
{
	ssize_t (*wri[2])(int, const void *, size_t);
	wri[0] = ft_write;
	wri[1] = write;

	for (int i = 0; i < 2 + STDOUT; i++)
	{
		fprintf(fd[i], "\n====== write ========\n");
		check_write(STDOUT, fd[i], wri[i % 2],
			// add string argv1eters here
			argv1,
			"abcdef",
			"0",
			"     ",
			"\t",
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
			TERMINATE);
	}
}

void	check_strdup(FILE *fd, char *(*func)(const char *), ...)
{
	va_list	ap;
	char	*param;
	char	*dst;
	int		testnbr;

	testnbr = 0;
	va_start(ap, func);
	while ((param = va_arg(ap, char *)))
	{
		dst = (*func)(param);
		fprintf(fd, "[strdup%d] %s | input: %s | ", ++testnbr, dst, param);
		// fprintf(fd, "[strdup%d] %s (%p) | input: %s (%p) | ", ++testnbr, dst, dst, param, param);
		if (dst != param)
			fprintf(fd, "ADRS DIFF (%p)\n", param);
		free(dst);
		dst = NULL;
	}
	va_end(ap);
}

void	run_check_strdup(FILE **fd, char *argv1)
{
	char *(*dup[2])(const char *);
	dup[0] = ft_strdup;
	dup[1] = strdup;

	for (int i = 0; i < 2 + STDOUT; i++)
	{
		fprintf(fd[i], "\n====== strdup ========\n");
		check_strdup(fd[i], dup[i % 2],
			// add string argv1eters here
			argv1,
			"abcdef",
			"0",
			"     ",
			"\t",
			"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
			TERMINATE);
	}
}

void	check_strcmp(FILE *fd, int (*func)(const char *, const char *), ...)
{
	va_list	ap;
	char	*s1;
	char	*s2;
	int		testnbr;

	testnbr = 0;
	va_start(ap, func);
	while ((s1 = va_arg(ap, char *)))
	{
		s2 = va_arg(ap, char *);
		fprintf(fd, "[strcmp%d] %d | %s, %s\n", ++testnbr, (*func)(s1, s2), s1, s2);
	}
	va_end(ap);
}

void	run_check_strcmp(FILE **fd, char *argv1, char *argv2)
{
	int (*cmp[2])(const char *, const char *);
	cmp[0] = ft_strcmp;
	cmp[1] = strcmp;
	for (int i = 0; i < 2 + STDOUT; i++)
	{
		fprintf(fd[i], "\n====== strcmp ========\n");
		check_strcmp(fd[i], cmp[i % 2],
			//add paris of string argv1s here
			argv1, argv2,
			"abc", "abc",
			"abc", "abcd",
			"abcd", "abc",
			"abcz", "abc",
			"z", "abc",
			"12345678901234567890zz", "12345678901234567890z",
			"12345678901234567890z", "12345678901234567890z",
			TERMINATE);
	}
}


void	check_strcpy(FILE *fd, char *(*func)(char *, const char *), ...)
{
	va_list	ap;
	char	*param;
	char	*dst;
	int		testnbr;

	testnbr = 0;
	va_start(ap, func);
	if (!(dst = (char *)calloc(sizeof(char), 30)))
		exit(EXIT_FAILURE);
	while ((param = va_arg(ap, char *)))
	{
		memset(dst, 'a', 20);
		fprintf(fd, "[strcpy%d] src = \"%s\" (%p)\n", ++testnbr, param, param);
		fprintf(fd, "          (before) dst = \"%s\" (%p)\n", dst, dst);
		(*func)(dst, param);
		fprintf(fd, "          (after)  dst = \"%s\" (%p)\n", dst, dst);
	}
	free(dst);
	dst = NULL;
	va_end(ap);
}

void	run_check_strcpy(FILE **fd, char *argv1)
{
	char *(*cpy[2])(char *, const char *);
	cpy[0] = ft_strcpy;
	cpy[1] = strcpy;

	for (int i = 0; i < 2 + STDOUT; i++)
	{
		fprintf(fd[i], "\n====== strcpy ======\n");
		check_strcpy(fd[i], cpy[i % 2],
			// add string argv1eters here
			argv1,
			"aaaaaaaaaaaaaaaaaa",
			"       ",
			TERMINATE);
	}
}

void	check_strlen(FILE *fd, size_t (*func)(const char *), ...)
{
	va_list	ap;
	char	*param;
	int		testnbr;

	testnbr = 0;
	va_start(ap, func);
	while ((param = va_arg(ap, char *)))
	{
		fprintf(fd, "[strlen%d] %ld | input: \"%s\"\n", ++testnbr, func(param), param);
	}
	va_end(ap);
}

void	run_check_strlen(FILE **fd, char *argv1)
{
	size_t	(*len[2])(const char *);
	len[0] = ft_strlen;
	len[1] = strlen;
	for (int i = 0; i < 2 + STDOUT; i++)
	{
		if (i % 2 == 0)
			fprintf(fd[i], "\n====== ft_strlen ======\n");
		else
			fprintf(fd[i], "\n====== strlen ======\n");
		check_strlen(fd[i], len[i % 2],
			// add string parameters here
			argv1,
			"abcdef",
			TERMINATE);
	}
}

int		main(int ac, char **av)
{
	FILE	*fd[4];
	char 	*argv1;
	char 	*argv2;

	if (ac < 2)
		argv1 = "comandline arg1";
	else
	{
		argv1 = av[1];
		if (ac < 3)
			argv2 = "2";
		else
			argv2 = av[2];
	}


	if ((fd[0] = fopen("actual.log", "w")) == NULL)
		exit(EXIT_FAILURE);
	if ((fd[1] = fopen("expected.log", "w")) == NULL)
		exit(EXIT_FAILURE);
	fd[2] = stdout;
	fd[3] = stdout;

	///ft_strlen vs strlen /////
	run_check_strlen(fd, argv1);

	// ft_strcpy vs strcpy ////
	run_check_strcpy(fd, argv1);

	// ft_strcmp vs strcmp ///
	run_check_strcmp(fd, argv1, argv2);

	// ft_strdup vs strdup ///
	run_check_strdup(fd, argv1);

	///////////// ft_write vs write ///////////////////
	run_check_write(fd, argv1);

	///////////// ft_read vs read ///////////////////
	run_check_read(fd, argv1, argv2);

	return (0);
}
