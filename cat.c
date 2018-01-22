#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


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

int is_dir(char *path)
{
   struct stat s;
   if(stat(path, &s)!=0)	//error
       return 0;
   int ret=S_ISDIR(s.st_mode);
   return ret;
}


int main(int argc, char const *argv[])
{

	int number_flag=0;
	int ends_flag=0;
	char files[1000][1000];
	int counter=0;

	if(argc==1)
	{
		printf("%s\n", "cat: No files entered");
		return 1;
	}


	for(int i=1;i<argc;i++)
	{
		if(strcmp(argv[i], "-n")==0 || strcmp(argv[i], "--number")==0)
		{
			number_flag=1;
		}
		else if(strcmp(argv[i], "-E")==0 || strcmp(argv[i], "--show-ends")==0)
		{
			ends_flag=1;
		}
		else if(strcmp(argv[i], "-nE")==0 || strcmp(argv[i], "-En")==0)
		{
			number_flag=1;
			ends_flag=1;
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

	//printf("number_flag: %d, ends_flag: %d\n", number_flag, ends_flag);


	if(number_flag==0 && ends_flag==0)
	{
		for(int i=0;i<counter;i++)
		{
			FILE *fp;
			char* line;
			char path[]="./";
			ssize_t read;
			size_t l=0;

			strcat(path, files[i]);

			if(strstr(files[i], "/")!=NULL)
			{
				//absolute path
				fp=fopen(files[i], "r");

				//printf("is_dir: %d\n", is_dir(files[i]));

				if(is_dir(files[i])==1)
				{
					printf("cat: %s: Is a directory\n", files[i]);
					continue;
				}

				if(!fp)
				{
					printf("cat: %s: No such file or directory\n", files[i]);
					continue;
				}

				while((read=getline(&line, &l, fp))!=-1)
				{
					printf("%s", line);
				}

				fclose(fp);
			}
			else
			{
				//relative path
				fp=fopen(path, "r");

				//printf("is_dir: %d\n", is_dir(files[i]));

				if(is_dir(files[i])==1)
				{
					printf("cat: %s: Is a directory\n", files[i]);
					continue;
				}

				if(!fp)
				{
					printf("cat: %s: No such file or directory\n", path);
					continue;
				}

				while((read=getline(&line, &l, fp))!=-1)
				{
					printf("%s", line);
				}

				fclose(fp);
			}

			printf("%s\n", "");
		}
	}
	else if(number_flag==1 && ends_flag==0)
	{
		int line_counter=0;

		for(int i=0;i<counter;i++)
		{
			FILE *fp;
			char* line;
			char path[]="./";
			ssize_t read;
			size_t l=0;

			strcat(path, files[i]);

			if(strstr(files[i], "/")!=NULL)
			{
				//absolute path
				fp=fopen(files[i], "r");

				if(is_dir(files[i])==1)
				{
					printf("cat: %s: Is a directory\n", files[i]);
					continue;
				}

				if(!fp)
				{
					printf("cat: %s: No such file or directory\n", files[i]);
					continue;
				}

				

				while((read=getline(&line, &l, fp))!=-1)
				{
					line_counter++;
					printf("\t%d  %s", line_counter, line);
				}

				fclose(fp);
			}
			else
			{
				//relative path
				fp=fopen(path, "r");

				if(is_dir(files[i])==1)
				{
					printf("cat: %s: Is a directory\n", files[i]);
					continue;
				}

				if(!fp)
				{
					printf("cat: %s: No such file or directory\n", path);
					continue;
				}


				while((read=getline(&line, &l, fp))!=-1)
				{
					line_counter++;
					printf("\t%d  %s", line_counter, line);
				}

				fclose(fp);
			}

			printf("%s\n", "");
		}
	}
	else if(number_flag==0 && ends_flag==1)
	{
		for(int i=0;i<counter;i++)
		{
			FILE *fp;
			char* line;
			char path[]="./";
			ssize_t read;
			size_t l=0;

			strcat(path, files[i]);

			if(strstr(files[i], "/")!=NULL)
			{
				//absolute path
				fp=fopen(files[i], "r");

				if(is_dir(files[i])==1)
				{
					printf("cat: %s: Is a directory\n", files[i]);
					continue;
				}

				if(!fp)
				{
					printf("cat: %s: No such file or directory\n", files[i]);
					continue;
				}

				while((read=getline(&line, &l, fp))!=-1)
				{
					remove_new_line(line);
					printf("%s$\n", line);
				}

				fclose(fp);
			}
			else
			{
				//relative path
				fp=fopen(path, "r");

				if(is_dir(files[i])==1)
				{
					printf("cat: %s: Is a directory\n", files[i]);
					continue;
				}

				if(!fp)
				{
					printf("cat: %s: No such file or directory\n", path);
					continue;
				}

				while((read=getline(&line, &l, fp))!=-1)
				{
					remove_new_line(line);
					printf("%s$\n", line);
				}

				fclose(fp);
			}

			printf("%s\n", "");
		}
	}
	else
	{

		int line_counter=0;

		for(int i=0;i<counter;i++)
		{
			FILE *fp;
			char* line;
			char path[]="./";
			ssize_t read;
			size_t l=0;

			strcat(path, files[i]);

			if(strstr(files[i], "/")!=NULL)
			{
				//absolute path
				fp=fopen(files[i], "r");

				if(is_dir(files[i])==1)
				{
					printf("cat: %s: Is a directory\n", files[i]);
					continue;
				}

				if(!fp)
				{
					printf("cat: %s: No such file or directory\n", files[i]);
					continue;
				}

				while((read=getline(&line, &l, fp))!=-1)
				{
					line_counter++;
					remove_new_line(line);
					printf("\t%d  %s$\n", line_counter, line);
				}

				fclose(fp);
			}
			else
			{
				//relative path
				fp=fopen(path, "r");

				if(is_dir(files[i])==1)
				{
					printf("cat: %s: Is a directory\n", files[i]);
					continue;
				}

				if(!fp)
				{
					printf("cat: %s: No such file or directory\n", path);
					continue;
				}

				while((read=getline(&line, &l, fp))!=-1)
				{
					line_counter++;
					remove_new_line(line);
					printf("\t%d  %s$\n", line_counter, line);
				}

				fclose(fp);
			}

			printf("%s\n", "");
		}
	}
	
	return 0;
}