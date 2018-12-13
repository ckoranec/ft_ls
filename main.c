/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkertgat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:00:43 by jkertgat          #+#    #+#             */
/*   Updated: 2018/12/12 20:03:11 by jkertgat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

void		print_l(t_file *head)
{
	struct passwd *s_pw;
	struct group *s_gr;
		while(head)
		{
			s_gr = getgrgid(head->s.st_gid);
			s_pw = getpwuid(head->s.st_uid);
			printf( (S_ISDIR(head->s.st_mode)) ? "d" : "-");
			printf( (head->s.st_mode & S_IRUSR) ? "r" : "-");
			printf( (head->s.st_mode & S_IWUSR) ? "w" : "-");
			printf( (head->s.st_mode & S_IXUSR) ? "x" : "-");
			printf( (head->s.st_mode & S_IRGRP) ? "r" : "-");
			printf( (head->s.st_mode & S_IWGRP) ? "w" : "-");
			printf( (head->s.st_mode & S_IXGRP) ? "x" : "-");
			printf( (head->s.st_mode & S_IROTH) ? "r" : "-");
			printf( (head->s.st_mode & S_IWOTH) ? "w" : "-");
			printf( (head->s.st_mode & S_IXOTH) ? "x" : "-");
			printf("  %d %s  %s",head->s.st_nlink,s_pw->pw_name,s_gr->gr_name);
			printf("  %lld  %s",head->s.st_size,ctime(&head->s.st_ctime));
			printf("%s",head->path);
			printf("\n");
			head = head->next;
		}
}

void	print_ls_yo(t_file *head, t_flags *flags)
{
//	while(head != NULL)
//	{
		if (flags->l == 1)
			print_l(head);
/*		else if (flags->a == 1)
			return (print_a());
		else if (flags->r == 1)
			return (print_r());
		else if (flags->bigr == 1)
			return (print_bigr());
		else if (flags->t == 1)
			return (print_time());
*/
//      printf("%s\n",head->path);
//		head = head->next;
//	}
}

void		addtolast(t_file **head, t_stat s, char *path)
{
	t_file *last;
	t_file *new;

	if(!(new = malloc(sizeof(t_file))))
		return;
	new->s = s;
	new->path = path;
	if(!(*head))
	{
		new->back = NULL;
		*head = new;
		return;
	}
	last = (*head);
	while(last->next != NULL)
		last = last->next;
	last->next = new;
	new->back = last;
}

void init(t_flags *flags)
{
	flags->l = 0;
	flags->a = 0;
	flags->r = 0;
	flags->bigr = 0;
	flags->t = 0;
}

void     parse(int ac, char **av, t_flags *flags)
{
    int     i;

    i = 0;
	init(flags);
    while (i++ < ac - 1)
    {
		if (av[i][0] != '-')
            break;
		if (av[i][0] == '-')
            while(*av[i]++)
            {
				if (*av[i] == 'l')
					flags->l = 1;
				else if (*av[i] == 'a')
					flags->a = 1;
				else if (*av[i] == 'r')
					flags->r = 1;
				else if (*av[i] == 't')
					flags->t = 1;
            }
    }
}


int main(int ac, char **av)
{
    DIR *dir;
    t_dirant *dp;
    t_file *fil;
    t_stat tmp;
	t_flags flags;

	parse(ac,av,&flags);
    if(!(dir = opendir(".")))
	{
		printf("no such directory");
		return(0);
	}
    while((dp = readdir (dir)) != NULL)
    {
        lstat(dp->d_name, &tmp);
		addtolast(&fil,tmp,dp->d_name);
    }
    closedir(dir);
    print_ls_yo(fil,&flags);
    return(0);
}
