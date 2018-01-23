all: date rm ls cat mkdir shell

shell: shell.c
	gcc shell.c -o shell

date: date.c
	gcc date.c -o date

rm:	rm.c
	gcc rm.c -o rm

ls:	ls.c
	gcc ls.c -o ls

cat: cat.c
	gcc cat.c -o cat

mkdir: mkdir.c
	gcc mkdir.c -o mkdir

clean:	
	rm -f date rm ls cat mkdir shell

 