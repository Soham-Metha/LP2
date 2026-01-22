#include <assert.h>
#include <proj.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAZE_HEIGHT 15
#define MAZE_WIDTH  15

typedef enum Block {
    BLOCK_EMPTY,
    BLOCK_WALL,
    BLOCK_START,
    BLOCK_END,
    BLOCK_FILL,
} Block;

typedef struct Point {
    int x;
    int y;
} Point;

Block maze[MAZE_HEIGHT][MAZE_WIDTH] = { 0 };
Point maze_dim                      = { 0 };

#define IN_BOUNDS(p) (p.x >= 0 && p.x < maze_dim.x && p.y >= 0 && p.y < maze_dim.y)
#define DEREF(maze, point) maze[point.y][point.x]

const char* get_block(Block b)
{
    switch (b) {
    case BLOCK_EMPTY:   return COLOR_WHITE_;
    case BLOCK_WALL:    return COLOR_BLACK_;
    case BLOCK_START:   return COLOR_RED___;
    case BLOCK_END:     return COLOR_GREEN_;
    case BLOCK_FILL:    return COLOR_BLUE__;
    }
    return "";
}

bool path_is_bfs = false;
void path_draw(bool visited[MAZE_HEIGHT][MAZE_WIDTH], Point curr)
{
    printf(CLEAR_SCREEN CURSOR_RESET "%s\n\n",
        path_is_bfs ? "BFS" : "DFS");

    for (int i = 0; i < maze_dim.y; i++) {
        for (int j = 0; j < maze_dim.x; j++) {
            printf("%s%s",
                (visited[i][j] && !maze[i][j]) ? get_block(BLOCK_FILL) : get_block(maze[i][j]),
                (i == curr.y && j == curr.x) ? " x " : "   ");
        }
        printf(COLOR_RESET_ "\n");
    }

    // sleep(1);
    getc(stdin);
}

bool dfs(bool visited[MAZE_HEIGHT][MAZE_WIDTH], Point curr)
{
    if (!IN_BOUNDS(curr) || DEREF(visited, curr) || BLOCK_WALL == DEREF(maze, curr))
        return false;

    DEREF(visited, curr) = true;
    path_draw(visited, curr);
    if (DEREF(maze, curr) == BLOCK_END)
        return true;

    Point top   = (Point) { curr.x, curr.y - 1 };
    Point left  = (Point) { curr.x - 1, curr.y };
    Point down  = (Point) { curr.x, curr.y + 1 };
    Point right = (Point) { curr.x + 1, curr.y };

    return dfs(visited, top) || dfs(visited, left) || dfs(visited, down) || dfs(visited, right);
}

bool bfs(bool visited[MAZE_HEIGHT][MAZE_WIDTH], Point queue[], int rear, int front)
{
    if (rear == front)
        return false;

#define CONDITIONED_ENQUE(p)                                                  \
    if (IN_BOUNDS(p) && !DEREF(visited, p) && BLOCK_WALL != DEREF(maze, p)) { \
        DEREF(visited, p) = true;                                             \
        queue[rear++]     = p;                                                \
    }

    path_draw(visited, queue[front]);
    if (DEREF(maze, queue[front]) == BLOCK_END)
        return true;

    Point top   = (Point) { queue[front].x, queue[front].y - 1 };
    Point left  = (Point) { queue[front].x - 1, queue[front].y };
    Point down  = (Point) { queue[front].x, queue[front].y + 1 };
    Point right = (Point) { queue[front].x + 1, queue[front].y };

    CONDITIONED_ENQUE(top)
    CONDITIONED_ENQUE(left)
    CONDITIONED_ENQUE(down)
    CONDITIONED_ENQUE(right)

    return bfs(visited, queue, rear, front + 1);
}

int prac_1_main(Arena* arena, String_View file)
{
    (void)arena;
    Point start = { 0 };
    Point end   = { 0 };

    SV_SCAN(file, 2, "%d %d", &maze_dim.x, &maze_dim.y);
    SV_SCAN(file, 2, "%d %d", &start.x, &start.y);
    SV_SCAN(file, 2, "%d %d", &end.x, &end.y);

    assert(maze_dim.x <= MAZE_WIDTH);
    assert(maze_dim.y <= MAZE_HEIGHT);

    for (int i = 0; i < maze_dim.y; i++) {
        for (int j = 0; j < maze_dim.x; j++) {
            SV_SCAN(file, 1, "%d", (int*)&maze[i][j]);
        }
    }

    DEREF(maze, start) = BLOCK_START;
    DEREF(maze, end)   = BLOCK_END;

    {     // DFS
        bool visited[MAZE_HEIGHT][MAZE_WIDTH] = { 0 };

        (void)dfs(visited, start);
    }

    {     // BFS
        bool visited[MAZE_HEIGHT][MAZE_WIDTH] = { 0 };
        Point queue[MAZE_HEIGHT * MAZE_WIDTH] = { 0 };

        path_is_bfs                           = true;
        DEREF(visited, start)                 = true;
        queue[0]                              = start;

        (void)bfs(visited, queue, 1, 0);
    }

    return 0;
}
