#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[]) {
	int pid;
	
	printf("Starting program; process has pid %d\n", getpid());

	FILE *output;
	FILE *filestream;
	output = fopen("fork-output.txt", "w");
	fprintf(output, "BEFORE FORK\n");
	fflush(output);
	int buffer = 100;
	
	int piper[2];
	char line[buffer];
	pipe(piper);

	if ((pid = fork()) < 0) {
		fprintf(stderr, "Could not fork()");
		exit(1);
	}

	/* BEGIN SECTION A */
	
	printf("Section A;  pid %d\n", getpid());
	fprintf(output, "Section A\n");
	fflush(output);
	//sleep(30);

	/* END SECTION A */
	if (pid == 0) {
		/* BEGIN SECTION B */
		
		close(piper[0]);
		filestream = fdopen(piper[1], "w");
		fputs("hello from Section B\n", filestream);
		
		printf("Section B\n");
		fprintf(output, "Section B\n");
		fflush(output);
		//sleep(30);
		//sleep(30);
		printf("Section B done sleeping\n");
		
		char *newenviron[] = { NULL };

		printf("Program \"%s\" has pid %d. Sleeping.\n", argv[0], getpid());
		//sleep(30);
		
		if (argc <= 1) {
			printf("No program to exec.  Exiting...\n");
			exit(0);
		}

		printf("Running exec of \"%s\"\n", argv[1]);
		
		dup2(fileno(output), STDOUT_FILENO);
		fclose(output);

		execve(argv[1], &argv[1], newenviron);
		printf("End of program \"%s\".\n", argv[0]);

		exit(0);

		/* END SECTION B */
	} else {
		/* BEGIN SECTION C */

		close(piper[1]);
		filestream = fdopen(piper[0], "r");
		fgets(line, buffer, filestream);
		printf("%s", line);
		
		printf("Section C\n");
		fprintf(output, "Section C\n");
		fflush(output);
		//sleep(30);
		wait(0);
		//sleep(30);
		printf("Section C done sleeping\n");

		exit(0);

		/* END SECTION C */
	}
	/* BEGIN SECTION D */

	printf("Section D\n");
	fprintf(output, "Section D\n");
	fflush(output);
	//sleep(30);

	/* END SECTION D */
}
