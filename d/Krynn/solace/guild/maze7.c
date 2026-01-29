/* Maze to the guild by Lord Rastlin */
/* modified to inherit the base file by Aridor, 09/94 */

#include "guild.h"
#include "local.h"

inherit MAZE_BASE;

void
create_maze() 
{
  add_exit(TDIR + "maze6", "north");
  add_exit(ENTRANCE, "south");
  add_exit(TDIR + "maze7", "east");
  add_exit(TDIR + "maze5", "west");
}
