#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/wait.h>

char* remove_new_line(char* str)
{
	unsigned char c1;

	while(*str!='\0')
	{
		if(*str=='\n')
		{
			*str='\0';
			break;
		}
		str++;
	}

	return str;
}

char* return_after_space(char* str)
{
	unsigned char c1;
	char* temp=str;

	while(*temp!='\0')
	{
		if(*temp==' ')
		{
			break;
		}
		temp++;
	}

	return temp;
}

void parse_command(char* command, char** args)
{
	while(*command!='\0')
	{
		while(*command=='\n'||*command==' '||*command=='\t')
		{
			*command='\0';
			command++;
		}

		*args=command;
		args++;
		while(*command!='\n' && *command!=' ' && *command!='\t' && *command!='\0')
		{
			command++;
		}
	}

	*args='\0';
}

void parse_command_for_cd(char* command, char** args)
{
	while(*command!='\0')
	{
		while(*command=='\n'||*command==' '||*command=='\t')
		{
			*command='\0';
			command++;
		}

		*args=command;
		args++;
		while(*command!='\n' && *command!=' ' && *command!='\t' && *command!='\0')
		{
			command++;
		}

		break;
	}

	*args='\0';
}

int main(int argc, char const *argv[])
{

	char command[1000];
	char* arguments[100];
	char* ARGS[100];
	char history[1000][1000];	//can store upto 1000 commands for history
	int counter=0;
	
	FILE *fp=fopen("history.txt", "ab+");
	
	while(1)
	{

		char cwd[1024];
		getcwd(cwd, sizeof(cwd));
		   	if(cwd==NULL)
		       perror("getcwd() error");


		printf("ush:%s >>>", cwd);
		
		
		fgets(command, sizeof(command), stdin);
		//printf("command: %s\n", command);
	
		int err=0;
		int flag=0;

		for(int i=0;command[i]!='\n';i++)
		{
			history[counter][i]=command[i];
		}

		if(command[0]!='\n')
		{
				counter++;
				if(fp==NULL)
				{	
					fprintf(fp,"%s\n", "Error: Could not store command");
				}
				else
				{
					fprintf(fp,"%s\n", history[counter-1]);
				}
		}


		if(strstr(command,"exit")!=NULL)	//exit internal command
		{
			flag=1;
			break;
		}
		else if(strstr(command,"cd ")!=NULL) //cd internal command
		{
			flag=1;
			remove_new_line(command);

			char* token=&command[3];
			if(strcmp(token, "~")==0)
			{
				struct passwd *pw;
				char* name=NULL;
				char* thug=NULL;
				pw=getpwuid(geteuid());
				if(pw)
				{
					name=pw->pw_name;
					int l=strlen(name);
					thug=malloc(6+l+1);
					strcpy(thug, "/home/");
				 	strcat(thug, name);
					chdir(thug);
				}
				else
					chdir("/home/vishaal");
				continue;
			}
			err=chdir(token);
			if(err==-1)
				printf("cd: %s: No such file or directory\n", token);

			continue;

		}
		else if(strcmp(command,"history\n")==0)	//history internal command
		{
			flag=1;

			rewind(fp);

			char line[256];
			int i=0;
			while(fgets(line, sizeof(line), fp))
			{
				printf("%d %s", i+1, line);
				i++;
			}
						
			fseek(fp, 0, SEEK_END);
			continue;
		}
		else if(strstr(command,"echo")!=NULL)  //echo internal command
		{
			flag=1;
			parse_command(command, arguments);

			int newline_flag=0;
			int escape_flag=0;
			char things_to_echo[1000][1000];
			int echo_counter=0;

			int size=0;
			for(int i=0;arguments[i]!='\0';i++)
			{
				size++;

				if(strcmp(arguments[i], "-n")==0)
				{
					newline_flag=1;
				}
				else if(strcmp(arguments[i], "-E")==0)
				{
					escape_flag=1;
				}
				else if(strcmp(arguments[i], "-En")==0 || strcmp(arguments[i], "-nE")==0)
				{
					newline_flag=1;
					escape_flag=1;
				}
				else
				{
					for(int j=0;arguments[i][j]!='\0';j++)
					{
						things_to_echo[echo_counter][j]=arguments[i][j];
					}

					echo_counter++;
				}
			}


			if(newline_flag==0 && escape_flag==0)
			{
				if(size==2)
				{
					printf("%s\n", " ");
					continue;
				}

				for(int i=1;i<echo_counter;i++)
				{
					printf("%s", things_to_echo[i]);
					printf("%s", " ");
				}

				printf("%s\n", " ");
			}
			else if(newline_flag==1 && escape_flag==0)
			{
				if(size==2)
				{
					printf("%s", " ");
					continue;
				}

				for(int i=1;i<echo_counter;i++)
				{
					printf("%s", things_to_echo[i]);
					if(i<echo_counter-1)
						printf("%s", " ");
				}

			}
			else if(newline_flag==0 && escape_flag==1)
			{
				if(size==2)
				{
					printf("%s\n", " ");
					continue;
				}

				for(int i=1;i<echo_counter;i++)
				{
					printf("%s", things_to_echo[i]);
					printf("%s", " ");
				}

				printf("%s\n", " ");
			}
			else
			{
				if(size==2)
				{
					printf("%s", " ");
					continue;
				}

				for(int i=1;i<echo_counter;i++)
				{
					printf("%s", things_to_echo[i]);
					if(i<echo_counter-1)
						printf("%s", " ");
				}
			}

			continue;
		}
		else if(strstr(command, "pwd")!=NULL)  //pwd internal command
		{
			int physical_flag=0;
			int logical_flag=0;

			parse_command(command, arguments);
			
			for(int i=0;arguments[i]!='\0';i++)
			{
				//printf("arguments[i]: %s\n", arguments[i]);

				if(strcmp(arguments[i], "-P")==0 || strcmp(arguments[i], "--physical")==0)
				{
					physical_flag=1;
				}
				else if(strcmp(arguments[i], "-L")==0 || strcmp(arguments[i], "--logical")==0)
				{
					logical_flag=1;
				}
				else if(strcmp(arguments[i], "-LP")==0 || strcmp(arguments[i], "-PL")==0)
				{
					logical_flag=1;
					physical_flag=1;
				}
			}

			//printf("physical_flag: %d, logical_flag: %d\n", physical_flag, logical_flag);

			if(physical_flag==0 && logical_flag==0)
			{
				if (getcwd(cwd, sizeof(cwd)) != NULL)
		       		printf("%s\n", cwd);
		   		else
		       		perror("getcwd() error");
			}
			else if(physical_flag==1 && logical_flag==0)
			{
				if (getcwd(cwd, sizeof(cwd)) != NULL)
		       		printf("%s\n", cwd);
		   		else
		       		perror("getcwd() error");
			}
			else if(physical_flag==0 && logical_flag==1)
			{
				//TODO
				printf("%s\n", "logical");
			}
			else
			{
				//TODO
			}

			continue;
		}



		parse_command(command, arguments);

		int size=0;
		for(int i=0;arguments[i]!='\0';i++)
		{
			size++;
		}


		int i;
		for(i=0;i<size-1;i++)
		{
			ARGS[i]=arguments[i];
		}

		
		ARGS[i]=0;

		int pid=fork();
		if(flag==0 && pid==0)
		{

			//printf(": %s\n", ARGS[0]);


			if(strcmp(ARGS[0], "date")==0)	//date external command
			{
				int s=strlen(cwd);
				char dat[s+6];

				strcpy(dat, cwd);
				strcat(dat, "/date");
				int er=execvp(dat, ARGS);
				if(er==-1)
					execvp("/home/vishaal/Desktop/CPrograms/simpleshell/date", ARGS);
				exit(1);
			}
			else if(strcmp(ARGS[0], "ls")==0)	//ls external command
			{
				int s=strlen(cwd);
				char dat[s+4];

				strcpy(dat, cwd);
				strcat(dat, "/ls");
				int er=execvp(dat, ARGS);
				if(er==-1)
					execvp("/home/vishaal/Desktop/CPrograms/simpleshell/ls", ARGS);
				exit(1);
			}
			else if(strcmp(ARGS[0], "cat")==0)	//cat external command
			{
				int s=strlen(cwd);
				char dat[s+5];

				strcpy(dat, cwd);
				strcat(dat, "/cat");
				int er=execvp(dat, ARGS);
				if(er==-1)
					execvp("/home/vishaal/Desktop/CPrograms/simpleshell/cat", ARGS);
				exit(1);
			}
			else if(strcmp(ARGS[0], "rm")==0)	//rm external command
			{
				int s=strlen(cwd);
				char dat[s+4];

				strcpy(dat, cwd);
				strcat(dat, "/rm");
				int er=execvp(dat, ARGS);
				if(er==-1)
					execvp("/home/vishaal/Desktop/CPrograms/simpleshell/rm", ARGS);
				exit(1);
			}
			else if(strcmp(ARGS[0], "mkdir")==0)	//mkdir external command
			{
				int s=strlen(cwd);
				char dat[s+7];

				strcpy(dat, cwd);
				strcat(dat, "/mkdir");
				int er=execvp(dat, ARGS);
				if(er==-1)
					execvp("/home/vishaal/Desktop/CPrograms/simpleshell/mkdir", ARGS);
				exit(1);
			}
			else
			{
				printf("%s: command not found\n", ARGS[0]);
			}

		}
		else if(flag==0)
		{
			wait(0);
		}
	}

	fclose(fp);

	return 0;
}


