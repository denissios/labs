#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

// ������ ������
#define N 9

int random_number() {
    // �������� ����� /dev/urandom ��� ������
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    // ������ ������ ����� �� �����
    unsigned char byte;
    if (read(fd, &byte, sizeof(byte)) != sizeof(byte)) {
        perror("read");
        exit(1);
    }

    // �������� �����
    close(fd);

    // ����������� ���������� ����� � ��������� �� 0 �� 255
    return (int)byte;
}

// ������� ��� ����������� �������
void copy_matrix(int src[N][N], int dst[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

// ������� ��� ��������, ����� �� ��������� ����� � ������
int is_valid(int grid[N][N], int row, int col, int num) {
    // �������� ������
    for (int j = 0; j < N; j++) {
        if (grid[row][j] == num) {
            return 0;
        }
    }

    // �������� �������
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return 0;
        }
    }

    // �������� �������� 3x3
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = start_row; i < start_row + 3; i++) {
        for (int j = start_col; j < start_col + 3; j++) {
            if (grid[i][j] == num) {
                return 0;
            }
        }
    }

    // ��� �������� ��������
    return 1;
}

// ������� ��� ������� ������ ������� ��������
int solve_sudoku(int grid[N][N], int row, int col) {
    // ���� ��������� ����� �����, �� ������ ������
    if (row == N - 1 && col == N) {
        return 1;
    }

    // ���� ��������� ����� ������, �� ��������� �� ���������
    if (col == N) {
        row++;
        col = 0;
    }

    // ���� ������ ��� ���������, �� ��������� �� ���������
    if (grid[row][col] > 0) {
        return solve_sudoku(grid, row, col + 1);
    }

    // ������� ��� ��������� ����� �� 1 �� 9
    for (int num = 1; num <= 9; num++) {
        // ���������, ����� �� ��������� ����� � ������
        if (is_valid(grid, row, col, num)) {
            // ������ ����� � ������
            grid[row][col] = num;

            // ���������� ������ ������
            if (solve_sudoku(grid, row, col + 1)) {
                return 1;
            }
        }

        // ������� ����� �� ������
        grid[row][col] = 0;
    }

    // ��� ������� ��� ������ ������
    return 0;
}

// ������� ��� ������������ ���� ����� � ������
void swap_rows(int grid[N][N], int row1, int row2) {
    for (int j = 0; j < N; j++) {
        int temp = grid[row1][j];
        grid[row1][j] = grid[row2][j];
        grid[row2][j] = temp;
    }
}

// ������� ��� ������������ ���� �������� � ������
void swap_cols(int grid[N][N], int col1, int col2) {
    for (int i = 0; i < N; i++) {
        int temp = grid[i][col1];
        grid[i][col1] = grid[i][col2];
        grid[i][col2] = temp;
    }
}

// ������� ��� ������������ ���� ����� ����� � ������
void swap_row_groups(int grid[N][N], int group1, int group2) {
    for (int i = 0; i < 3; i++) {
        swap_rows(grid, group1 * 3 + i, group2 * 3 + i);
    }
}

// ������� ��� ������������ ���� ����� �������� � ������
void swap_col_groups(int grid[N][N], int group1, int group2) {
    for (int j = 0; j < 3; j++) {
        swap_cols(grid, group1 * 3 + j, group2 * 3 + j);
    }
}

// ������� ��� ���������������� ������
void transpose(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int temp = grid[i][j];
            grid[i][j] = grid[j][i];
            grid[j][i] = temp;
        }
    }
}

// ������� ��� ��������� ������
void generate_sudoku(int grid[N][N], int shuffles) {
    // �������� �������� ������
    int base[N][N] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {4, 5, 6, 7, 8, 9, 1, 2, 3},
        {7, 8, 9, 1, 2, 3, 4, 5, 6},
        {2, 3, 4, 5, 6, 7, 8, 9, 1},
        {5, 6, 7, 8, 9, 1, 2, 3, 4},
        {8, 9, 1, 2, 3, 4, 5, 6, 7},
        {3, 4, 5, 6, 7, 8, 9, 1, 2},
        {6, 7, 8, 9, 1, 2, 3, 4, 5},
        {9, 1, 2, 3, 4, 5, 6, 7, 8}
    };

    // ����������� �������� ������ � �����
    copy_matrix(base, grid);

    // ���������� ��������� ������������ � �����
    for (int i = 0; i < shuffles; i++) {
        // ����� ���������� ���� ������������
        int type = random_number() % 5;

        // ����� ��������� �������� ��� ������������
        int x = random_number() % 3;
        int y = random_number() % 3;
        while (x == y) {
            y = random_number() % 3;
        }

        // ���������� ������������ � ����������� �� ����
        switch (type) {
        case 0: // ������������ ���� ����� � ����� ������
            swap_rows(grid, x * 3 + y, x * 3 + (y + 1) % 3);
            break;
        case 1: // ������������ ���� �������� � ����� ������
            swap_cols(grid, x * 3 + y, x * 3 + (y + 1) % 3);
            break;
        case 2: // ������������ ���� ����� �����
            swap_row_groups(grid, x, y);
            break;
        case 3: // ������������ ���� ����� ��������
            swap_col_groups(grid, x, y);
            break;
        case 4: // ���������������� �����
            transpose(grid);
            break;
        }
    }
}

void remove_numbers(int grid[N][N], int count) {
    // �������� ������� ��� ������� ��������� �����
    int removed[N][N];
    memset(removed, 0, sizeof(removed));

    // �������� ��������� ����� �� �����
    for (int i = 0; i < count; i++) {
        // ��������� ��������� ����������
        int row = random_number() % N;
        int col = random_number() % N;

        // ��������, ��� ����� ��� �� �������
        if (removed[row][col] == 0) {
            // �������� ����� �� �����
            grid[row][col] = 0;
            // ������� ���������� ����� � �������
            removed[row][col] = 1;
        }
        else {
            // ���������� ��������� ����������
            i--;
        }
    }
}





int port; // ���� ��� ����� � ��������
char log_file[256] = { 0 }; // ��� ����� ��� ����
char config_file[256]; // ��� ����� ��� ����
int shmid;
int semid;
int client_socks[20];
int server_sock;

// ������� ��������� ���������, ���������� � ����������� ������
struct data {
    int num; // ���������� ��������, ������������� ��������
    char sudoku[1024]; // ������
    int interm_sud[N][N];
};

void read_config(int* port, char* log_file) {
    // �������� ����������������� ����� ��� ������
    FILE* fp = fopen(config_file, "r");
    if (fp == NULL) {
        perror("fopen");
        exit(1);
    }

    // ������ ����� � ����� ����� ��� ���� �� ����������������� �����
    if (fscanf(fp, "%d %s", port, log_file) != 2) {
        fprintf(stderr, "Invalid config file format\n");
        exit(1);
    }

    // �������� ����������������� �����
    fclose(fp);

    // ���������� ��������� ����� � ����� ����� ��� ����
    char timestamp[32];
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    if (tm == NULL) {
        perror("localtime");
        exit(1);
    }
    if (strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", tm) == 0) {
        fprintf(stderr, "Failed to format timestamp\n");
        exit(1);
    }
    strcat(log_file, timestamp);
}

void daemonize() {
    // �������� ����������� ������������ �����/������/������
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // �������� ����� ��� ����������� �������� �������
    int log_fd = open(log_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (log_fd == -1) {
        perror("open");
        exit(1);
    }

    // ��������������� ������������ �����/������/������ � ���� ��� ����
    dup2(log_fd, STDIN_FILENO);
    dup2(log_fd, STDOUT_FILENO);
    dup2(log_fd, STDERR_FILENO);

    // �������� ����������� ����� ��� ����
    close(log_fd);
}

void handle_client(int client_sock, int semid, int grid[N][N], int solution[N][N]) {
    // �������� ��� ����������� ������� � �������������� ��������
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1; // ������ ��������
    op.sem_flg = 0;
    if (semop(semid, &op, 1) == -1) {
        perror("semop");
        return;
    }

    // ����������� ����������� ������
    struct data* shmptr = (struct data*)shmat(shmid, NULL, 0);
    if (shmptr == (struct data*)-1) {
        perror("shmat");
        return;
    }

    // ��������� ����������� ������

    // �������������� ������ � ���� ������
    char sudoku[1024];
    sprintf(sudoku, "\nMystery:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                sprintf(sudoku + strlen(sudoku), ". ");
            }
            else {
                sprintf(sudoku + strlen(sudoku), "%d ", grid[i][j]);
            }
        }
        sprintf(sudoku + strlen(sudoku), "\n");
    }
    sprintf(sudoku + strlen(sudoku), "\n\nSolution:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            sprintf(sudoku + strlen(sudoku), "%d ", solution[i][j]);
        }
        sprintf(sudoku + strlen(sudoku), "\n");
    }

    strcpy(shmptr->sudoku, sudoku);
    int shm_num = shmptr->num;
    char shm_sudoku[1024];
    strcpy(shm_sudoku, shmptr->sudoku);

    // ���������� ����������� ������
    if (shmdt(shmptr) == -1) {
        perror("shmdt");
        return;
    }

    op.sem_op = 1; // ������������ ��������
    if (semop(semid, &op, 1) == -1) {
        perror("semop");
        return;
    }

    // �������� ������ �������
    if (write(client_sock, shm_sudoku, strlen(shm_sudoku) + 1) != strlen(shm_sudoku) + 1) {
        perror("write");
        close(client_sock);
    }
}

void handle_prog(int client_sock, int server_sock, int semid) {
    // ��������� ���������� ���������� ������������
    int shuffles = random_number() % 100 + 1;

    // ��������� ������ � ������� worker-���������
    for (int i = 0; i < shuffles; i++) {
        // �������� worker-��������
        pid_t worker_pid = fork();
        if (worker_pid == -1) {
            perror("fork");
            close(client_sock);
            break;
        }
        else if (worker_pid == 0) {
            // ��� worker-��������
            // �������� ��� ����������� ������� � �������������� ��������
            struct sembuf op;
            op.sem_num = 0;
            op.sem_op = -1; // ������ ��������
            op.sem_flg = 0;
            if (semop(semid, &op, 1) == -1) {
                perror("semop");
                exit(1);
            }

            // ����������� ����������� ������
            struct data* shmptr = (struct data*)shmat(shmid, NULL, 0);
            if (shmptr == (struct data*)-1) {
                perror("shmat");
                exit(1);
            }

            close(server_sock); // �������� ������ �������
            generate_sudoku(shmptr->interm_sud, random_number());

            // ���������� ����������� ������
            if (shmdt(shmptr) == -1) {
                perror("shmdt");
                exit(1);
            }

            op.sem_op = 1; // ������������ ��������
            if (semop(semid, &op, 1) == -1) {
                perror("semop");
                exit(1);
            }
            exit(0); // ���������� worker-��������
        }
        else {
            wait(NULL);
        }
    }

    // ����������� ����������� ������
    struct data* shmptr = (struct data*)shmat(shmid, NULL, 0);
    if (shmptr == (struct data*)-1) {
        perror("shmat");
        exit(1);
    }

    // ������� ������
    int solution[N][N];
    copy_matrix(shmptr->interm_sud, solution);
    solve_sudoku(solution, 0, 0);

    // �������� ����� �� ������
    int count = random_number() % 21 + 40; // ���������� ��������� ����� �� 40 �� 60
    remove_numbers(shmptr->interm_sud, count);

    handle_client(client_sock, semid, shmptr->interm_sud, solution);

    // ���������� ����������� ������
    if (shmdt(shmptr) == -1) {
        perror("shmdt");
        exit(1);
    }
}

void signal_handler(int signum) {
    // ��������� ������� SIGTERM
    if (signum == SIGTERM) {
        // �������� ���������� �������
        for (size_t i = 0; i < 20; i++) {
            if (client_socks[i] != -1) {
                handle_prog(client_socks[i], server_sock, semid);
                client_socks[i] = -1;
                close(client_socks[i]);
            }
        }

        printf("\n SIGTERM \n");
        exit(0);
    }

    // ��������� ������� SIGHUP
    if (signum == SIGHUP) {
        // ���������� ��������� SIGHUP �� ����� �������� �������� �������
        sigset_t mask;
        sigemptyset(&mask);
        sigaddset(&mask, SIGHUP);
        sigprocmask(SIG_BLOCK, &mask, NULL);
        // ������������� ����������������� �����
        read_config(&port, log_file);
        // ������������� ��������� SIGHUP
        sigprocmask(SIG_UNBLOCK, &mask, NULL);
        printf("\n SIGHUP \n");
    }

    if (signum == SIGINT) {
        // �������� ����������� ������
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl");
            exit(1);
        }
        printf("\n");
        exit(0);
    }
}

int main(int argc, char* argv[]) {
    // �������� ���������� ��������� ������
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <config_file>\n", argv[0]);
        exit(1);
    }

    // ������ ����������������� �����
    strcpy(config_file, argv[1]);
    read_config(&port, log_file);

    // daemonize();

    // ��������� ����������� ��������
    signal(SIGTERM, signal_handler);
    signal(SIGHUP, signal_handler);
    signal(SIGINT, signal_handler);

    // �������� ������
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("socket");
        exit(1);
    }

    // �������� ������ � ������
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    // ������������� ������
    if (listen(server_sock, 10) == -1) {
        perror("listen");
        exit(1);
    }

    // �������� ����������� ������
    shmid = shmget(IPC_PRIVATE, sizeof(struct data), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // ����������� ����������� ������
    struct data* shmptr = (struct data*)shmat(shmid, NULL, 0);
    if (shmptr == (struct data*)-1) {
        perror("shmat");
        exit(1);
    }

    // ������������� ����������� ������
    shmptr->num = 0;
    strcpy(shmptr->sudoku, "");

    for (size_t i = 0; i < 20; i++) {
        client_socks[i] = -1;
    }

    // �������� ��������
    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // ������������� ��������
    union semun {
        int val;
        struct semid_ds* buf;
        unsigned short* array;
    } arg;
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1) {
        perror("semctl");
        exit(1);
    }

    // �������� master-��������
    pid_t master_pid = fork();
    if (master_pid == -1) {
        perror("fork");
        exit(1);
    }
    else if (master_pid == 0) {
        // ��� master-��������
        while (1) {
            printf("Waiting...\n");
            // �������� ���������� �� �������
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_len);
            if (client_sock == -1) {
                perror("accept");
                continue;
            }
            
            for (size_t i = 0; i < 20; i++) {
                if (client_socks[i] == -1) {
                    client_socks[i] = client_sock;
                    break;
                }
            }

            // sleep(5);

            // �������� worker-��������
            pid_t worker_pid = fork();
            if (worker_pid == -1) {
                perror("fork");
                close(client_sock);
                continue;
            }
            else if (worker_pid == 0) {
                // ������ ������� �� �������
                char buffer[1024]; // ����� ��� �������� �������
                int n = read(client_sock, buffer, sizeof(buffer)); // ���������� ����������� ����
                if (n == -1) {
                    perror("read");
                    close(client_sock);
                    continue;
                }

                // �������� ������� �� ������������ "generate"
                if (strcmp(buffer, "generate") == 0) {
                    handle_prog(client_sock, server_sock, semid);

                    continue;
                }
                else {
                    char* message = "Available commands: 1. generate";
                    if (write(client_sock, message, strlen(message) + 1) != strlen(message) + 1) {
                        perror("write");
                        close(client_sock);
                        continue;
                    }
                }
                close(client_sock);
            }
            else {
                // ��� master-��������
                waitpid(worker_pid, NULL, 0);

                for (size_t i = 0; i < 20; i++) {
                    if (client_socks[i] == client_sock) {
                        client_socks[i] = -1;
                        break;
                    }
                }
                close(client_sock);
            }
        }
    }
    else {
        // ��� ������������� ��������
        close(server_sock); // �������� ������ �������
        waitpid(master_pid, NULL, 0); // �������� ���������� master-��������
    }

    // ���������� ����������� ������
    if (shmdt(shmptr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // �������� ����������� ������
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    // �������� ��������
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl");
        exit(1);
    }

    return 0;
}
