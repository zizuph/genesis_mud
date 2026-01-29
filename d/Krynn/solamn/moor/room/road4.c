/* created by Aridor 09/14/93 
 Modified by Mirandus to add exit to newbie zone 09/24/15*/

#include "../local.h"

inherit ROOM_BASE

#define GULLY "/d/Krynn/solamn/pal_gully/rooms/"

void
create_moor_room()
{
    set_short("In the Canyon");
    set_long(BS("You are at the end of a small canyon, leading west "
         +   "and ending to the east, where the road slopes to the "
         +   "top of the ridge. There is a small path leading west "
		 +   "towards a cavern and a mine.",SL));
		 
	add_item(({"mine", "mines", "abandoned mine"}), "You can barely "
    +"see the mines from here. They appear like "
    +"little humps in the distance.\n");
    add_item(({"cave", "caverns", "well-kept caverns", "well-kept caves", 
    "old cavern"}), "You can barely see the "
    +"caverns from here. They look more like a bump "
    +"in the distance.\n");
	add_item(({"brush", "overgrown path", "path", "growth"}), "The path "
	+"has cleared up becoming much more open and rather easy to traverse.\n");	
	add_item(({"grass", "grasses", "pleasant grass", "pleasant grasses"}),
    "The tree lined part of the path is behind you and you've walked out "
    +"into the open space of the moors. The grass of the moor is knee "
    +"high and there are various varieties.\n");
    add_item(({"trees", "tree"}), "Behind you are the tree which provided "
	+"shade for you as you walked through along the path. Now you are in "
	+"the openness of the moors.\n");

    add_exit(ROOM + "road3","east",0,1);
    add_exit(GULLY + "np4", "west", 0, 0);

}


/*int
blocked()
{
    write(BS("The canyon comes to a dead stop here. An avalanche has "
      +   "destroyed the road to the west, and someone has put up "
      +   "a sign:  DANGER  - Avalanche. Until the road has been "
      +   "cleared and repaired, it is impossible to continue in "
      +   "this direction.",SL));
    return 1;
}*/


