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

void task1(const char* mode);
void task2();
void task3();
void task4();
void task5();
void task6();
void task7(const char* name);
void task10();
void task11();

int main(int argc, char** argv, char** envp) {
    const int task_num = 1;

    switch (task_num) {
    case 1:
        if (argc != 2) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task1(argv[1]);
        break;
    case 2:
        if (argc != 1) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task2();
        break;
    case 3:
        if (argc != 1) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task3();
        break;
    case 4:
        if (argc != 1) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task4();
        break;
    case 5:
        if (argc != 1) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task5();
        break;
    case 6:
        if (argc != 1) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task6();
        break;
    case 7:
        if (argc != 2) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task7(argv[1]);
        break;
    case 10:
        if (argc != 1) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task10();
        break;
    case 11:
        if (argc != 1) {
            printf("Invalid count of arguments or their value\n");
            break;
        }
        task11();
        break;
    default:
        break;
    }

    return 0;
}



void task1(const char* mode_str) {
    const int mode = strncmp(mode_str, "1", 1) == 0 ? 1 : 0;
    int pipefd[2];
    char tmp[1];

    printf("%d\n", mode);

    if (pipe(pipefd) == -1) {
        perror("Error with pipe!");
    }
    else {
        const int pid = fork();
        switch (pid) {
        case -1:
            perror("Error with fork!");
            break;
        case 0:
            printf("Child\n");
            sleep(1);

            const int res_read = read(pipefd[0], tmp, 1);
            if (res_read == -1) {
                perror("Error with read in child!");
            }
            else {
                printf("Read in child: %s\n", tmp);
            }

            sleep(1);

            if (mode == 1) {
                const int res_write = write(pipefd[1], tmp, 1);
                if (res_write == -1) {
                    perror("Error with write in child!");
                }
            }

            close(pipefd[0]);
            close(pipefd[1]);
            break;
        default:
            printf("Parent\n");

            const int res_write = write(pipefd[1], "a", 1);
            if (res_write == -1) {
                perror("Error with write in parent!");
            }

            sleep(3);

            if (mode == 1) {
                const int res_read = read(pipefd[0], tmp, 1);
                if (res_read == -1) {
                    perror("Erorr with read in parent!");
                }
                else {
                    printf("Read in parent: %s\n", tmp);
                }
            }

            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            break;
        }
    }
}



void task2() {
    int pipefd[2], res_read;
    char tmp[100];

    if (pipe(pipefd) == -1) {
        perror("Error with pipe!");
    }
    else {
        const int pid = fork();
        switch (pid) {
        case -1:
            perror("Error with fork!");
            break;
        case 0:
            printf("Child\n");

            while ((res_read = read(0, tmp, 100)) > 0) {
                write(pipefd[1], tmp, res_read);
            }

            close(pipefd[0]);
            close(pipefd[1]);
            break;
        default:
            printf("Parent\n");

            while ((res_read = read(pipefd[0], tmp, 100)) > 0) {
                write(1, tmp, res_read);
                alarm(5);
            }

            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            break;
        }
    }
}



void task3() {
    int pipefd[2], res_read, res_write;
    char tmp[100];

    if (pipe(pipefd) == -1) {
        perror("Error with pipe!");
    }
    else {
        const int pid = fork();
        switch (pid) {
        case -1:
            perror("Error with fork!");
            break;
        case 0:
            printf("Child\n");

            while (1) {
                if ((res_read = read(0, tmp, 100)) > 0) {
                    printf("Child reads from keyboard: %s", tmp);
                    if (write(pipefd[1], tmp, res_read) == -1) {
                        perror("Error 1 with write in child");
                    }
                    else {
                        printf("Child writes in pipefd[1]: %s", tmp);
                    }
                    sleep(1);
                    if (read(pipefd[0], tmp, 100) == -1) {
                        perror("Error 2 with read in child");
                    }
                    else {
                        printf("\nChild reads from pipefd[0]: %s\n\n", tmp);
                    }
                }
            }

            close(pipefd[0]);
            close(pipefd[1]);
            break;
        default:
            printf("Parent\n");

            while (1) {
                if ((res_read = read(pipefd[0], tmp, 100)) > 0) {
                    printf("\nParent reads from pipefd[0]: %s", tmp);
                    sleep(1);
                    if (write(pipefd[1], tmp, res_read) == -1) {
                        perror("Error with write in parent!");
                    }
                    else {
                        printf("Parent writes in pipefd[1]: %s", tmp);
                    }
                    sleep(1);
                }
            }

            close(pipefd[0]);
            close(pipefd[1]);
            wait(NULL);
            break;
        }
    }
}



void task4() {
    int pipefd[2], res_read, res_write;
    char tmp[100];

    if (pipe(pipefd) == -1) {
        perror("Error with pipe!");
    }
    else {
        const int pid = fork();
        switch (pid) {
        case -1:
            perror("Error with fork!");
            break;
        case 0:
            printf("Child\n");

            char fd_read_num[2];
            char fd_write_num[2];
            sprintf(fd_read_num, "%d", pipefd[0]);
            sprintf(fd_write_num, "%d", pipefd[1]);
            execl("exec4.out", "exec4.out", fd_read_num, fd_write_num, NULL);

            perror("Error with exec!");
            break;
        default:
            printf("Parent\n");

            while ((res_read = read(pipefd[0], tmp, 100)) > 0) {
                write(1, "Parent reads from pipefd[0]: ", sizeof("Parent read from pipefd[0]: "));
                write(1, tmp, res_read);
                printf("\n\n");
            }

            close(pipefd[0]);
            close(pipefd[1]);
            break;
        }
    }
}



void task5() {
    int pipefd[2], res_read, res_write;
    char tmp[100];

    if (pipe(pipefd) == -1) {
        perror("Error with pipe!");
    }
    else {
        const int pid = fork();
        switch (pid) {
        case -1:
            perror("Error with fork!");
            break;
        case 0:
            printf("Child\n");

            close(pipefd[0]);
            close(1);
            dup(pipefd[1]);
            close(pipefd[1]);

            execlp("who", "who", NULL);

            perror("Error with who!");
            break;
        default:
            printf("Parent\n");

            close(pipefd[1]);
            close(0);
            dup(pipefd[0]);
            close(pipefd[0]);
            
            execlp("wc", "wc", "-l", NULL);

            perror("Error with wc");
            break;
        }
    }
}



void task6() {
    struct stat Stat;
    int pipefd[2], res_open, res_read, res_write;
    const char* fileName = "../../../../../../../../file6";
    char tmp[100];

    if (stat(fileName, &Stat) == -1) {
        perror("Error with stat!");
    }
    if (!S_ISFIFO(Stat.st_mode)) {
        printf("Not FIFO!\n");
    }

    if (pipe(pipefd) == -1) {
        perror("Error with pipe!");
    }
    else {
        const int pid = fork();
        switch (pid) {
        case -1:
            perror("Error with fork!");
            break;
        case 0:
            printf("Child\n");
            if ((res_open = open(fileName, O_RDONLY | O_NDELAY)) == -1) {  // 
                perror("Error with open in child!");
            }
            
            while ((res_read = read(res_open, tmp, sizeof(tmp))) > 0) {
                write(1, tmp, res_read);
            }

            if (close(res_open) == -1) {
                perror("Error with close in child!");
            }

            break;
        default:
            printf("Parent\n");
            sleep(1);
            if((res_open = open(fileName, O_WRONLY | O_NDELAY)) == -1) {  // 
                perror("Error with open in parent!");
            }

            while ((res_read = read(0, tmp, sizeof(tmp))) > 0) {
                write(res_open, tmp, res_read);
            }

            if (close(res_open) == -1) {
                perror("Error with close in parent!");
            }
           
            break;
        }
    }
}



void task7(const char* fileName) {
    struct flock lock;
    int res_open, res_read;
    char tmp[100];
    
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;

    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error with fork!");
        break;
    case 0:
        printf("Child\n");
        if ((res_open = open(fileName, O_RDWR | O_TRUNC)) == -1) {
            perror("Error with open in child!");
        }

        for (size_t i = 0; i < 50; i++) {
            lock.l_type = F_WRLCK;
            if (fcntl(res_open, F_SETLKW, &lock) == -1) {
                perror("Error with fcntl in child!");
            }
            if ((res_read = read(res_open, tmp, sizeof(tmp))) > 0) {
                write(1, tmp, res_read);
            };

            lock.l_type = F_UNLCK;
            fcntl(res_open, F_SETLK, &lock);
        }

        printf("\n\n");
        break;
    default:
        printf("Parent\n");
        if ((res_open = open(fileName, O_RDWR | O_TRUNC)) == -1) {
            perror("Error with open in parent!");
        }

        lock.l_type = F_WRLCK;
        if (fcntl(res_open, F_SETLKW, &lock) == -1) {
            perror("Error with fcntl in parent!");
        }
        for (size_t i = 0; i < 50; i++) {
            write(res_open, "1234568790\n", sizeof("1234568790\n"));
        }

        lock.l_type = F_UNLCK;
        fcntl(res_open, F_SETLK, &lock);

        if (close(res_open) == -1) {
            perror("Error with close in parent!");
        }

        wait(NULL);
        break;
    }
}



void task10() {
    int res_open, res_read;
    char tmp[5];

    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error with fork!");
        break;
    case 0:
        printf("Child\n");

        while (1) {
            res_read = read(0, tmp, sizeof(tmp));
            if (res_read == -1) {
                perror("Error with read in child!");
                break;
            }

            write(1, "In child: ", sizeof("In child: "));
            write(1, tmp, res_read);
        }

        break;
    default:
        printf("Parent\n");

        while (1) {
            res_read = read(0, tmp, sizeof(tmp));
            if (res_read == -1) {
                perror("Error with read in parent!");
                break;
            }
            write(1, "In parent: ", sizeof("In parent: "));
            write(1, tmp, res_read);

        }

        wait(NULL);
        break;
    }
}



void task11() {
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;

    int res_open, res_read;
    char tmp[5];

    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error with fork!");
        break;
    case 0:
        printf("Child\n");

        while ((res_read = read(0, tmp, sizeof(tmp))) > 0) {
            lock.l_type = F_WRLCK;
            if (fcntl(1, F_SETLKW, &lock) == -1) {
                perror("Error with fcntl in child!");
            }
            write(1, "In child: ", sizeof("In child: "));
            write(1, tmp, res_read);

            lock.l_type = F_UNLCK;
            fcntl(0, F_SETLK, &lock);
        }

        break;
    default:
        printf("Parent\n");

        while ((res_read = read(0, tmp, sizeof(tmp))) > 0) {
            write(1, "In parent: ", sizeof("In parent: "));
            write(1, tmp, res_read);
        }

        lock.l_type = F_UNLCK;
        fcntl(0, F_SETLK, &lock);

        wait(NULL);
        break;
    }
}
