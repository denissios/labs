#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <time.h>

struct ids {
    int idFrom;
    int idTo;
};

struct message {
    long type;
    struct ids Ids;
    char data[32];
    int count;
};

int id;
struct message* Message;

void handler(int signum) {
    if (msgctl(id, IPC_RMID, 0) == -1) {
        perror("Error 1 with msgctl!");
    }
    free(Message);

    printf("\nServer stopped\n");
    exit(0);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Invalid count of arguments or their value\n");
        exit(1);
    }

    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("Error with SIGINT!");
    }

    int key = atoi(argv[1]);
    if ((id = msgget(key, IPC_CREAT | S_IWUSR | S_IRUSR)) == -1) {
        perror("Error with msgget!");
    }

    printf("Id: %d\n", id);

    Message = malloc(sizeof(struct message));

    while (1) {
        if (msgrcv(id, Message, sizeof(struct message), 4, 0) == -1) { // (msgrcv(id, Message, sizeof(struct message), 4, 0) for task 10
            perror("Error with msgrcv!");
            free(Message);

            if (msgctl(id, IPC_RMID, 0) == -1) {
                perror("Error 2 with msgctl");
            }
            return 1;
        }

        printf("Msgrcv:\n type = %ld\n idFrom = %d\n idTo = %d\n data = %s\n count = %d\n\n", Message->type, Message->Ids.idFrom, Message->Ids.idTo, Message->data, Message->count);

        Message->type = 1;
        Message->Ids.idTo = Message->Ids.idFrom;
        Message->Ids.idFrom = id;
        Message->count++;

        if (msgsnd(Message->Ids.idTo, Message, sizeof(struct message), 0) == -1) {
            perror("Error with msgsnd!");
            free(Message);

            if (msgctl(id, IPC_RMID, 0) == -1) {
                perror("Error 3 with msgctl");
            }
            return 1;
        }

        printf("Msgsnd:\n type = %ld\n idFrom = %d\n idTo = %d\n data = %s\n count = %d\n\n", Message->type, Message->Ids.idFrom, Message->Ids.idTo, Message->data, Message->count);
    }

    return 0;
}
