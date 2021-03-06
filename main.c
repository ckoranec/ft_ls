/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkertgat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 20:00:43 by jkertgat          #+#    #+#             */
/*   Updated: 2018/12/16 19:55:00 by jkertgat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"
#include <string.h>

void swap(t_file *head) 
{ 
    char *temp = head->path; 
    head->path = head->next->path; 
    head->next->path= temp; 
} 

void bubblesort(t_file *head) 
{ 
    int swapped; 
    t_file *ptr1; 
    t_file *lptr = NULL; 
   
	swapped = 1;
    while(swapped)
    { 
        swapped = 0; 
        ptr1 = head; 
   
        while (ptr1->next != lptr) 
        { 
            if (ft_strcmp(head->path,head->next->path)> 0) 
            {  
                swap(ptr1); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
} 

t_file *lst_swap(t_file *p1, t_file *p2)
{
	p1->next = p2->next;
	p2->next = p1;
	return (p2);
}

t_file *lst_sort_ascii(t_file *head)
{

	if (!head)
		return (NULL);
	if (head->next && ft_strcmp(head->path, head->next->path) > 0)
		head = lst_swap(head, head->next);
	head->next = lst_sort_ascii(head->next);
	if (head->next && ft_strcmp(head->path, head->next->path) > 0)
	{
		head = lst_swap(head, head->next);
		head->next = lst_sort_ascii(head->next);
	}
	return (head);
}



void		print_l(t_file *head,t_flags *flags)
{
	struct passwd *s_pw;
	struct group *s_gr;

	lst_sort_ascii(head);
while(head)
	{
		if (head->path)
		{			
			if (flags->a == 0 && head->path[0] != '.')
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
			printf("  %2hu %s  %s",head->s.st_nlink,s_pw->pw_name,s_gr->gr_name);
			printf("  %7lld  %.6s %.5s",head->s.st_size,ctime(&head->s.st_mtime) + 4,ctime(&head->s.st_mtime) + 11);
			printf(" %s",head->path);
			printf("\n");
			}
		}
		if(flags->a == 1)
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
			printf("  %2hu %s  %s",head->s.st_nlink,s_pw->pw_name,s_gr->gr_name);
			printf("  %7lld  %.6s %.5s",head->s.st_size,ctime(&head->s.st_mtime) + 4,ctime(&head->s.st_mtime) + 11);
			printf(" %s",head->path);
			printf("\n");
		}
		head = head->next;
	}
}

void	print_ls_yo(t_file *head, t_flags *flags)
{
//	while(head != NULL)
//	{
		if (flags->l == 1)
			print_l(head,flags);
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
		head = head->next;
//	}
}

void		addtolast(t_file **head, t_stat s, char *path)
{
	t_file *last;
	t_file *new;

	if(!(new = ft_memalloc(sizeof(t_file))))
		return;
	if(!(new->path = ft_memalloc(sizeof(char*))))
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
	while(last && last->next)
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
    print_ls_yo(fil,&flags);
    closedir(dir);
    return(0);
}
