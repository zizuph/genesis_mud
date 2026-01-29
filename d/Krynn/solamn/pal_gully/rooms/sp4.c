/* 
 * sp1.c, Road leading to Dewar Gully from Palanthas
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_CONNECT_BASE;

/*
 * Function name: reset_pal_connecting_room
 * Description  : Resets the room
 */
void
reset_pal_connecting_room()
{
	
}

/*
 * Function name: create_pal_connecting_room
 * Description  : Constructor, redefine this to configure your room
 */
void 
create_pal_connecting_room()
{
    set_short("overgrown path");
    set_long("Further away from the city now the path begins to take you "
	+"into the moors of Palanthas. The overgrowth begins to change into "
	+"pleasant grasses and the trees are left behind bringing you into "
	+"the open air. In the distance you think you see a mine and "
	+"some caverns.\n");
	
    add_item(({"mine", "mines", "abandoned mine"}), "You can barely "
    +"see the mines from here. They appear like "
    +"little humps in the distance.\n");
    add_item(({"cave", "caverns", "well-kept caverns", "well-kept caves", 
    "old cavern"}), "You can barely see the "
    +"caverns from here. They look more like a hump "
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
        
    add_exit(RDIR + "sp3","northeast",0);
	add_exit(RDIR + "sp5","southwest",0);
    reset_pal_connecting_room();
    
}