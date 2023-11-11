#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task8();
void task9();
void task10();
void task11();

int main(int argc, char** argv, char** envp) {
    const int task_num = 1;

    switch (task_num) {
    case 1:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task1();
        break;
    case 2:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task2();
        break;
    case 3:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task3();
        break;
    case 4:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task4();
        break;
    case 5:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task5();
        break;
    case 6:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task6();
        break;
    case 8:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task8();
        break;
    case 9:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task9();
        break;
    case 10:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task10();
        break;
    case 11:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task11();
        break;
    default:
        break;
    }

    return 0;
}



void handler1(int signum) {
    if (signal(signum, SIG_DFL) == SIG_ERR) {
        perror("Error with signal in handler!");
    }
    else {
        printf("\nSignal handler 1\n");
    }
}

void task1() {
    if (signal(SIGINT, handler1) == SIG_ERR) {
        perror("Error with signal!");
    }
    else {
        pause();
    }
}



void handler2(int signum) {
    printf("\nSignal handler 2\n");
}

void task2() {
    struct sigaction act;
    act.sa_handler = handler2;
    act.sa_flags = SA_RESETHAND;
    sigemptyset(&act.sa_mask);

    if (sigaction(SIGINT, &act, NULL) == -1) {
        perror("Error with sigaction");
    }
    else {
        pause();
    }
}



void handler3(int signum) {
    wait(NULL);
    printf("\nParent signal handler\n");
}

void task3() {
    struct sigaction act;
    act.sa_handler = handler3;
    act.sa_flags = SA_RESETHAND;
    sigemptyset(&act.sa_mask);

    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child\n");
        break;
    default:
        printf("Parent\n");
        if (sigaction(SIGCHLD, &act, NULL) == -1) {
            perror("Error with sigaction act2!");
        }
        pause();
        break;
    }
}



void task4() {
    int status = 0;
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child\n");
        /*for (size_t i = 0; i < 1000; i++) {
            for (size_t j = 0; j < 1000; j++) {
                printf("%lu ", i);
            }
            printf("\n\n");
        }*/

        printf("Pause\n");
        if (pause() == -1) {
            perror("Error with pause!");
        }
        printf("\n");

        exit(5);
        break;
    default:
        printf("Parent\n");
        if (wait(&status) == -1) {
            perror("Error with wait!");
        }
        else {
            printf("Status: %x\n", WEXITSTATUS(status));
        }
        break;
    }
}



void task5() {
    int status = 0;
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child\n");
        for (size_t i = 0; i < 10000; i++) {
            for (size_t j = 0; j < 10000; j++) {
                printf("%lu ", i);
            }
            printf("\n");
            printf("\n");
        }

        /*printf("Pause\n");
        if (pause() == -1) {
            perror("Error with pause!");
        }
        printf("\n");*/

        printf("\n");
        exit(5);
        break;
    default:
        printf("Parent\n");
        sleep(1);
        if (kill(pid, SIGCHLD) == -1) {
            perror("Error with kill!");
        }

        if (wait(&status) == -1) {
            perror("Error with wait!");
        }
        else {
            printf("\nStatus: %x\n", WEXITSTATUS(status));
        }
        break;
    }
}



void task6() {
    int status = 0;
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child\n");
        for (size_t i = 0; i < 10000; i++) {
            for (size_t j = 0; j < 10000; j++) {
                printf("%lu ", i);
            }
            printf("\n");
            printf("\n");
        }

        /*printf("Pause\n");
        if (pause() == -1) {
            perror("Error with pause!");
        }
        printf("\n");*/

        printf("\n");
        exit(5);
        break;
    default:
        printf("Parent\n");
        sleep(1);
        if (kill(pid, SIGINT) == -1) {
            perror("Error with kill!");
        }

        if (wait(&status) == -1) {
            perror("Error with wait!");
        }
        else {
            printf("\nStatus: %x\n", WEXITSTATUS(status));
        }
        break;
    }
}



size_t TASK8_OUTER_LOOP_NUMBER = 100000;
void handler8() {
    printf("\nSignal handler 8\n");
    TASK8_OUTER_LOOP_NUMBER = 2500;
}

void task8() {
    int status = 0;
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child\n");

        if (signal(SIGINT, handler8) == SIG_ERR) {
            perror("Error with signal!");
        }

        for (size_t i = 0; i < TASK8_OUTER_LOOP_NUMBER; i++) {
            for (size_t j = 0; j < 1000; j++) {
                printf("%lu ", i);
            }
            printf("\n");
            printf("\n");
        }

        printf("\n");
        exit(5);
        break;
    default:
        printf("Parent\n");
        sleep(1);
        if (kill(pid, SIGINT) == -1) {
            perror("Error with kill!");
        }

        if (wait(&status) == -1) {
            perror("Error with wait!");
        }
        else {
            printf("\nStatus: %x\n", WEXITSTATUS(status));
        }
        break;
    }
}



size_t TASK9_OUTER_LOOP_NUMBER = 100000;
void handler9() {
    printf("\nSignal handler 9\n");
    TASK9_OUTER_LOOP_NUMBER = 3500;
}

void task9() {
    int status = 0;
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child\n");

        if (signal(SIGALRM, handler9) == SIG_ERR) {
            perror("Error with signal!");
        }

        alarm(1);

        for (size_t i = 0; i < TASK9_OUTER_LOOP_NUMBER; i++) {
            for (size_t j = 0; j < 1000; j++) {
                printf("%lu ", i);
            }
            printf("\n");
            printf("\n");
        }

        printf("\n");
        exit(5);
        break;
    default:
        printf("Parent\n");
        if (wait(&status) == -1) {
            perror("Error with wait!");
        }
        else {
            printf("\nStatus: %x\n", WEXITSTATUS(status));
        }
        break;
    }
}



void handler10(int signum) {
    const size_t count = 4;
    printf("\nSignal %d starts\n", signum);
    for (size_t i = 0; i < count; ++i) {
        printf("%lu\n", count - i);
        sleep(1);
    }
    printf("Signal %d ends\n", signum);
}

void task10() {
    int status = 0;
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child\n");

        struct sigaction act1;
        act1.sa_handler = handler10;
        act1.sa_flags = SA_NODEFER;

        struct sigaction act2;
        act2.sa_handler = handler10;
        act2.sa_flags = SA_NODEFER;

        if (sigaction(SIGUSR1, &act1, NULL) == -1) {
            perror("Error with sigaction!");
            exit(0);
        }
        if (sigaction(SIGUSR2, &act2, NULL) == -1) {
            perror("Error with sigaction!");
            exit(0);
        }

        for (size_t i = 0; i < 20000; i++) {
            sleep(0.5);
            printf("%lu\n", i);
        }

        printf("\n");
        exit(5);
        break;
    default:
        printf("Parent\n");

        sleep(1);
        kill(pid, SIGUSR1);
        kill(pid, SIGUSR2);
        kill(pid, SIGUSR2);
        kill(pid, SIGUSR2);

        if (wait(&status) == -1) {
            perror("Error with wait!");
        }
        else {
            printf("\nStatus: %x\n", WEXITSTATUS(status));
        }
        break;
    }
}



void handler11(int signum) {
    printf("Signal %d handler\n\n", signum);
}

void task11() {
    struct sigaction sa1;
    sa1.sa_handler = handler11;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;
    sigaction(SIGUSR1, &sa1, NULL);

    struct sigaction sa2;
    sa2.sa_handler = handler11;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;
    sigaction(SIGUSR2, &sa2, NULL);

    sigset_t sync;
    sigemptyset(&sync);
    sigaddset(&sync, SIGUSR1);
    sigaddset(&sync, SIGUSR2);
    if (sigprocmask(SIG_BLOCK, &sync, NULL) == -1) {
        perror("Error with sigprocmask!");
    }

    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        int ppid = getppid();
        sigset_t s1;
        sigemptyset(&s1);
        sleep(1);
        for(size_t i = 0; i < 5; i++) {
            printf("Parent\n");
            sleep(1);
            kill(ppid, SIGUSR1);
            sigsuspend(&s1);
        }
        exit(5);
        break;
    default:
        sigset_t s2;
        sigemptyset(&s2);
        for (size_t i = 0; i < 5; i++) {
            sigsuspend(&s2);
            printf("Child\n");
            sleep(1);
            kill(pid, SIGUSR2);
        }
        break;
    }
}
