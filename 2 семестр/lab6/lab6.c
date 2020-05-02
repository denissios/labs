#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define BUFFER_LENGTH 128

typedef struct node
{
    int val;
    struct vertex* vertex;
    struct node* next;
} node;

typedef struct vertex
{
    int vertex;
    int x;
    int y;
    int count;
    struct vertex* next;
    node adj_list;
} vertex;

typedef struct Graph
{
    int numVertices;
    vertex vert_list;
} Graph;

void dialog_msg();
void dialog(int x, Graph* graph);
void timing();
void create(Graph* x);
void add_vertex(Graph* x, vertex* vertex, bool flag);
void add_edge(Graph* x, int src, int dest, bool flag1, bool flag2);
void delete_vertex(Graph* x, int id);
void remove_adj(Graph* x, int val, int vert);
void generate(Graph* graph);
void dfs(Graph* g, bool used[], vertex* cur);
bool add_adj(vertex* a, vertex* b, bool flag1, bool flag2);
void printGraph(Graph* x);
void find_connected(Graph* x, int vert, bool flag);
char* get_str(void);
int get_int(const char* msg);
int get_index(Graph* x, int vert);
vertex* get_by_id(Graph* x, int id);
void readf(Graph* x);
void save(Graph* x);

int main()
{
    srand(time(NULL));
    Graph graph = { 0 };
    int x = -1;
    readf(&graph);
    while (x != 0)
    {
        dialog_msg();
        x = get_int("Your choice");
        if (x < 0 || x > 7)
        {
            printf("[WARNING] Wrong option\n");
            continue;
        }
        printf("\n");
        dialog(x, &graph);
    }

    save(&graph);
    return 0;
}

void dialog_msg()
{
    printf("\n0. Exit\n");
    printf("1. Add new vertex\n");
    printf("2. Add new edge\n");
    printf("3. Delete vertex\n");
    printf("4. Search vertex\n");
    printf("5. Print graph\n");
    printf("6. Timing\n");
    printf("7. Generate random graph\n");
    printf("Your choice: ");
}

void dialog(int x, Graph* graph)
{
    if (x == 1) {
        create(graph);
    }

    if (x == 2) {
        printf("Enter two vertices: \n");
        printf("Enter vertex a: ");
        int a = get_int("Enter vertex a");
        printf("Enter vertex b: ");
        int b = get_int("Enter vertex b");
        add_edge(graph, a, b, true, true);
    }

    if (x == 3) {
        printf("Enter a vertex, that you want to delete: ");
        int id = get_int("Enter a vertex, that you want to delete");
        delete_vertex(graph, id);
    }

    if (x == 4) {
        int vert = get_int("vertex");
        find_connected(graph, vert, true);
    }

    if (x == 5) {
        printGraph(graph);
    }

    if (x == 6) {
        save(graph);
        timing();
        exit(0);
    }

    if (x == 7) {
        generate(graph);
    }
}

void timing()
{
    Graph* y = (Graph*)calloc(1, sizeof(Graph));
    size_t cnt1 = 1000, cnt2 = cnt1, n = 16;
    while (n--)
    {
        size_t count_vertex = cnt2;
        size_t count_edge = 2 * count_vertex;
        while (cnt2--)
        {
            vertex* ptr = (vertex*)calloc(1, sizeof(vertex));
            if (!ptr)
                return;
            ptr->vertex = rand() % count_vertex;
            ptr->x = rand() % count_vertex;
            ptr->y = rand() % count_vertex;
            add_vertex(y, ptr, false);
        }

        while (count_edge--)
            add_edge(y, rand() % count_vertex, rand() % count_vertex, false, true);

        clock_t first, last;
        first = clock();
        find_connected(y, rand() % count_vertex, false);
        last = clock();
        if (last - first < 3)
        {
            vertex* ptr = y->vert_list.next;
            while (ptr)
            {
                vertex* tmp = ptr->next;
                delete_vertex(y, ptr->vertex);
                ptr = tmp;
            }
            n++;
            cnt2 = cnt1;
            continue;
        }
        
        printf("Test number %u\n", 16 - n);
        printf("Count of vertices: %u\n", count_vertex);
        printf("Count of edges: %u\n", 2 * count_vertex);
        printf("Time = %d\n", last - first);
        printf("\n");
        
        vertex* ptr = y->vert_list.next;
        while (ptr)
        {
            vertex* tmp = ptr->next;
            delete_vertex(y, ptr->vertex);
            ptr = tmp;
        }

        cnt1 += 1000;
        cnt2 = cnt1;
    }
}

void generate(Graph* graph)
{
    int n = rand() % 10;
    while (n--)
    {
        vertex* ptr = (vertex*)calloc(1, sizeof(vertex));
        if (!ptr)
            return;
        ptr->vertex = rand() % 10;
        ptr->x = rand() % 100;
        ptr->y = rand() % 100;
        add_vertex(graph, ptr, false);
    }

    int m = rand() % 30;
    while (m--)
        add_edge(graph, rand() % 10, rand() % 10, false, true);
}

void dfs(Graph* g, bool used[], vertex* cur)
{
    if (!cur)
        return;

    int idx = get_index(g, cur->vertex);
    if (used[idx])
        return;

    used[idx] = true;
    node* ptr = cur->adj_list.next;
    while (ptr)
    {
        dfs(g, used, ptr->vertex);
        ptr = ptr->next;
    }
}

void create(Graph* x)
{
    vertex* ver = (vertex*)calloc(1, sizeof(vertex));
    if (!ver)
        return;
    printf_s("Enter num: ");
    ver->vertex = get_int("Enter num");
    printf_s("Enter x: ");
    ver->x = get_int("Enter x");
    printf_s("Enter y: ");
    ver->y = get_int("Enter y");
    ver->count = 0;
    add_vertex(x, ver, true);
}

void add_vertex(Graph* x, vertex* ver, bool flag)
{
    vertex* ptr = &x->vert_list;
    while (ptr->next)
    {
        if (ptr->next->vertex == ver->vertex)
        {
            if (flag)
                printf("You want to add an existing vertex\n");
            return;
        }
        ptr = ptr->next;
    }
    ptr->next = ver;
    x->numVertices += 1;
}

bool add_adj(vertex* a, vertex* b, bool flag1, bool flag2)
{
    node* node_ptr = &a->adj_list;
    while (node_ptr->next)
    {
        if (node_ptr->next->val == b->vertex)
        {
            if (flag1)
                printf("You want to add an existing edge\n");
            return false;
        }
        node_ptr = node_ptr->next;
    }

    if (a == b && flag2)
        a->count++;

    node_ptr->next = calloc(1, sizeof(node));
    node_ptr->next->val = b->vertex;
    node_ptr->next->vertex = b;
    return true;
}

void add_edge(Graph* x, int src, int dest, bool flag1, bool flag2)
{
    vertex* a = NULL;
    vertex* b = NULL;

    vertex* ptr = &x->vert_list;
    while (ptr->next)
    {
        if (ptr->next->vertex == src)
            a = ptr->next;
        if (ptr->next->vertex == dest)
            b = ptr->next;
        ptr = ptr->next;
    }

    if (a == NULL || b == NULL)
    {
        if (flag1)
            printf_s("We don't have one of these vertices\n");
        return;
    }

    if (add_adj(a, b, flag1, flag2) && a != b)
    {
        if (flag2)
        {
            a->count++;
            b->count++;
        }
        add_adj(b, a, flag1, flag2);
    }
}

void delete_vertex(Graph* x, int id)
{
    vertex* prev = &x->vert_list;
    vertex* ptr = prev->next;
    while (ptr && ptr->vertex != id)
    {
        prev = ptr;
        ptr = ptr->next;
    }
    if (!ptr)
    {
        printf("We don't have this vertex\n");
        return;
    }

    node* node_ptr = ptr->adj_list.next;
    while (node_ptr)

    {
        if (node_ptr->val != id)
            remove_adj(x, node_ptr->val, ptr->vertex);

        node* tmp = node_ptr->next;
        free(node_ptr);
        node_ptr = tmp;
    }

    prev->next = ptr->next;
    free(ptr);

    x->numVertices--;
}

void remove_adj(Graph* x, int val, int vert)
{
    vertex* ptr = x->vert_list.next;
    while (ptr && ptr->vertex != val)
        ptr = ptr->next;

    if (!ptr)
        return;

    node* prev_node = &ptr->adj_list;
    node* node_ptr = prev_node->next;
    while (node_ptr && node_ptr->val != vert)
    {
        prev_node = node_ptr;
        node_ptr = node_ptr->next;
    }

    if (node_ptr)
    {
        prev_node->next = node_ptr->next;
        free(node_ptr);
    }
}

void printGraph(Graph* x)
{
    vertex* ptr = x->vert_list.next;
    while (ptr)
    {
        printf("\n Adjacency list of vertex %d:\n ", ptr->vertex);

        node* adj = ptr->adj_list.next;

        if (!adj)
        {
            printf("This vertex don't have adjacent vertices\n");
            ptr = ptr->next;
            continue;
        }

        while (adj)
        {
            printf("-> %d ", adj->val);
            adj = adj->next;
        }

        printf("\n");
        ptr = ptr->next;
    }
}

void find_connected(Graph* x, int vert, bool flag1)
{
    bool flag2 = false;
    vertex* tmp = &x->vert_list;
    while (tmp->next)
    {
        if (tmp->next->vertex == vert)
        {
            flag2 = true;
            break;
        }
        tmp = tmp->next;
    }
    if (!flag2 && flag1)
    {
        printf("We don't have this vertex\n");
        return;
    }

    bool* used = (bool*)calloc(x->numVertices, sizeof(bool));
    dfs(x, used, get_by_id(x, vert));
    
    if (flag1)
        printf("Connected vertices: ");
    vertex* ptr = x->vert_list.next;
    flag2 = false;
    for (int i = 0; i < x->numVertices; ++i, ptr = ptr->next)
        if (used[i] && ptr->vertex != vert)
        {
            if (flag1)
                printf("%d ", ptr->vertex);
            flag2 = true;
        }
    if (!flag2 && flag1)
        printf("This vertex don't have connected vertices");

    if (flag1)
        printf("\n");
    free(used);
}

void readf(Graph* x)
{
    FILE* fd = fopen("Graph", "rb");
    if (fd == NULL)
        return;
    
    size_t count = 0;
    fread(&count, sizeof(int), 1, fd);
    for (size_t i = 0; i < count; i++)
    {
        if (feof(fd) != 0)
        {
            fclose(fd);
            return;
        }
        vertex* ptr = (vertex*)calloc(1, sizeof(vertex));
        if (!ptr)
            return;
        fread(ptr, sizeof(vertex), 1, fd);
        add_vertex(x, ptr, true);
        ptr->next = NULL;
        ptr->adj_list.next = NULL;
    }

    vertex* ptr = x->vert_list.next;
    if (!ptr)
        return;
    while (ptr)
    {
        if (feof(fd) != 0)
        {
            fclose(fd);
            return;
        }
        
        fread(&count, sizeof(int), 1, fd);
        for (size_t i = 0; i < count; i++)
        {
            int a = 0;
            fread(&a, sizeof(int), 1, fd);
            add_edge(x, ptr->vertex, a, false, false);
        }

        ptr = ptr->next;
    }
    fclose(fd);
}

void save(Graph* x)
{
    FILE* fd = fopen("Graph", "wb");
    vertex* ptr = x->vert_list.next;
    if (!ptr)
    {
        fclose(fd);
        return;
    }
    fwrite(&(x->numVertices), sizeof(int), 1, fd);
    while (ptr)
    {
        fwrite(ptr, sizeof(vertex), 1, fd);
        ptr = ptr->next;
    }
    ptr = x->vert_list.next;
    while (ptr)
    {
        fwrite(&(ptr->count), sizeof(int), 1, fd);
        node* adj = ptr->adj_list.next;
        while (adj)
        {
            fwrite(&(adj->val), sizeof(int), 1, fd);
            adj = adj->next;
        }
        ptr = ptr->next;
    }
    fclose(fd);

    ptr = x->vert_list.next;
    while (ptr)
    {
        vertex* tmp = ptr->next;
        delete_vertex(x, ptr->vertex);      
        ptr = tmp;
    }
    
    free(ptr);
}

char* get_str(void)
{
    char buf[BUFFER_LENGTH] = "";
    size_t str_len = 0;
    char* str = (char*)malloc(sizeof(char));
    if (!str)
    {
        printf("Cannot allocate");
        return NULL;
    }

    *str = '\0';

    int n = 0;
    do {
        n = scanf_s("%127[^\n]", buf, BUFFER_LENGTH);
        if (n == 1)
        {
            str_len += strlen(buf);
            char* tmp = (char*)realloc(str, str_len + 1);
            if (!tmp)
            {
                printf("Cannot reallocate");
                free(str);
                return NULL;
            }
            str = tmp;
            strcat(str, buf);
        }
        else if (!n)
            scanf_s("%*c");
        else
        {
            free(str);
            return NULL;
        }
    } while (n);

    return str;
}

int get_int(const char* msg)
{
    int res = 0;
    int ret_val = 0;
    while (!ret_val)
    {
        ret_val = scanf_s("%d", &res);
        if (!ret_val)
        {
            printf("[ERROR] Waiting for integer\n");
            scanf_s("%*[^\n]");
            printf("%s: ", msg);
        }
    }

    scanf_s("%*c");

    return res;
}

int get_index(Graph* x, int vert)
{
    int idx = 0;
    vertex* ptr = x->vert_list.next;
    while (ptr && ptr->vertex != vert)
    {
        ++idx;
        ptr = ptr->next;
    }

    return idx;
}

vertex* get_by_id(Graph* x, int id)
{
    vertex* ptr = x->vert_list.next;
    if (!ptr)
        return;
    while (ptr && ptr->vertex != id)
        ptr = ptr->next;

    return ptr;
}