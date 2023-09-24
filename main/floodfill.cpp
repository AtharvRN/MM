#include "robot_moves.h"
#include "Queue.h"

const short size_x = 10, size_y = 10;
const short tx = 5, ty = 5;
const short max_size = 15;

#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_DOWN 2
#define DIR_LEFT 3

#define abs(x) ((x) < 0 ? -(x) : (x))
#define max(x, y) ((x) > (y) ? (x) : (y))

class pair {
    public:
        short first, second;
        pair() {}
        pair(short f, short s) {
            first = f;
            second = s;
        }
};

class grid_struct {
    public:
        bool wall_down[max_size][max_size] = {0};
        bool wall_left[max_size][max_size] = {0};
        short grid[max_size][max_size];
        short cx, cy, cdir;

        grid_struct(short x, short y, short d) {
            for (short i = 0; i < size_x; i++) {
                wall_down[i][size_y] = true;
            }
            for (short i = 0; i < size_y; i++) {
                wall_left[size_x][i] = true;
            }
            cx = x;
            cy = y;
            cdir = d;
            update_grid();
        }

        void add_wall(short x, short y, short dir) {
            if (dir == DIR_DOWN) {
                wall_down[x][y] = true;
            } else if (dir == DIR_LEFT) {
                wall_left[x][y] = true;
            } else if (dir == DIR_RIGHT) {
                wall_left[x+1][y] = true;
            } else if (dir == DIR_UP) {
                wall_down[x][y+1] = true;
            }
            update_grid();
        }

        bool check_wall(short x, short y, short dir) {
            if (dir == DIR_DOWN) {
                return wall_down[x][y];
            } else if (dir == DIR_LEFT) {
                return wall_left[x][y];
            } else if (dir == DIR_RIGHT) {
                return wall_left[x+1][y];
            } else if (dir == DIR_UP) {
                return wall_down[x][y+1];
            } else {
                // unreachable
                return false;
            }
        }

        void update_grid() {
            for (short i = 0; i < size_x; i++) {
                for (short j = 0; j < size_y; j++) {
                    grid[i][j] = -1;
                }
            }
            grid[tx][ty] = 0;
            Queue<pair> q(4 * max(size_x, size_y) + 1);
            q.push({tx, ty});
            while (q.count()) {
                pair p = q.pop();
                short x = p.first, y = p.second;
                if (!check_wall(x, y, DIR_UP) && grid[x][y+1] == -1) {
                    grid[x][y+1] = grid[x][y] + 1;
                    q.push(pair(x, y+1));
                }
                if (!check_wall(x, y, DIR_RIGHT) && grid[x+1][y] == -1) {
                    grid[x+1][y] = grid[x][y] + 1;
                    q.push(pair(x+1, y));
                }
                if (!check_wall(x, y, DIR_DOWN) && grid[x][y-1] == -1) {
                    grid[x][y-1] = grid[x][y] + 1;
                    q.push(pair(x, y-1));
                }
                if (!check_wall(x, y, DIR_LEFT) && grid[x-1][y] == -1) {
                    grid[x-1][y] = grid[x][y] + 1;
                    q.push(pair(x-1, y));
                }
            }
        }

        void update_walls() {
            short front_dir = cdir;
            short left_dir = (cdir + 3) % 4;
            short right_dir = (cdir + 1) % 4;
            if (wallFront()) {
                add_wall(cx, cy, front_dir);
            }
            if (wallLeft()) {
                add_wall(cx, cy, left_dir);
            }
            if (wallRight()) {
                add_wall(cx, cy, right_dir);
            }
        }

        void flood_fill_step() {
            update_walls();
            short dir_to_move = -1;
            for (short i = 0; i < 4; i++) {
                short dir = (cdir + i) % 4;
                short nx = cx + (dir == DIR_LEFT) - (dir == DIR_RIGHT);
                short ny = cy + (dir == DIR_UP) - (dir == DIR_DOWN);
                if (!check_wall(cx, cy, dir) && grid[nx][ny] < grid[cx][cy]) {
                    dir_to_move = dir;
                    break;
                }
            }
            if (dir_to_move == -1) {
                return;
            }
            short rots = (dir_to_move - cdir + 4) % 4;
            if (rots == 1) {
                turnRight();
            } else if (rots == 2) {
                turnRight();
                turnRight();
            } else if (rots == 3) {
                turnLeft();
            }
            moveForward();
        }

        void flood_fill() {
            while (cx != tx || cy != ty) {
                flood_fill_step();
            }
        }
};

void gotoTarget(short cx, short cy, short cdir) {
    grid_struct g(cx, cy, cdir);
    g.flood_fill();
}