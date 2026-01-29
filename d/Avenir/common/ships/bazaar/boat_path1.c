/*
 * Filename: /d/Avenir/common/ships/bazaar/boat_path1.c
 * Original creator: Kazz on Feb 1995
 * Purpose: leads from outpost to beach with boat
 * Last update(s):
 *    Manat on Jul 2000 - changed coding style and stuff
 *                        moved #include below inherit
 * Known bug(s):
 * To-do:
 */
#pragma save_binary
#pragma strict_types
/* added strict_types check because you always want it! Manat on Jul 2000 */

inherit "/std/room";
inherit "/d/Avenir/inherit/sair_wall";

#include "/d/Avenir/common/common.h"
/* #include "/d/Avenir/common/outpost/outpost.h"
 * It's only included to use the SHORT and LONG defines...
 * and that's really not needed. Manat on Jul 2000
 */
#include <terrain.h>

#define OUTPOSTBOAT "/d/Avenir/common/ships/bazaar/"

/*
 * Function name: create_room
 * Description  : This is the creator of the room.
 * Changes      : Added return type and removed SHORT and LONG.
 *                added set_terrain.
 */
public void
create_room()
{
    /* room description */
    set_short("Short tunnel");
    set_long( "You are in a very short tunnel in the cavern rock. The " +
              "tunnel opens up almost immediately to the northeast, " +
              "leading to a sandy beach and the edge of water. The " +
              "white glowing light is stronger in that direction. You " +
              "can enter the fort to the southwest.\n" );

    /* room exits */
    add_exit(OUTPOSTBOAT + "boat_path2", "northeast");
    add_exit(OUTPOST + "fort7", "southwest");

    /* room settings */
    LIGHT
	IN
    IN_IN
    set_terrain(TERRAIN_ROCK|TERRAIN_WARM|TERRAIN_SHADOWS|
                TERRAIN_UNDERGROUND);

    /* room items */
    add_item( ({ "tunnel", "cavern", "cavern rock" }),
             "The cavern rock is rather non-descript.\n" );
    add_item( ({ "beach", "sandy beach" }),
             "The beach is on the edge of the calm water.\n" );
    add_item( ({ "light", "white light", "glowing light" }),
             "The light is much brighter to the northeast.\n" );
    add_item( "water",
             "The water seems to be part of a large body of water.\n" );
			 
	add_sair_wall();
    set_sair_dest(({DEAD+ "path/landing", DARK+"l2/add/t36"}));
    add_item(({"wall"}), "The wall of the cavern extends as far as the "
		    +"eye can see.\n");		 
}
public void
init()
{
    ::init();
    sair_init();  
}
