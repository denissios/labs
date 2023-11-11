#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

void task1();
void task2(const char* name, const char* permissions);
void task4(const char* name);
void task7(const char* name);
void task8(int argc, char** argv);
void task9(int argc, char** argv);
void task10(const char* name);
void task11(int argc, char** argv);

int main(int argc, char** argv) {
    const int task_num = 11;

    switch (task_num) {
        case 1:
            task1();
            break;
        case 2:
            if (argc != 3) {
                printf("Invalid count of arguments\n");
                break;
            }
            task2(argv[1], argv[2]);
            break;
        case 4:
            if (argc != 2) {
                printf("Invalid count of arguments\n");
                break;
            }
            task4(argv[1]);
            break;
        case 7:
            if (argc != 2) {
                printf("Invalid count of arguments\n");
                break;
            }
            task7(argv[1]);
            break;
        case 8:
            if (argc < 1 || argc > 3) {
                printf("Invalid count of arguments\n");
                break;
            }
            task8(argc, argv);
            break;
        case 9:
            if (argc < 1 || argc > 3) {
                printf("Invalid count of arguments\n");
                break;
            }
            task9(argc, argv);
            break;

        case 10:
            if (argc != 2) {
                printf("Invalid count of arguments\n");
                break;
            }
            task10(argv[1]);
            break;
        case 11:
            if (argc < 2) {
                printf("Invalid count of arguments\n");
                break;
            }
            task11(argc, argv);
            break;
        default:
            break;
    }

    return 0;
}



void task1() {
    int file = open("file", O_RDONLY);
    if (file == -1) {
        const char* err1 = "errno: ";
        write(STDOUT_FILENO, err1, sizeof(char) * strlen(err1));
        char tmp[5];
        int length = snprintf(tmp, 5, "%d", errno);
        write(STDOUT_FILENO, tmp, sizeof(char) * length);
        write(STDOUT_FILENO, "\n", sizeof(char));

        const char* err2 = "strerror: ";
        write(STDOUT_FILENO, err2, sizeof(char) * strlen(err2));
        write(STDOUT_FILENO, strerror(errno), sizeof(char) * strlen(strerror(errno)));
        write(STDOUT_FILENO, "\n", sizeof(char));

        perror("perror");
        write(STDOUT_FILENO, "\n", sizeof(char));
    }
    else {
        close(file);
    }
}



void task2(const char* name, const char* perm) {
    const int permissions = strtol(perm, NULL, 10);
    int file = open(name, O_CREAT | O_WRONLY | O_TRUNC, permissions);
    if (file == -1) {
        perror("Error with create file!");
    }
    else {
        const char* str1 = "lalalalalala\n";
        const char* str2 = "papapapap\n";
        const int res1 = write(file, str1, sizeof(char) * strlen(str1));
        const int res2 = write(file, str2, sizeof(char) * strlen(str2));
        if (res1 == -1 || res2 == -1) {
            perror("Error with write!");
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
        else {
            const char* result = "After write";
            write(STDOUT_FILENO, result, strlen(result));
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
        if (close(file) == -1) {
            perror("Error with close!");
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
    }

    file = open(name, O_RDONLY);
    if (file == -1) {
        perror("Error 2 with open file!");
    }
    else {
        char tmp[64];
        const int res = read(file, tmp, sizeof(tmp));
        if (res == -1) {
            perror("Error with read file!");
        }
        write(STDOUT_FILENO, tmp, res);
        if (close(file) == -1) {
            perror("Error 2 with close!");
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
    }

    file = open(name, O_RDWR);
    if (file == -1) {
        perror("Error 3 with open file!");
    } 
    else {
        if (close(file) == -1) {
            perror("Error 3 with close!");
        }
        else {
            const char* result = "End";
            write(STDOUT_FILENO, result, strlen(result));
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
    }
}



void task4(const char* name) {
    int permissions = strtol("666", NULL, 8);
    int file = open(name, O_CREAT | O_RDWR | O_TRUNC, permissions);
    if (file == -1) {
        perror("Error with create file!");
    }
    else {
        const char* str1 = "1234567890\n";
        const char* str2 = "0987654321\n";
        const int res1 = write(file, str1, sizeof(char) * strlen(str1));
        const int res2 = write(file, str2, sizeof(char) * strlen(str2));
        if (res1 == -1 || res2 == -1) {
            perror("Error with write!");
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
        
        int seek_count = lseek(file, 0, SEEK_SET);
        if (seek_count == -1) {
            perror("Error with lseek!");
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
        char tmp[64];
        int res = read(file, tmp, sizeof(tmp));
        if (res == -1) {
            perror("Error with read file!");
        }
        write(STDOUT_FILENO, tmp, res);
        write(STDOUT_FILENO, "\n", sizeof(char));

        seek_count = lseek(file, 2, SEEK_SET);
        if (seek_count == -1) {
            perror("Error 2 with lseek!");
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
        res = read(file, tmp, sizeof(tmp));
        if (res == -1) {
            perror("Error 2 with read file!");
        }
        write(STDOUT_FILENO, tmp, res);
        write(STDOUT_FILENO, "\n", sizeof(char));

        seek_count = lseek(file, -6, SEEK_CUR);
        if (seek_count == -1) {
            perror("Error 3 with lseek!");
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
        res = read(file, tmp, sizeof(tmp));
        if (res == -1) {
            perror("Error 3 with read file!");
        }
        write(STDOUT_FILENO, tmp, res);
        write(STDOUT_FILENO, "\n", sizeof(char));

        seek_count = lseek(file, -6, SEEK_END);
        if (seek_count == -1) {
            perror("Error 4 with lseek!");
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
        res = read(file, tmp, sizeof(tmp));
        if (res == -1) {
            perror("Error 4 with read file!");
        }
        write(STDOUT_FILENO, tmp, res);
        write(STDOUT_FILENO, "\n", sizeof(char));


        const char* raz = "Raz\n";
        if (lseek(file, 512 * 512, SEEK_END) == -1) {
            perror("Error with seek in Raz");
        }
        const int resRaz = write(file, raz, strlen(raz));
        if (resRaz == -1) {
            perror("Error with write in Raz");
        }

        if (close(file) == -1) {
            perror("Error with close!");
        }
        else {
            const char* result = "End";
            write(STDOUT_FILENO, result, strlen(result));
            write(STDOUT_FILENO, "\n", sizeof(char));
        }
    }
}



void task7(const char* name) {
    struct stat Stat;
    const int stat_res = stat(name, &Stat);
    if (stat_res == -1) {
        perror("Error with stat!");
        return;
    }

    char tmp[64];

    const char* device = "Device: ";
    write(STDOUT_FILENO, device, sizeof(char) * strlen(device));
    int sprintf_res = (int)sprintf(tmp, "%u", (unsigned int)Stat.st_dev);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* inode = "inode: ";
    write(STDOUT_FILENO, inode, sizeof(char) * strlen(inode));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_ino);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* Mode = "Mode: ";
    write(STDOUT_FILENO, Mode, sizeof(char) * strlen(Mode));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_mode);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* Link = "Link: ";
    write(STDOUT_FILENO, Link, sizeof(Link) * strlen(Link));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_nlink);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* UID = "UID: ";
    write(STDOUT_FILENO, UID, sizeof(char) * strlen(UID));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_uid);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* GID = "GID: ";
    write(STDOUT_FILENO, GID, sizeof(char) * strlen(GID));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_gid);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* Dev = "Dev: ";
    write(STDOUT_FILENO, Dev, sizeof(char) * strlen(Dev));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_rdev);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* Size = "Size: ";
    write(STDOUT_FILENO, Size, sizeof(char) * strlen(Size));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_size);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* Blk = "Blk: ";
    write(STDOUT_FILENO, Blk, sizeof(char) * strlen(Blk));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_blksize);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* Blocks = "Blocks: ";
    write(STDOUT_FILENO, Blocks, sizeof(char) * strlen(Blocks));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_blocks);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* aTime = "aTime: ";
    write(STDOUT_FILENO, aTime, sizeof(char) * strlen(aTime));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_atime);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* mTime = "mTime: ";
    write(STDOUT_FILENO, mTime, sizeof(char) * strlen(mTime));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_mtime);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));

    const char* cTime = "cTime: ";
    write(STDOUT_FILENO, cTime, sizeof(char) * strlen(cTime));
    sprintf_res = (int)sprintf(tmp, "%u", (unsigned int) Stat.st_ctime);
    write(STDOUT_FILENO, tmp, sprintf_res * sizeof(char));
    write(STDOUT_FILENO, "\n", sizeof(char));
}



int copy(int ifstream, int ofstream) {
    char tmp[256];
    int res_read;
    while(res_read = read(ifstream, tmp, sizeof(tmp))) {
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

void task8(int argc, char** argv) {
    int ifstream, ofstream;
    if (argc < 2) {
        ifstream = STDIN_FILENO;
    }
    else {
        ifstream = open(argv[1], O_RDONLY);
        if (ifstream == -1) {
            perror("Error with 'in' file!");
        }
    }
    if (argc < 3) {
        ofstream = STDOUT_FILENO;
    }
    else {
        ofstream = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 666);
        if (ofstream == -1) {
            perror("Error with 'out' file!");
        }
    }

    if(copy(ifstream, ofstream) != -1) {
        const char* res = "Copied!";
        write(STDOUT_FILENO, res, sizeof(char) * strlen(res));
        write(STDOUT_FILENO, "\n", sizeof(char));
    };

    if (close(ifstream) == -1) {
        perror("Error with close 'in'!");
    }
    if (close(ofstream) == -1) {
        perror("Error with close 'out'!");
    }
}



int copy_standart() {
    char tmp[256];
    int res_read;
    while (res_read = read(STDIN_FILENO, tmp, sizeof(tmp))) {
        const int res_write = write(STDOUT_FILENO, tmp, sizeof(tmp));
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

void task9(int argc, char** argv) {
    int ifstream, ofstream, old_in, old_out;
    if (argc < 2) {
        ifstream = STDIN_FILENO;
    }
    else {
        old_in = dup(0);
        if (close(0) == -1) {
            perror("Error with close default 'in'!");
        }

        ifstream = open(argv[1], O_RDONLY);
        if (ifstream == -1) {
            perror("Error with 'in' file!");
        }
    }
    if (argc < 3) {
        ofstream = STDOUT_FILENO;
    }
    else {
        old_out = dup(1);
        if (close(1) == -1) {
            perror("Error with close default 'out'!");
        }

        ofstream = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 666);
        if (ofstream == -1) {
            perror("Error with 'out' file!");
        }
    }

    if (copy_standart() != -1) {
        if (argc == 2 && dup2(old_in, STDIN_FILENO) == -1) {
            perror("Error with return default 'in'!");
        }
        if (argc == 3 && dup2(old_out, STDOUT_FILENO) == -1) {
            perror("Error with return default 'in'!");
        }

        const char* res = "Copied!";
        write(STDOUT_FILENO, res, sizeof(char) * strlen(res));
        write(STDOUT_FILENO, "\n", sizeof(char));
    };

    if (close(ifstream) == -1) {
        perror("Error with close 'in'!");
    }
    if (close(ofstream) == -1) {
        perror("Error with close 'out'!");
    }
}



void task10(const char* name) {
    int file = open(name, O_RDONLY);
    if (file == -1) {
        perror("Erorr file open file!");
    }

    struct stat Stat;
    if (stat(name, &Stat) == -1) {
        perror("Error with stat!");
    }
    else {
        for (int i = Stat.st_size - 1; i >= 0; i--) {
            char tmp[1];

            const int lseek_res = lseek(file, i, SEEK_SET);
            if (lseek_res == -1) {
                perror("Error with lseek!");
                break;
            }

            const int read_res = read(file, tmp, sizeof(char));
            if (read_res == -1) {
                perror("Error with read!");
                break;
            }

            const int write_res = write(STDOUT_FILENO, tmp, sizeof(char));
            if (write_res == -1) {
                perror("Error with write!");
                break;
            }
        }

        write(STDOUT_FILENO, "\n", sizeof(char));
        if (close(file) == -1) {
            perror("Error with close 'in'!");
        }
    }

    const char* result = "End";
    write(STDOUT_FILENO, result, strlen(result));
    write(STDOUT_FILENO, "\n", sizeof(char));
}



void task11(int argc, char** argv) {
    int max_size = 0, number = 0;
    for (size_t i = 1; i < argc; i++) {
        struct stat Stat;
        if (stat(argv[i], &Stat) == -1) {
            perror("Error with stat!");
        }
        else {
            if (Stat.st_size > max_size) {
                max_size = Stat.st_size;
                number = i;
            }
        }
    }

    const char* res1 = "Filename: ";
    write(STDOUT_FILENO, res1, sizeof(char) * strlen(res1));
    write(STDOUT_FILENO, argv[number], sizeof(char) * strlen(argv[number]));
    write(STDOUT_FILENO, "\n", sizeof(char));

    char tmp[64];
    const int n = sprintf(tmp, "%u", (unsigned int)(sizeof(char) * max_size));
    const char* res2 = "File size: ";
    write(STDOUT_FILENO, res2, sizeof(char) * strlen(res2));
    write(STDOUT_FILENO, tmp, sizeof(char) * n);
    write(STDOUT_FILENO, "\n", sizeof(char));
}
