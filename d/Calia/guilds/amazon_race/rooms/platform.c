/*
 *    platform.c  
 *
 * On a big wooden platform.
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */

inherit "/std/room.c";
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

int
block_exit()
{
   write("That way is currently under construction, come back another day.\n");
   return 1; 
}

void
create_room()
{
    set_short("On a big wooden platform");
    set_long("You have arrived at a big wooden platform, stationed "+
      "high up in one of the larger trees. Several rope bridges "+
      "connects it with other smaller platforms and treehouses.\n");
      
    add_exit(ROOMS + "bridge","northwest");
    add_exit(ROOMS + "info","north");
    add_exit(ROOMS + "message","west");
    add_exit(ROOMS + "a","northeast", &block_exit());
    add_exit(ROOMS + "a","east", &block_exit());
    add_exit(ROOMS + "a","south", &block_exit());
    add_exit(CONNECTING_ROOM,"down");
}
