#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int check_file_exists(const char *file)
{
	int exists=0;

	if(access(file,F_OK)!=-1)
	{
    	// file exists
		exists=1;
	}
	
	return exists;
}


int main(int argc, char const *argv[])
{
	int prompt_flag=0;
	int verbose_flag=0;
	char files[1000][1000];
	int counter=0;

	if(argc==1)
	{
		printf("%s\n", "rm: missing operand");
		return 1;
	}

	for(int i=1;i<argc;i++)
	{
		if(strcmp(argv[i], "-i")==0)
		{
			prompt_flag=1;
		}
		else if(strcmp(argv[i], "-v")==0 || strcmp(argv[i], "--verbose")==0)
		{
			verbose_flag=1;
		}
		else if(strcmp(argv[i], "-iv")==0 || strcmp(argv[i], "-vi")==0)
		{
			prompt_flag=1;
			verbose_flag=1;
		}
		else
		{
			for(int j=0;argv[i][j]!='\0';j++)
			{
				files[counter][j]=argv[i][j];
			}

			counter++;
		}
	}

	//printf("prompt flag: %d, verbose flag: %d\n", prompt_flag, verbose_flag);

	if(prompt_flag==0 && verbose_flag==0)
	{

		int ret=0;

		for(int i=0;i<counter;i++)
		{
			ret=remove(files[i]);

			if(ret==-1)
			{
				int err=errno;

				switch(err)
				{
					case EACCES:	printf("rm: cannot remove '%s': Permission denied\n", files[i]);
									break;

					case EBUSY:		printf("rm: cannot remove '%s': File is busy\n", files[i]);
									break;

					case ENOENT:	printf("rm: cannot remove '%s': No such file or directory\n", files[i]);
									break;

					default:		printf("rm: cannot remove '%s': Error\n", files[i]);
				}
			}
		}
	}
	else if(prompt_flag==1 && verbose_flag==0)
	{
		int ret=0;

		for(int i=0;i<counter;i++)
		{
			
			int file_exists=check_file_exists(files[i]);

			if(file_exists==1)
			{
				//file exists
				printf("rm: remove regular file '%s'?\n", files[i]);

				char opt1, opt2;
				opt1=getchar();
				opt2=getchar();


				//printf("%c\n", opt);
				
				if(opt1=='y' || opt2=='y')
				{
					ret=remove(files[i]);

					if(ret==-1)
					{
						int err=errno;

						switch(err)
						{
							case EACCES:	printf("rm: cannot remove '%s': Permission denied\n", files[i]);
											break;

							case EBUSY:		printf("rm: cannot remove '%s': File is busy\n", files[i]);
											break;

							case ENOENT:	printf("rm: cannot remove '%s': No such file or directory\n", files[i]);
											break;

							default:		printf("rm: cannot remove '%s': Error\n", files[i]);
						}
					}
				}
			}
			else
			{
				printf("rm: cannot remove '%s': No such file or directory\n", files[i]);
			}
		}	
	}
	else if(prompt_flag==0 && verbose_flag==1)
	{
		int ret=0;

		for(int i=0;i<counter;i++)
		{
			ret=remove(files[i]);

			if(ret==-1)
			{
				int err=errno;

				switch(err)
				{
					case EACCES:	printf("rm: cannot remove '%s': Permission denied\n", files[i]);
									break;

					case EBUSY:		printf("rm: cannot remove '%s': File is busy\n", files[i]);
									break;

					case ENOENT:	printf("rm: cannot remove '%s': No such file or directory\n", files[i]);
									break;

					default:		printf("rm: cannot remove '%s': Error\n", files[i]);
				}
			}
			else
			{
				printf("removed '%s'\n", files[i]);
			}
		}
	}
	else
	{
		int ret=0;

		for(int i=0;i<counter;i++)
		{
			
			int file_exists=check_file_exists(files[i]);

			if(file_exists==1)
			{
				//file exists
				printf("rm: remove regular file '%s'?\n", files[i]);

				char opt1, opt2;
				opt1=getchar();
				opt2=getchar();


				// printf("%c %c\n", opt1, opt2);
				
				if(opt1=='y' || opt2=='y')
				{
					ret=remove(files[i]);

					//printf("ret: %d\n", ret);

					if(ret==-1)
					{
						int err=errno;

						switch(err)
						{
							case EACCES:	printf("rm: cannot remove '%s': Permission denied\n", files[i]);
											break;

							case EBUSY:		printf("rm: cannot remove '%s': File is busy\n", files[i]);
											break;

							case ENOENT:	printf("rm: cannot remove '%s': No such file or directory\n", files[i]);
											break;

							default:		printf("rm: cannot remove '%s': Error\n", files[i]);
						}
					}
					else
					{
						printf("removed '%s'\n", files[i]);
					}
				}
			}
			else
			{
				printf("rm: cannot remove '%s': No such file or directory\n", files[i]);
			}
		}
	}

	return 0;
}