#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char** environ;

void task1(char** envp);
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8(const char* name);
void task9(const char* name);
void task10(int argc, char** argv, char** envp);
void task11(int argc, char** argv, char** envp);

int main(int argc, char** argv, char** envp) {
    const int task_num = 1;

    switch (task_num) {
    case 1:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task1(envp);
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
    case 7:
        if (argc != 1) {
            printf("Invalid count of arguments\n");
            break;
        }
        task7();
        break;
    case 8:
        if (argc != 2) {
            printf("Invalid count of arguments\n");
            break;
        }
        task8(argv[1]);
        break;
    case 9:
        if (argc != 2) {
            printf("Invalid count of arguments\n");
            break;
        }
        task9(argv[1]);
        break;
    case 10:
        if (argc < 2) {
            printf("Invalid count of arguments\n");
            break;
        }
        task10(argc, argv, envp);
        break;
    case 11:
        if (strcmp(argv[1], "-f") && strcmp(argv[1], "-s") || argc < 3) {
            printf("Invalid! Use 'prog_name -f command [args]' or 'prog_name -s command [argv]'\n");
            break;
        }
        task11(argc, argv, envp);
        break;
    default:
        break;
    }

    return 0;
}



void task1(char** envp) {
    printf("Before add environ:\n");
    for (size_t i = 0; environ[i]; i++) {
        printf("%s\n", environ[i]);
    }
    printf("\n");
    printf("\n");
    printf("\n");

    printf("Before add envp:\n");
    for (size_t i = 0; envp[i]; i++) {
        printf("%s\n", envp[i]);
    }
    printf("\n");
    printf("\n");
    printf("\n");

    if (setenv("AAA", "123456", 0) == -1) {
        perror("Error with setenv!");
    }
    else {
        printf("After add environ:\n");
        for (size_t i = 0; environ[i]; i++) {
            printf("%s\n", environ[i]);
        }
        printf("\n");
        printf("\n");
        printf("\n");

        printf("After add envp:\n");
        for (size_t i = 0; envp[i]; i++) {
            printf("%s\n", envp[i]);
        }
        printf("\n");
        printf("\n");
        printf("\n");

        printf("After add system env:\n");
        system("env");
        printf("\n");
        printf("\n");
        printf("\n");

        const char* str1 = getenv("AAA");
        if (str1 == NULL) {
            printf("Error in getenv AAA!\n");
        }
        else {
            printf("AAA: %s\n", str1);
        }

        const char* str2 = getenv("SHELL");
        if (str2 == NULL) {
            printf("Error in getenv SHELL!\n");
        }
        else {
            printf("SHELL: %s\n", str2);
        }

        const char* str3 = getenv("BBB");
        if (str3 == NULL) {
            printf("Error in getenv BBB!\n");
        }
        else {
            printf("BBB: %s\n", str3);
        }
    }
}



void task2() {
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
        break;
    }
}



void task3() {
    int status;
    printf("Parent before. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        exit(5);
        break;
    default:
        printf("Parent after. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        const int child = wait(&status);
        if (child == -1) {
            perror("Error with wait!");
        }
        printf("Wait for child with pid = %d until he ends. Status of child = %d\n", child, WEXITSTATUS(status));
        break;
    }
}



void task4() {
    printf("Parent before. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child starts. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        printf("Child is sleeping\n");
        sleep(0.5);
        printf("Child ends. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        break;
    default:
        printf("Parent after. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        break;
    }
}



void task5() {
    printf("Parent before. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child starts. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        break;
    default:
        printf("Parent after. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        printf("Parent is sleeping\n");
        sleep(1);
        printf("Parent ends. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        system("ps");
        break;
    }
}



void task6() {
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child starts. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        if (pause() == -1) {
            perror("Error with pause!");
        }
        break;
    default:
        printf("Parent starts. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        if (pause() == -1) {
            perror("Error with pause!");
        }
        break;
    }
}



void task7() {
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("Child starts. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        if (setpgrp() == -1) {
            perror("Error with setpgrp!");
        }
        else {
            printf("Child after setpgrp. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        }
        if (pause() == -1) {
            perror("Error with pause!");
        }
        break;
    default:
        printf("Parent starts. pid = %d, ppid = %d getpgrp = %d\n", getpid(), getppid(), getpgrp());
        if (pause() == -1) {
            perror("Error with pause!");
        }
        break;
    }
}



int copy(int ifstream, int ofstream) {
    char tmp[16];
    int res_read;
    while (res_read = read(ifstream, tmp, sizeof(tmp))) {
        const int res_write = write(ofstream, tmp, sizeof(tmp));
        if (res_write == -1) {
            perror("Error with copy in write!");
            return -1;
        }
    }
    if (res_read == -1) {
        perror("Error with copy in read!");
        return -1;
    }

    return 0;
}

void task8(const char* name) {
    int ofstream_child, ofstream_parent;
    int ifstream = open(name, O_RDONLY);
    if (ifstream == -1) {
        perror("Error with 'in' file!");
    }
    else {
        const int pid = fork();
        switch (pid) {
        case -1:
            perror("Error wth fork!");
            break;
        case 0:
            ofstream_child = open("child_file", O_CREAT | O_WRONLY | O_TRUNC, 666);
            if (ofstream_child == -1) {
                perror("Error with 'child out' file!");
            }
            else {
                if (copy(ifstream, ofstream_child) == -1) {
                    perror("Error wth child copy!");
                }
                if (close(ofstream_child) == -1) {
                    perror("Error with close child file!");
                }
            }

            printf("Child:\n");
            ofstream_child = open("child_file", O_RDONLY, 666);
            if (ofstream_child == -1) {
                perror("Error 2 with open 'child out' file");
            }
            else {
                if (copy(ofstream_child, 1) == -1) {
                    perror("Error 2 wth child copy!");
                }
                if (close(ofstream_child) == -1) {
                    perror("Error 2 with close child file!");
                }
            }
            break;
        default:
            ofstream_parent = open("parent_file", O_CREAT | O_WRONLY | O_TRUNC, 666);
            if (ofstream_parent == -1) {
                perror("Error with 'parent out' file!");
            }
            else {
                if (copy(ifstream, ofstream_parent) == -1) {
                    perror("Error wth parent copy!");
                }
                if (close(ofstream_parent) == -1) {
                    perror("Error with close parent file!");
                }
            }

            if (wait(NULL) == -1) {
                perror("Error with wait!");
            }

            printf("\n\n\n\nParent:\n");
            ofstream_parent = open("parent_file", O_RDONLY, 666);
            if (ofstream_parent == -1) {
                perror("Error 2 with open 'parent out' file");
            }
            else {
                if (copy(ofstream_parent, 1) == -1) {
                    perror("Error 2 wth parent copy!");
                }
                if (close(ofstream_parent) == -1) {
                    perror("Error 2 with close parent file!");
                }
            }
            break;
        }

        printf("\n");
        if (close(ifstream) == -1) {
            perror("Error with close 'in'!");
        }
    }
}



void task9(const char* name) {
    int ifstream_child, ifstream_parent, ofstream_child, ofstream_parent;
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        ifstream_child = open(name, O_RDONLY);
        if (ifstream_child == -1) {
            perror("Error with 'in' file!");
        }
        ofstream_child = open("child_file", O_CREAT | O_WRONLY | O_TRUNC, 666);
        if (ofstream_child == -1) {
            perror("Error with 'child out' file!");
        }
        else {
            if (copy(ifstream_child, ofstream_child) == -1) {
                perror("Error wth child copy!");
            }
            if (close(ofstream_child) == -1) {
                perror("Error with close child file!");
            }
        }

        printf("Child:\n");
        ofstream_child = open("child_file", O_RDONLY, 666);
        if (ofstream_child == -1) {
            perror("Error 2 with open 'child out' file");
        }
        else {
            if (copy(ofstream_child, 1) == -1) {
                perror("Error 2 wth child copy!");
            }
            if (close(ofstream_child) == -1) {
                perror("Error 2 with close child file!");
            }
        }

        printf("\n");
        if (close(ifstream_child) == -1) {
            perror("Error with close 'in'!");
        }
        break;
    default:
        ifstream_parent = open(name, O_RDONLY);
        if (ifstream_parent == -1) {
            perror("Error with 'in' file!");
        }
        ofstream_parent = open("parent_file", O_CREAT | O_WRONLY | O_TRUNC, 666);
        if (ofstream_parent == -1) {
            perror("Error with 'parent out' file!");
        }
        else {
            if (copy(ifstream_parent, ofstream_parent) == -1) {
                perror("Error wth parent copy!");
            }
            if (close(ofstream_parent) == -1) {
                perror("Error with close parent file!");
            }
        }

        if (wait(NULL) == -1) {
            perror("Error with wait!");
        }

        printf("\n\n\n\nParent:\n");
        ofstream_parent = open("parent_file", O_RDONLY, 666);
        if (ofstream_parent == -1) {
            perror("Error 2 with open 'parent out' file");
        }
        else {
            if (copy(ofstream_parent, 1) == -1) {
                perror("Error 2 wth parent copy!");
            }
            if (close(ofstream_parent) == -1) {
                perror("Error 2 with close parent file!");
            }
        }

        printf("\n");
        if (close(ifstream_parent) == -1) {
            perror("Error with close 'in'!");
        }
        break;
    }
}



void task10(int argc, char** argv, char** envp) {
    const int pid = fork();
    switch (pid) {
    case -1:
        perror("Error wth fork!");
        break;
    case 0:
        printf("\n\n\n\nChild:\n");

        printf("Args: \n");
        for (size_t i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }

        printf("\n\nEnv: \n");
        for (size_t i = 0; envp[i]; i++) {
            printf("%s ", envp[i]);
        }

        printf("\n\n\n");
        if (execve(argv[1], argv, envp) == -1) {
            perror("Error with execve");
        }

        printf("\n\n\n123123123123123123123123123");

        printf("\n\n");
        break;
    default:
        printf("\n\nParent:\n");

        printf("Args: \n");
        for (size_t i = 0; i < argc; i++) {
            printf("%s ", argv[i]);
        }

        printf("\n\nEnv: \n");
        for (size_t i = 0; envp[i]; i++) {
            printf("%s ", envp[i]);
        }

        printf("\n\n");
        break;
    }
}



void task11(int argc, char** argv, char** envp) {
    if (!strcmp(argv[1], "-f")) {
        execvp(argv[2], argv + 2);
        return;
    }
    if (!strcmp(argv[1], "-s")) {
        char ar[1024] = "";
        for (size_t i = 2; i < argc; i++) {
            strcat(ar, argv[i]);

            if (i != argc - 1) {
                strcat(ar, " ");
            }
        }

        system(ar);
        return;
    }

    printf("Invalid! Use 'prog_name -f command [args]' or 'prog_name -s command [argv]'");
}
