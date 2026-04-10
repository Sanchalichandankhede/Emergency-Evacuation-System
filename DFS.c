#include <stdio.h>
#include <string.h>

#define MAX_ROOMS 20

/* ── Graph ── */
int adj[MAX_ROOMS][MAX_ROOMS];
int num_rooms;

/* ── DFS state ── */
int visited[MAX_ROOMS];
int path[MAX_ROOMS];     /* current path being explored */
int path_len;
int exit_found;

/* ── Recursive DFS ── */
void dfs(int room, int exit_room) {
    visited[room] = 1;
    path[path_len++] = room;   /* add current room to path */

    printf("Room %d  ", room);

    /* base case: reached the exit */
    if (room == exit_room) {
        printf("\n\n  EXIT REACHED!\n");
        printf("  Path found: ");
        for (int i = 0; i < path_len; i++) {
            printf("Room %d", path[i]);
            if (i < path_len - 1) printf(" --> ");
        }
        printf("\n  Total rooms crossed: %d\n", path_len - 1);
        exit_found = 1;
        return;
    }

    /* explore each adjacent room (go deep first) */
    for (int neighbor = 0; neighbor < num_rooms; neighbor++) {
        if (adj[room][neighbor] == 1 && !visited[neighbor] && !exit_found) {
            dfs(neighbor, exit_room);
        }
    }

    /* backtrack: remove room from current path if exit not found */
    if (!exit_found) {
        printf("\n  [Backtracking from Room %d]", room);
        path_len--;
    }
}

/* ── Main ── */
int main() {
    int edges, u, v, src, exit_room;

    printf("=== DFS Emergency Evacuation System ===\n");
    printf("(Explores deeply — finds A path, not necessarily shortest)\n\n");

    printf("Enter number of rooms : ");
    scanf("%d", &num_rooms);

    printf("Enter number of corridors : ");
    scanf("%d", &edges);

    memset(adj, 0, sizeof(adj));

    printf("Enter corridors (room_a room_b) — rooms numbered 0 to %d:\n", num_rooms - 1);
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;   /* undirected */
    }

    printf("Enter starting room  : ");
    scanf("%d", &src);

    printf("Enter exit room      : ");
    scanf("%d", &exit_room);

    memset(visited, 0, sizeof(visited));
    path_len   = 0;
    exit_found = 0;

    printf("\n[DFS Traversal Order]: ");
    dfs(src, exit_room);

    if (!exit_found)
        printf("\n\n  No path to exit found!\n");

    return 0;
}
 *   while BFS directly finds 0→2→4 (shorter).
 */
