#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
	int directory_flag=0;
	int all_flag=0;
	char directories[1000][1000];
	int counter=0;

	//printf("%s\n", "came to ls");

	for(int i=1;i<argc;i++)
	{
		if(strcmp(argv[i],"-a")==0 || strcmp(argv[i],"--all")==0)
		{
			all_flag=1;
		}
		else if(strcmp(argv[i],"-d")==0 || strcmp(argv[i],"--directory")==0)
		{
			directory_flag=1;
		}
		else if(strcmp(argv[i],"-da")==0 || strcmp(argv[i],"-ad")==0)
		{
			directory_flag=1;
			all_flag=1;
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

	//printf("%s\n", "thug");

	if(all_flag==0 && directory_flag==0)
	{
		struct dirent *de;
		DIR* dr=NULL;


		if(counter==0)
		{
			dr=opendir(".");


			if(dr==NULL)
			{
				int errx=errno;

				switch(errx)
				{
					case EACCES:	printf("ls: cannot access: '%s': Permission denied", ".");
									break;

					case ENOENT:	printf("ls: cannot access: '%s': No such file or directory", ".");
									break;
				
					default:		printf("ls: cannot access: '%s': Error", ".");
				}	
			}
			else
			{
				while((de=readdir(dr))!=NULL)
				{
					if((de->d_name[0])!='.')
						printf("%s  ", de->d_name);
				}
			}

			printf("%s\n", "");
			closedir(dr);
		}

		
		for(int i=0;i<counter;i++)
		{
			dr=opendir(directories[i]);

			if(dr==NULL)
			{
				int errx=errno;
			
				switch(errx)
				{
					case EACCES:	printf("ls: cannot access: '%s': Permission denied", directories[i]);
									break;
					case ENOENT:	printf("ls: cannot access: '%s': No such file or directory", directories[i]);
									break;
					default:		printf("ls: cannot access: '%s': Error", directories[i]);
				}
			}
			else
			{
				printf("%s:\n", directories[i]);

				while((de=readdir(dr))!=NULL)
				{
					if((de->d_name)[0]!='.')
						printf("%s  ", de->d_name);
				}
			}

			printf("%s\n", "");

			if(i<counter-1)
				printf("%s\n", "");

			closedir(dr);
		}
	}
	else if(all_flag==1 && directory_flag==0)
	{
		struct dirent *de;
		DIR* dr=NULL;

		if(counter==0)
		{
			dr=opendir(".");
			if(dr==NULL)
			{
				int errx=errno;

				switch(errx)
				{
					case EACCES:	printf("ls: cannot access: '%s': Permission denied", ".");
									break;

					case ENOENT:	printf("ls: cannot access: '%s': No such file or directory", ".");
									break;
				
					default:		printf("ls: cannot access: '%s': Error", ".");
				}	
			}
			else
			{
				while((de=readdir(dr))!=NULL)
				{
					printf("%s  ", de->d_name);
				}
			}

			printf("%s\n", "");
			closedir(dr);
		}

		
		for(int i=0;i<counter;i++)
		{
			dr=opendir(directories[i]);

			if(dr==NULL)
			{
				int errx=errno;
			
				switch(errx)
				{
					case EACCES:	printf("ls: cannot access: '%s': Permission denied", directories[i]);
									break;
					case ENOENT:	printf("ls: cannot access: '%s': No such file or directory", directories[i]);
									break;
					default:		printf("ls: cannot access: '%s': Error", directories[i]);
				}
			}
			else
			{
				printf("%s:\n", directories[i]);

				while((de=readdir(dr))!=NULL)
				{
					printf("%s  ", de->d_name);
				}
			}

			printf("%s\n", "");

			if(i<counter-1)
				printf("%s\n", "");
			
			closedir(dr);
		}
	}
	else if(all_flag==0 && directory_flag==1)
	{
		struct dirent *de;
		DIR* dr=NULL;

		if(counter==0)
		{
			printf("%s\n", ".");
		}
		else
		{
			for(int i=0;i<counter;i++)
			{

				dr=opendir(directories[i]);

				if(dr==NULL)
				{
					int errx=errno;
			
					switch(errx)
					{
						case EACCES:	printf("ls: cannot access: '%s': Permission denied", directories[i]);
										break;
						case ENOENT:	printf("ls: cannot access: '%s': No such file or directory", directories[i]);
										break;
						default:		printf("ls: cannot access: '%s': Error", directories[i]);
					}	
				}
				else
				{
					printf("%s  ", directories[i]);
				}	

				printf("%s\n", "");

				if(i<counter-1)
					printf("%s\n", "");
			}
		}
	}
	else
	{
		struct dirent *de;
		DIR* dr=NULL;

		if(counter==0)
		{
			printf("%s\n", ".");
		}
		else
		{
			for(int i=0;i<counter;i++)
			{

				dr=opendir(directories[i]);

				if(dr==NULL)
				{
					int errx=errno;
			
					switch(errx)
					{
						case EACCES:	printf("ls: cannot access: '%s': Permission denied", directories[i]);
										break;
						case ENOENT:	printf("ls: cannot access: '%s': No such file or directory", directories[i]);
										break;
						default:		printf("ls: cannot access: '%s': Error", directories[i]);
					}	
				}
				else
				{
					printf("%s  ", directories[i]);
				}	
						
				printf("%s\n", "");

				if(i<counter-1)
					printf("%s\n", "");
			}
		}
	}

	return 0;
}