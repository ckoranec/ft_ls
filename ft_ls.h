#ifndef FT_LS_H
# define FT_LS_H
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>

typedef struct stat t_stat;
typedef struct dirent t_dirant;

typedef struct s_flags
{
	int l;
	int a;
	int r;
	int bigr;
	int t;
} t_flags;

typedef struct	s_file
{
	t_stat	s;
	char *path;
	struct s_file	*next;
	struct s_file	*back;
}				t_file;
#endif
