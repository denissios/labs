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

void task1();
void task2(char** argv);
void task3(char** argv);
void task4(char** argv);
void task5(char** argv);
void task11();

int main(int argc, char** argv, char** envp) {
    const int task_num = 11;

    switch (task_num) {
    case 1:
        task1();
        break;
    case 2:
        if (argc != 3) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task2(argv);
        break;
    case 3:
        if (argc != 3) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task3(argv);
        break;
    case 4:
        if (argc != 3) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task4(argv);
        break;
    case 5:
        if (argc != 2) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task5(argv);
        break;
    case 11:
        task11();
        break;
    default:
        break;
    }

    return 0;
}



struct message {
    long type;
    char text[32];  // char text[32] for task 11
};

void task1() {
    const int id = msgget(IPC_PRIVATE, S_IWUSR | S_IRUSR);
    if (id == -1) {
        perror("Error with msgget!");
    }

    struct message* Message;
    for (size_t i = 1; i < 5; i++) {
        Message = malloc(16);
        Message->type = i;
        strcpy(Message->text, "2");
        if (msgsnd(id, Message, 1, 0) == -1) {
            perror("Error with msgsnd!");
            free(Message);
        }
        printf("type = %ld,  text = '%s'\n", Message->type, Message->text);
        free(Message);
    }

    struct msqid_ds msq;
    if (msgctl(id, IPC_STAT, &msq) == -1)
    {
        perror("Error 1 with msgctl!");
    }

    printf("\nmsg_stime = %s", ctime(&msq.msg_stime));
    printf("msg_rtime = %s", ctime(&msq.msg_rtime));
    printf("msg_ctime = %s", ctime(&msq.msg_ctime));
    printf("__msg_cbytes = %ld\n", msq.__msg_cbytes);
    printf("msg_qnum = %ld\n", msq.msg_qnum);
    printf("msg_qbytes = %ld\n", msq.msg_qbytes);
    printf("msg_lspid = %d\n", msq.msg_lspid);
    printf("msg_lrpid = %d\n", msq.msg_lrpid);
    printf("msg_perm.uid = %d\n", msq.msg_perm.uid);
    printf("msg_perm.gid = %d\n", msq.msg_perm.gid);
    printf("msg_perm.cuid = %d\n", msq.msg_perm.cuid);
    printf("msg_perm.cgid = %d\n", msq.msg_perm.cgid);
    printf("msg_perm.mode = %o\n", msq.msg_perm.mode);
    printf("msg_perm.__key = %d\n", msq.msg_perm.__key);
    printf("msg_perm.__seq = %d\n", msq.msg_perm.__seq);

    if (msgctl(id, IPC_RMID, 0) == -1) {
        perror("Error 2 with msgctl!");
    }
}



void task2(char** argv) {
    int id;
    struct message* Message;

    if (strcmp(argv[1], "-c") == 0) {
        if ((id = msgget(IPC_PRIVATE, S_IWUSR | S_IRUSR)) == -1) {
            perror("Error with msgget!");
            exit(1);
        }

        for (size_t i = 1; i < 5; i++) {
            Message = malloc(16);
            Message->type = i;
            strcpy(Message->text, "2");
            if (msgsnd(id, Message, 1, 0) == -1) {
                perror("Error with msgsnd!");
                free(Message);
            }
            printf("type = %ld,  text = '%s'\n", Message->type, Message->text);
            free(Message);
        }
        printf("id = %d\n", id);
    }
    else {
        char* endptr;

        id = (int)strtol(argv[1], &endptr, 10);
        if (argv[1] == endptr || *endptr) {
            perror("Error with strtol!");
        }

        int type = (int)strtol(argv[2], &endptr, 10);
        if (argv[2] == endptr || *endptr) {
            perror("Error with strtol!");
        }

        if ((Message = malloc(2048)) == NULL) {
            perror("Error with malloc!");
            exit(1);
        }

        if ((msgrcv(id, Message, 2048, type, 0)) == -1) {
            perror("Error with msgrcv!");
            free(Message);
        }
        else {
            printf("type = %ld\n", Message->type);
            printf("text = %s\n", Message->text);
            free(Message);
            if (msgctl(id, IPC_RMID, 0) == -1) {
                perror("Error with msgctl!");
            }
        }
    }
}



void task3(char** argv) {
    int id;
    struct message* Message;

    if (strcmp(argv[1], "-c") == 0) {
        if ((id = msgget(IPC_PRIVATE, S_IWUSR | S_IRUSR)) == -1) {
            perror("Error with msgget!");
            exit(1);
        }

        for (size_t i = 1; i < 5; i++) {
            Message = malloc(16);
            Message->type = i;
            strcpy(Message->text, "2");
            if (msgsnd(id, Message, 1, 0) == -1) {
                perror("Error with msgsnd!");
                free(Message);
            }
            printf("type = %ld,  text = '%s'\n", Message->type, Message->text);
            free(Message);
        }
        printf("id = %d\n", id);
    }
    else {
        char* endptr;

        id = (int)strtol(argv[1], &endptr, 10);
        if (argv[1] == endptr || *endptr) {
            perror("Error with strtol!");
        }

        int type = (int)strtol(argv[2], &endptr, 10);
        if (argv[2] == endptr || *endptr) {
            perror("Error with strtol!");
        }

        if ((Message = malloc(2048)) == NULL) {
            perror("Error with malloc!");
            exit(1);
        }

        if ((msgrcv(id, Message, 2048, type, IPC_NOWAIT)) == -1) {
            perror("Error with msgrcv!");
            free(Message);
        }
        else {
            printf("type = %ld\n", Message->type);
            printf("text = %s\n", Message->text);
            free(Message);
            if (msgctl(id, IPC_RMID, 0) == -1) {
                perror("Error with msgctl!");
            }
        }
    }
}



void task4(char** argv) {
    int id;
    struct message* Message;

    if (strcmp(argv[1], "-c") == 0) {
        if ((id = msgget(IPC_PRIVATE, S_IWUSR | S_IRUSR)) == -1) {
            perror("Error with msgget!");
            exit(1);
        }

        for (size_t i = 1; i < 5; i++) {
            Message = malloc(16);
            Message->type = i;
            strcpy(Message->text, "2222222");
            if (msgsnd(id, Message, 1, 0) == -1) {
                perror("Error with msgsnd!");
                free(Message);
            }
            printf("type = %ld,  text = '%s'\n", Message->type, Message->text);
            free(Message);
        }
        printf("id = %d\n", id);
    }
    else {
        char* endptr;

        id = (int)strtol(argv[1], &endptr, 10);
        if (argv[1] == endptr || *endptr) {
            perror("Error with strtol!");
        }

        int type = (int)strtol(argv[2], &endptr, 10);
        if (argv[2] == endptr || *endptr) {
            perror("Error with strtol!");
        }

        if ((Message = malloc(2048)) == NULL) {
            perror("Error with malloc!");
            exit(1);
        }

        if ((msgrcv(id, Message, 8, type, MSG_NOERROR)) == -1) {
            perror("Error with msgrcv!");
            free(Message);
        }
        else {
            printf("type = %ld\n", Message->type);
            printf("text = %s\n", Message->text);
            free(Message);
            if (msgctl(id, IPC_RMID, 0) == -1) {
                perror("Error with msgctl!");
            }
        }
    }
}



void task5(char** argv) {
    int id;
    struct message* Message;

    char* endptr;
    id = (int)strtol(argv[1], &endptr, 10);
    if (argv[1] == endptr || *endptr) {
        perror("Error with strtol!");
    }

    if (msgctl(id, IPC_RMID, 0) == -1) {
        perror("Error with msgctl!");
    }
    else {
        printf("Successfully removed with id = %d!\n", id);
    }
}



int id;
struct message* Message;

void handler(int signum) {
    if (msgctl(id, IPC_RMID, 0) == -1) {
        perror("Error with msgctl!");
    }
    free(Message);
    printf("\nStopped\n");
    exit(0);
}

void task11() {
    if ((id = msgget(IPC_PRIVATE, S_IWUSR | S_IRUSR)) == -1) {
        perror("Error with msgget!");
        exit(1);
    }

    if (signal(SIGINT, handler) == SIG_ERR) {
        perror("Error with SIGINT!");
    }

    struct message* Message = malloc(sizeof(struct message));
    Message->type = 1;
    strcpy(Message->text, "123456789");

    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error with fork!");
        break;
    case 0:
        for (size_t i = 0; i < 4; i ++) {
            sleep(2);
            if (msgsnd(id, Message, sizeof(struct message), 0) == -1) {
                perror("Error 1 with msgsnd!");
                free(Message);
            }
            printf("Child msgsnd:\n type = %ld\n text = %s\n\n", Message->type, Message->text);

            if ((msgrcv(id, Message, sizeof(struct message), 2, 0)) == -1) {
                perror("Error 1 with msgrcv!");
                free(Message);
            }
            sleep(1);
            printf("Child msgrcv:\n type = %ld\n text = %s\n\n\n\n\n", Message->type, Message->text);

            Message->type = 1;
        }
        
        break;
    default:
        for (size_t i = 0; i < 4; i++) {
            if ((msgrcv(id, Message, sizeof(struct message), 1, 0)) == -1) {
                perror("Error 2 with msgrcv!");
                free(Message);
            }
            sleep(1);
            printf("Parent msgrcv:\n type = %ld\n text = %s\n\n", Message->type, Message->text);

            Message->type = 2;

            if (msgsnd(id, Message, sizeof(struct message), 0) == -1) {
                perror("Error 2 with msgsnd!");
                free(Message);
            }
            printf("Parent msgsnd:\n type = %ld\n text = %s\n\n", Message->type, Message->text);
        }
        
        wait(NULL);
        break;
    }
}
