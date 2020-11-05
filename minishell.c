#include "minishell.h"

int		ft_is_there(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtok(char *str, const char c)
{
	static char		*stock = NULL;
	char			*ptr;
	int				flg;

	flg = 0;
	ptr = NULL;
	if (str != NULL)
		stock = ft_strdup(str);
	while (*stock != '\0')
	{
		if (flg == 0 && *stock != c)
		{
			flg = 1;
			ptr = stock;
		}
		else if (flg == 1 && *stock == c)
		{
			*stock = '\0';
			stock += 1;
			break ;
		}
		stock += 1;
	}
	return (ptr);
}

char** exec_Function(char *str,char **argv)
{
    int i;
    int counter;
    char strCopy[ft_strlen(str)];
    char *ptr;
    ft_strcpy(strCopy,str);

    i = 0;
    counter = 0;
    ptr = ft_strtok(str,'\n');
    while(ptr != NULL)
    {
        ptr = ft_strtok(NULL,'\n');
        counter++;
    }
    if(!(argv = (char**)malloc((counter+1)*(sizeof(char*)))))
    {
        ft_putendl("error allocated");
        exit(0);
    }

    char* ptrCopy= ft_strtok(strCopy,'\n');
    while(ptrCopy!=NULL)
    {
        if(!(argv[i]=(char*)malloc((sizeof(char)+1)*ft_strlen(ptrCopy))))
        {
            ft_putendl("error allocated");
            for (int j = i-1; j >-1 ; j--) {
                free(argv[j]);
            }
            free(argv);
            exit(0);
        }
        ft_strcpy(argv[i],ptrCopy);
        argv[i][ft_strlen(ptrCopy)]='\0';
        ptrCopy = ft_strtok(NULL,'\n');
        i++;
    }
    argv[counter]=NULL;
    return argv;

}
void    minishell(char *str,char **argv ,char **env)
{
    pid_t id;
    env = NULL;
    argv = exec_Function(str ,argv);
        if (ft_strcmp("cd",str ) == 0)
        {
            struct passwd   *pwd;
            char            *path;
            
            path = argv[1];
            if(path == NULL)
            {
                pwd = getpwuid(getuid());
                path = pwd->pw_dir;
            }
            if (path[0] == '/')
                (*path) = ++(*path);
            chdir(path);
            //error chdir message
        }
        else if (ft_strcmp("exit",str ) == 0)
        {
            exit(1);
        }
        else
        {
            id = fork();
            if (id < 0)
            {
                ft_putendl("fork faild");
                exit(0);
            }
            else if(id == 0) 
            {
                int i = 0;
                execvp(argv[0],argv);
                while (argv[i++])
                    free(argv[i]);
                free(argv);
                if(ft_strcmp(str,"\n")!=0)
		            ft_putendl("command not found\n");
                    exit(1);
             }
            else 
            {
                wait(&id);
            }
        }
}