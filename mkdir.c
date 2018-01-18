#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <assert.h>



int mkdir_for_parent(char* file_path, mode_t mode) 
{
	assert(file_path && *file_path);
	char* p;
	
	for(p=strchr(file_path+1, '/');p;p=strchr(p+1, '/'))
	{
		*p='\0';
		if(mkdir(file_path, mode)==-1)
		{
			if(errno!=EEXIST) 
			{ 
				*p='/';
				return errno; 
			}
		}
		
		*p='/';
	}
	
	return 0;
}

int main(int argc, char const *argv[])
{

	int verbose_flag=0;
	int parent_flag=0;
	char directories[1000][1000];
	int counter=0;

	if(argc==1)
	{
		printf("%s\n", "mkdir: missing operand");
		return 1;
	}

	//printf("argc: %d\n", argc);

	for(int i=1;i<argc;i++)
	{
		//printf("argv[i]: %s\n", argv[i]);

		if(strcmp(argv[i], "-v")==0 || strcmp(argv[i], "--verbose")==0)
		{
			verbose_flag=1;
		}
		else if(strcmp(argv[i], "-p")==0 || strcmp(argv[i], "--parents")==0)
		{
			parent_flag=1;
		}
		else if(strcmp(argv[i], "-vp")==0 || strcmp(argv[i], "-pv")==0)
		{
			parent_flag=1;
			verbose_flag=1;
		}
		else
		{
			for(int j=0;argv[i][j]!='\0';j++)
			{
				directories[counter][j]=argv[i][j];
			}

			counter++;
		}
	}


	//printf("verbose_flag: %d, parent_flag: %d\n", verbose_flag, parent_flag);


	if(verbose_flag==0 && parent_flag==0)
	{
		int ret=0;
		for(int i=0;i<counter;i++)
		{
			ret=mkdir(directories[i], 0777);

			if(ret==-1)
			{
				int errsv=errno;
				//printf("%d\n", errsv);
				switch(errsv)
				{
					case EACCES: printf("mkdir: cannot create directory '%s': Permission denied\n", directories[i]);
								 break;
					case EEXIST: printf("mkdir: cannot create directory '%s': File exists\n", directories[i]);
								 break;
					case ENOENT: printf("mkdir: cannot create directory '%s': No such file or directory\n", directories[i]);
								 break;
					default: printf("mkdir: cannot create directory '%s': Error\n", directories[i]);
				}
			}
		}
	}
	else if(verbose_flag==1 && parent_flag==0)
	{
		int ret=0;
		for(int i=0;i<counter;i++)
		{
			ret=mkdir(directories[i], 0777);

			if(ret==-1)
			{
				int errsv=errno;
				//printf("%d\n", errsv);
				switch(errsv)
				{
					case EACCES: printf("mkdir: cannot create directory '%s': Permission denied\n", directories[i]);
								 break;
					case EEXIST: printf("mkdir: cannot create directory '%s': File exists\n", directories[i]);
								 break;
					case ENOENT: printf("mkdir: cannot create directory '%s': No such file or directory\n", directories[i]);
								 break;
					default: printf("mkdir: cannot create directory '%s': Error\n", directories[i]);
				}
			}
			else
			{
				printf("mkdir: created directory '%s'\n", directories[i]);
			}
		}
	}
	else if(verbose_flag==0 && parent_flag==1)
	{
		int ret=0;
		for(int i=0;i<counter;i++)
		{
			ret=mkdir_for_parent(directories[i], 0755);

			if(ret!=0)
			{
				
				//printf("%d\n", errsv);
				switch(ret)
				{
					case EACCES: printf("mkdir: cannot create directory '%s': Permission denied\n", directories[i]);
								 break;
					case EEXIST: printf("mkdir: cannot create directory '%s': File exists\n", directories[i]);
								 break;
					case ENOENT: printf("mkdir: cannot create directory '%s': No such file or directory\n", directories[i]);
								 break;
					default: printf("mkdir: cannot create directory '%s': Error\n", directories[i]);
				}
			}

			ret=mkdir(directories[i], 0777);

			if(ret==-1)
			{
				int errsv=errno;
				//printf("%d\n", errsv);
				switch(errsv)
				{
					case EACCES: printf("mkdir: cannot create directory '%s': Permission denied\n", directories[i]);
								 break;
					case EEXIST: printf("mkdir: cannot create directory '%s': File exists\n", directories[i]);
								 break;
					case ENOENT: printf("mkdir: cannot create directory '%s': No such file or directory\n", directories[i]);
								 break;
					default: printf("mkdir: cannot create directory '%s': Error\n", directories[i]);
				}
			}
		}
	}
	else
	{
		int ret=0;
		for(int i=0;i<counter;i++)
		{
			ret=mkdir_for_parent(directories[i], 0755);

			if(ret!=0)
			{
				
				//printf("%d\n", errsv);
				switch(ret)
				{
					case EACCES: printf("mkdir: cannot create directory '%s': Permission denied\n", directories[i]);
								 break;
					case EEXIST: printf("mkdir: cannot create directory '%s': File exists\n", directories[i]);
								 break;
					case ENOENT: printf("mkdir: cannot create directory '%s': No such file or directory\n", directories[i]);
								 break;
					default: printf("mkdir: cannot create directory '%s': Error\n", directories[i]);
				}
			}

			ret=mkdir(directories[i], 0777);

			if(ret==-1)
			{
				int errsv=errno;
				//printf("%d\n", errsv);
				switch(errsv)
				{
					case EACCES: printf("mkdir: cannot create directory '%s': Permission denied\n", directories[i]);
								 break;
					case EEXIST: printf("mkdir: cannot create directory '%s': File exists\n", directories[i]);
								 break;
					case ENOENT: printf("mkdir: cannot create directory '%s': No such file or directory\n", directories[i]);
								 break;
					default: printf("mkdir: cannot create directory '%s': Error\n", directories[i]);
				}
			}
			else
			{
				printf("mkdir: created directory '%s'\n", directories[i]);
			}
		}
	}

	return 0;
}