/* Maze to the guild by Lord Rastlin */
/* modified to inherit the base file by Aridor, 09/94 */

#include "local.h"

inherit MAZE_BASE;

void
create_maze()
{
    add_exit(TDIR + "maze2", "north");
    add_exit(TDIR + "maze3", "south");
    add_exit(TDIR + "maze2", "east");
    add_exit(TDIR + "maze1", "west");
}
