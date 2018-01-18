#include <stdio.h>
#include <string.h>
#include <time.h>

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

int main(int argc, char const *argv[])
{
	int rfc_flag=0;
	int utc_flag=0;


	for(int i=1;i<argc;i++)
	{
		if(strcmp(argv[i],"-R")==0 || strcmp(argv[i],"--rfc-2822")==0)
		{
			rfc_flag=1;
		}
		else if(strcmp(argv[i],"-u")==0 || strcmp(argv[i],"--utc")==0 || strcmp(argv[i],"--universal")==0)
		{
			utc_flag=1;
		}
		else if(strcmp(argv[i],"-uR")==0 || strcmp(argv[i],"-Ru")==0)
		{
			utc_flag=1;
			rfc_flag=1;
		}
	}

	if(rfc_flag==0 && utc_flag==0)
	{
		time_t cur_time;
		cur_time=time(NULL);
		char* t=ctime(&cur_time);
		remove_new_line(t);

		for(int i=0;i<strlen(t)-4;i++)
		{
			printf("%c", t[i]);
		}	

		printf("%s", "IST ");

		for(int i=strlen(t)-4;i<strlen(t);i++)
		{
			printf("%c", t[i]);
		}

		printf("%s\n", "");
	}
	else if(rfc_flag==1 && utc_flag==0)
	{
		time_t cur_time;
		cur_time=time(NULL);
		char* t=ctime(&cur_time);
		remove_new_line(t);

		char day[4];
		char month[4];
		char date[3];
		char ttime[9];
		char year[5];


		int j=0;
		for(int i=0;i<3;i++)
		{
			day[j++]=t[i];
		}	

		j=0;
		for(int i=4;i<7;i++)
		{
			month[j++]=t[i];
		}

		j=0;
		for(int i=8;i<10;i++)
		{
			date[j++]=t[i];
		}

		j=0;
		for(int i=11;i<19;i++)
		{
			ttime[j++]=t[i];
		}

		j=0;
		for(int i=strlen(t)-4;i<strlen(t);i++)
		{
			year[j++]=t[i];
		}

		for(int i=0;i<3;i++)
		{
			printf("%c", day[i]);
		}

		printf("%s", ", ");

		for(int i=0;i<2;i++)
		{
			printf("%c", date[i]);
		}

		printf("%s", " ");

		for(int i=0;i<3;i++)
		{
			printf("%c", month[i]);
		}

		printf("%s", " ");

		for(int i=0;i<4;i++)
		{
			printf("%c", year[i]);
		}

		printf("%s", " ");

		for(int i=0;i<8;i++)
		{
			printf("%c", ttime[i]);
		}

		printf("%s\n", " +0530");
	}
	else if(rfc_flag==0 && utc_flag==1)
	{
		time_t t;
		struct tm *gmt_time;
		t=time(NULL);
		gmt_time=gmtime(&t);
		char* ptime=asctime(gmt_time);
		remove_new_line(ptime);

		for(int i=0;i<strlen(ptime)-4;i++)
		{
			printf("%c", ptime[i]);
		}	

		printf("%s", "UTC ");

		for(int i=strlen(ptime)-4;i<strlen(ptime);i++)
		{
			printf("%c", ptime[i]);
		}

		printf("%s\n", "");
	}
	else
	{

		time_t t;
		struct tm *gmt_time;
		t=time(NULL);
		gmt_time=gmtime(&t);
		char* ptime=asctime(gmt_time);
		remove_new_line(ptime);	

		char day[4];
		char month[4];
		char date[3];
		char ttime[9];
		char year[5];


		int j=0;
		for(int i=0;i<3;i++)
		{
			day[j++]=ptime[i];
		}	

		j=0;
		for(int i=4;i<7;i++)
		{
			month[j++]=ptime[i];
		}

		j=0;
		for(int i=8;i<10;i++)
		{
			date[j++]=ptime[i];
		}

		j=0;
		for(int i=11;i<19;i++)
		{
			ttime[j++]=ptime[i];
		}

		j=0;
		for(int i=strlen(ptime)-4;i<strlen(ptime);i++)
		{
			year[j++]=ptime[i];
		}

		for(int i=0;i<3;i++)
		{
			printf("%c", day[i]);
		}

		printf("%s", ", ");

		for(int i=0;i<2;i++)
		{
			printf("%c", date[i]);
		}

		printf("%s", " ");

		for(int i=0;i<3;i++)
		{
			printf("%c", month[i]);
		}

		printf("%s", " ");

		for(int i=0;i<4;i++)
		{
			printf("%c", year[i]);
		}

		printf("%s", " ");

		for(int i=0;i<8;i++)
		{
			printf("%c", ttime[i]);
		}

		printf("%s\n", " +0000");
	}

	return 0;
}