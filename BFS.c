/*
 * BFS - Emergency Evacuation Route Planner
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 20

/* ── Graph ── */
int adj[MAX_ROOMS][MAX_ROOMS];   /* adjacency matrix */
int num_rooms;

/* ── BFS state ── */
int visited[MAX_ROOMS];
int parent[MAX_ROOMS];           /* to reconstruct path */
int queue[MAX_ROOMS * MAX_ROOMS];
int front, rear;

/* ── Queue helpers ── */
void enqueue(int room) { queue[rear++] = room; }
int  dequeue()         { return queue[front++]; }
int  is_empty()        { return front == rear; }

/* ── Print path from source to exit using parent[] ── */
void print_path(int src, int dest) {
    int path[MAX_ROOMS], len = 0;

    /* trace back from exit to source */
    int cur = dest;
    while (cur != -1) {
        path[len++] = cur;
        cur = parent[cur];
    }

    printf("\n  Path found: ");
    for (int i = len - 1; i >= 0; i--) {
        printf("Room %d", path[i]);
        if (i > 0) printf(" --> ");
    }
    printf("\n  Total rooms crossed: %d\n", len - 1);
}

/* ── BFS traversal ── */
void bfs(int src, int exit_room) {
    /* initialise */
    memset(visited, 0, sizeof(visited));
    memset(parent, -1, sizeof(parent));
    front = rear = 0;

    printf("\n[BFS Traversal Order]: ");

    visited[src] = 1;
    enqueue(src);

    while (!is_empty()) {
        int room = dequeue();
        printf("Room %d  ", room);

        if (room == exit_room) {
            printf("\n\n  EXIT REACHED!\n");
            print_path(src, exit_room);
            return;
        }

        /* explore all adjacent rooms */
        for (int neighbor = 0; neighbor < num_rooms; neighbor++) {
            if (adj[room][neighbor] == 1 && !visited[neighbor]) {
                visited[neighbor] = 1;
                parent[neighbor] = room;
                enqueue(neighbor);
            }
        }
    }

    printf("\n\n  No path to exit found!\n");
}

/* ── Main ── */
int main() {
    int edges, u, v, src, exit_room;

    printf("=== BFS Emergency Evacuation System ===\n");
    printf("(Finds the SHORTEST path to exit)\n\n");

    printf("Enter number of rooms : ");
    scanf("%d", &num_rooms);

    printf("Enter number of corridors : ");
    scanf("%d", &edges);

    memset(adj, 0, sizeof(adj));

    printf("Enter corridors (room_a room_b) — rooms numbered 0 to %d:\n", num_rooms - 1);
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;   /* undirected: corridor goes both ways */
    }

    printf("Enter starting room  : ");
    scanf("%d", &src);

    printf("Enter exit room      : ");
    scanf("%d", &exit_room);

    bfs(src, exit_room);

    return 0;
}
