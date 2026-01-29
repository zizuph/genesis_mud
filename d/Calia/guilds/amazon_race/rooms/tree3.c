/*
 *    tree3.c  
 *
 * Center of a camouflaged treehouse 
 * at the Amazon racial guild
 *
 * Baldacin@Genesis, Nov 2003   
 *
 */

inherit "/std/room.c";
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    set_short("At the center of a camouflaged treehouse");
    set_long("At the center of a camouflaged treehouse. This section "+
      "of the tree is quite spacious, the crown of this tree must "+
      "be huge. To the north you spot an amazon warrior, training "+
      "some of the younger women. West of here a big board has been "+
      "nailed to the branched wall and to the southwest of here you "+
      "can see some bunks.\n");

    add_item(({"treehouse","treetop","hut"}), "This fairly large treehouse "+
      "has been constructed in what seems to be one of the largest trees "+
      "in the whole forest. It can easily hold a large group of people.\n");
    add_item("bunks","They don't seem to comfortable, You would have to get "+
      "close to know for sure.\n");
    add_item(({"wall","walls"}), "The walls are made from branches, "+
      "twined together, forming a wall. In some places it has been "+
      "reinforced by some planks, making it sturdy.\n");
    add_item(({"board", "big board"}), "It is the board the Amazons "+
      "use to communicate with each other.\n");
              
    add_prop(ROOM_I_INSIDE, 1);
    add_exit(ROOMS + "tree2","north");
    add_exit(ROOMS + "tree4","west");
    add_exit(ROOMS + "tree1","southwest");
    add_exit(ROOMS + "bridge","southeast");
}
