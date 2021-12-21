#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// Nombre total de thread
#define NB_FORK 2
// Taille du message
#define LENGTH_MSG 30
// Tableau contenant le message
char message[LENGTH_MSG] = "";

// Fonction exécutée dans le fork
void job(int * tube) {
	int tid = getpid();
	// timer pour attendre maximum 5 secondes
	int i = 5;
	while (i > 0) {
		// lecture dans le tube
		if (read(*tube, message, LENGTH_MSG) > 0) {
			printf("Message du processus [%i] : %s", tid, message);
			break;
		}
		sleep(1);
	}
}
// Fonction qui attend chacun des processus fils
void waitForAll() {
	int status;
	pid_t pid;
	int n = 0;
	while (n < NB_FORK) {
		pid = wait(&status);
		n++;
	}
}

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);

                /* Send "string" through the output side of pipe */
                write(fd[1], string, (strlen(string)+1));
                exit(0);
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }
        
        return(0);
}