/*
 * Filename: /d/Avenir/common/ships/bazaar/boat_path2.c
 * Original creator: Kazz on Apr 1995
 * Purpose: The first lake-level view of the Lake.
 *          Beach 'dock' for the boat to the Park.
 * Last update(s):
 *    Kazz on May 1995    - added do_call_boat
 *    Boriska on Sep 1995 - Changes in bazaar ship project
 *    Denis on May 1996   - Removed this_object();
 *    Manat on Jul 2000   - changed coding style and stuff
 *                          moved #include below inherit
 *    Lilith,  Sep 2021   - added prop for fishermen club
 * Known bug(s):
 * To-do:
 */
#pragma save_binary
#pragma strict_types
/* added strict_types check because you always want it! Manat on Jul 2000 */

inherit "/std/room";
inherit "/d/Avenir/common/ships/bazaar/pipe.c";
inherit "/d/Avenir/inherit/sair_wall";

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/include/relation.h"
 /* #include "/d/Avenir/common/outpost/outpost.h"
  * these things doesn't seem to be used */
#include "/d/Avenir/common/ships/bazaar/ship.h"
 /* #include "/sys/ss_types.h"
  * Is this really needed? It seem to be included from common.h .
  */
#include <terrain.h>
#define OUTPOSTBOAT "/d/Avenir/common/ships/bazaar/"

private object ship;

/*
 * Function name: init
 * Description  : Init the players command set
 * Changes      :
 */
public void
init()
{
    ::init();
    init_boat_room();
    sair_init();  
}

public void
create_room()
{
    /* room description */
    set_short("sandy beach");
    set_long("You stand on a thin sandy beach within an immense underground "+
             "cavern. A great, underground sea begins at your feet, and "+
             "stretches further to the north than you can see. The entire "+
             "great cavern is lit by strange phosphorescent veins running "+
             "through the ceiling far overhead. A short metal pipe leans "+
             "out of the calm sea.\n");

    /* room exits */  
    add_exit(OUTPOSTBOAT + "boat_path1", "southwest");

    /* room settings */
    LIGHT
    IN
    set_terrain(TERRAIN_ROCK|TERRAIN_WARM|TERRAIN_SHADOWS|
                TERRAIN_UNDERGROUND);				
    add_prop(TERRAIN_ONWATER, 1);
    add_prop(OBJ_I_CONTAIN_WATER, 1);
	add_prop(ROOM_I_TYPE, ROOM_BEACH);
	add_prop("_live_i_can_fish", ({"freshwater", "saltwater", "subterranean"}));


    /* room items */
    add_item( ({ "sea", "great sea" }),
             "The light from above does not penetrate the sea, making "+
             "it a heavy shade of black.\n" );
    add_item( ({ "light", "white light", "glowing light" }),
             "The light gives an unearthly glow to everything.\n" );
    add_item( ({ "veins", "strange veins" }),
             "The veins criss-cross the entire cavern ceiling. They "+
             "are more concentrated to the far east.\n" );
    add_item( ({ "island", "islands" }),
             "Trees and vegetation grow on the nearest islands. You can "+
             "barely discern a boat travelling between distant "+
             "islands.\n" );
    add_item( ({ "cavern", "underground cavern" }),
             "The cavern stretches farther than you can see. Strangely "+
	     "glowing veins cast light down onto the great sea and "+
	     "islands.\n" );
    add_item( ({ "beach", "sandy beach" }),
             "The beach marks the beginning of the great sea. From the "+
             "here, you can return to the tunnel and fort.\n" );
    add_item( ({ "pipe", "metal pipe" }), "@@pipe_description@@" );
    add_item( ({ "scratches", "pipe scratches" }),
             "@@pipe_scratch_description@@" );
    add_cmd_item( ({"sea", "in water", "water", "great sea", "in sea" }),
                 ({ "swim" }), "The islands are too far away to swim to.\n" );

    /* ship starts here */
    ship = clone_object(OUTPOSTBOAT + "ship");
    ship->move(this_object(),1);
    ship->start_ship();
    set_boat_start_room(this_object());
    BAZAAR_DOCK->set_boat_start_room(this_object());
	
    add_sair_wall();
    set_sair_dest(({DARK+"l2/add/t36", PORT +"port2", DARK+"l1/waters"}));
    add_item(({"wall"}), "The wall of the cavern extends as far as the "
		    +"eye can see.\n");

}

/*
 * Function name: query_ship
 * Description  : return the ship object
 * Returns      : the ship
 */
public object
query_ship()
{
    return ship;
}
