#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char* argv[]) {
	int pipefd[2], res_read;
	char tmp[100];

	pipefd[0] = atoi(argv[1]);
	pipefd[1] = atoi(argv[2]);

	while ((res_read = read(0, tmp, 100)) > 0) {
		printf("Exec program reads from keyboard: %s", tmp);
		if (write(pipefd[1], tmp, res_read) == -1) {
			perror("Error with write in child!");
		}
	}

	close(pipefd[0]);
	close(pipefd[1]);
	return 0;
}
