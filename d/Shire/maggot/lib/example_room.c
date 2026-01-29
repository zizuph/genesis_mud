/* Example room using base_example.c
 */

#include "/d/Shire/sys/defs.h"  // domain definitions. Always include
#include "defs.h" // definitions for area. include in area files
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Shire/maggot/lib/base_example.c";

/* create_road_room() defined in base_example. Now we use it here
 * to use all the room definitions in that file.
 */
public void
create_road_room()
{
/*
 * we can change these for this room
 */
    areadesc = "green field"; // eg "green, grassy field", "dense thicket"
    area = "alongside";  // eg "northern", "next to", "west of"
    areaname = "the Brandywine river"; // eg "the bridge", "the field", "Bree"
    land = "Eriador"; // eg "Shire", "Trollshaws"
    areatype = 3; // what type of area it is. This time it's 'trees'
/* short description will be this:
 * A green field with some trees alongside the Brandywine river in Eriador.
 */

    extraline = "The land is trampled by many travellers who have gone " +
        "this way.";
/* 
 * Long description:
 * A green field with some trees alongside the Brandywine river in 
 * Eriador. The light of day shines across the Brandywine river. It 
 * is afternoon. The land is trampled by many travellers who have gone 
 * this way.
 */

/*
 * The following add_item() will be added to those already defined in
 * base_example.c
 */
    add_item(({"trees"}),
        "They are tall and grow in groves everywhere.\n");
    add_item(({"down", "ground"}),
        "The ground is trampled and covered with grass.\n");
    add_item(({"grass"}),
        "It is green and has been trampled by many travellers.\n");

/*
 * Will add this room tell to the default ones defined in base_excample
 */
    add_room_tell("The leaves move in the wind.");
/*
 * Adds an exit to the room. This one won't work though.
 */
    add_exit("pathname", "direction");
/*
 * makes the room reset periodically
 */
    reset_shire_room();
}


void
init()
{   
/*
 * Used to initilaize some functions. Not needed, but nice to have in
 * each room.
 */
    ::init();
}


void
reset_shire_room()
{
/*
 * Put routines in here that you want executed each time room 
 * resets, like npcs cloned, reset specific variables, etc.
 */

}
