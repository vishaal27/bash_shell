# bash_shell

This is an implementation of a simple shell using the fork, exec and wait system calls. The shell is capable of handling 5 internal and 5 external commands. The elaborate description of each command is as follows:


INTERNAL:

1) cd: The cd command is used for changing the current working directory. It uses the chdir() system call.
2) exit: The exit command exits the running shell.
3) pwd: The pwd command displays the present working directory in the running shell. It uses the getcwd() system call.
4) history: The history command displays the entire history of commands entered into the shell from the time the shell was first run.
5) echo: The echo command displays the text that is entered onto the shell. It can handle two command line options. They are:
	-n: On using this option, the last \n(newline) character is truncated.
	-E: This option can be used to disable the interpretation of backslash escapes like \n, \t, \r etc. For eg., if wew type in echo -E "e\n", the out put will be e\n.


EXTERNAL:

1) ls: The ls command is used to display the contents of a particular directory. It uses the opendir(), readdir() and closedir() system calls. It can handle two command line options. They are->
	-a: This option lists all the files and directories in the particular directory(including hidden files and directories i.e. starting with '.')
	-d: This option lists only the name of the directory and not its contents.
2) cat: The cat command is used to concatenate the contents of various files given as parameters and then display the output onto the shell. It can handle two command line options. They are->
	-n: This option is used to number the lines outputted.
	-E: This option is used to show the ends of each line by appending a $ at the end of each line.
3) date: The date command is used to display the current system time and date. It uses the asctime(), time(), ctime() and localtime_r() system calls. It can handle two command line options. They are->
	-R: This option is used to format the output in in RFC 2822 format. Eg. Sun, 1 Jan 2018 00:00:00 +0530
	-u: This option is used to display the current GMT(UTC) time and date.
4) rm: The rm command is used to remove files and directories. It uses the remove() system call. It can handle two command line options. They are->
	-i: This option diplays a prompt question before every file/directory removal takes place. Only if the user inputs y/Y(showing his approval to remove the files), the file gets removed.
	-v: This option display a message giving information of the operation that was performed.
5) mkdir: The mkdir command is used to create new directories. It uses the mkdir() system call. It can handle two command line options. They are->
	-p: This option creates the entire directory structure of the given input parameters i.e. if the structure(parent directories) exists then only the lowest level directory is created else it creates parent directories as well.
	-v: This option displays a message giving information of the operation that was performed.

If any command apart from these is entered, the shell will output an error message saying command does not exist.


The assumptions made include:
	-It is a single user shell.
	-The user is not a root user.
	-There are no symbolic links present i.e. pwd -P and -L(physical and logical directories) returns the same.

