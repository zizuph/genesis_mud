/*
 * MAIN5.c
 * Main intersection in the middle of caverns.
 * - Alaron January 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
  object door;
  set_short("Central Hall");
  set_long("   You stand in an enormous intersection of hundreds "+
	   "of interlocking tunnels and passages. The intersection "+
	   "is dimly lit by an enormous torch hanging from one of the "+
	   "cave walls at another intersection to the north. This area "+
	   "shows signs of heavy traffic. The floor has smoothed grooves "+
	   "in it where large, wheel-drawn equipment may get pulled through "+
	   "here frequently. A larger, more noticeable tunnel branches "+
	   "off to the west, as well as two to the north and "+
	   "south. The rest of the branching tunnels and passages are "+
	   "the size of small animals and too small for you to enter.\n\n");

  add_item( ({"torch", "large torch", "north"}),
	    "The large torch to the north looks more like a tree "+
	    "stump than a torch. It is drenched in tar and looks "+
	    "like it will last quite a bit longer.\n");

  add_exit(THIS_DIR + "main6", "north");
  add_exit(THIS_DIR + "main4", "south");
  add_exit(THIS_DIR + "loop1", "east");

  
  add_item(({"symbol","symbol on door","door symbol"}),
	   "The symbol looks like this...\n"+
	   "                             \n"+
	   "                             \n"+
	   "           *     *           \n"+
	   "         *         *         \n"+
	   "        **         **        \n"+
	   "        **    *    **        \n"+
	   "        *  *     *  *        \n"+
	   "         *         *         \n"+
	   "          *       *          \n"+
	   "         / *     * \\         \n"+
	   "        /__ *   * __\\        \n"+
	   "             * *             \n"+
	   "              *              \n");                        
  
/*
  door = clone_object(THIS_DIR+"obj/door_b.c");
  door ->move(TO);
*/
}






