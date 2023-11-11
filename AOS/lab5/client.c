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
    printf("\nClient stopped\n");
    exit(0);
}

int main(int argc, char* argv[]) {
    int to;
    if (argc < 4) {
        printf("Invalid count of arguments or their value\n");
        exit(1);
    }

    char* endptr;
    int idTo;
    int key = atoi(argv[3]);

    if ((idTo = msgget(key, IPC_CREAT | S_IWUSR | S_IRUSR)) == -1) {
        perror("Error 1 with msgget!");
        return 1;
    }

    int type = (int)strtol(argv[2], &endptr, 10);
    if (argv[2] == endptr || *endptr) {
        perror("Error with strtol!");
        exit(1);
    }
    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("Error with SIGINT!");
    }

    if ((id = msgget(IPC_PRIVATE, S_IWUSR | S_IRUSR)) == -1) {
        perror("Error 2 with msgget!");
    }

    Message = malloc(sizeof(struct message));
    Message->type = type;
    strcpy(Message->data, argv[1]);
    Message->count = 0;
    Message->Ids.idFrom = idTo; // id -> idTo for task 10
    Message->Ids.idTo = idTo;
    while (1) {
        Message->type = type;
        sleep(4);
        if (msgsnd(Message->Ids.idTo, Message, sizeof(struct message), 0) == -1) {
            perror("Error with msgsnd!");
            free(Message);

            if (msgctl(id, IPC_RMID, 0) == -1) {
                perror("Error 2 with msgctl");
            }
            return 1;
        }
        printf("Msgsnd:\n type = %ld\n idFrom = %d\n idTo = %d\n data = %s\n count = %d\n\n", Message->type, Message->Ids.idFrom, Message->Ids.idTo, Message->data, Message->count);

        if (msgrcv(idTo, Message, sizeof(struct message), 1, 0) == -1) {  // (msgrcv(idTo, Message, sizeof(struct message), 1, 0) == -1) for task 10
            perror("Error with msgrcv!");
            free(Message);

            if (msgctl(id, IPC_RMID, 0) == -1) {
                perror("Error 3 with msgctl");
            }
            return 1;
        }

        printf("Msgrcv:\n type = %ld\n idFrom = %d\n idTo = %d\n data = %s\n count = %d\n\n", Message->type, Message->Ids.idFrom, Message->Ids.idTo, Message->data, Message->count);

        to = Message->Ids.idFrom;
        Message->Ids.idFrom = Message->Ids.idTo;
        Message->Ids.idTo = to;
    }

    return 0;
}
