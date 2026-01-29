/* File         : /d/Khalakhor/se_speir/rannoch/village/pub_kitchen.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-29      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     : Mostly borrowed from Khail's Macdunn pub kitchen
 * Modifications:  
 */
#pragma strict_types

#include "room.h"
#include <stdproperties.h>

inherit "/d/Khalakhor/std/room";

public void
create_khalakhor_room()
{
    set_short("the kitchen of the Walkway Pub");
    set_long("This is the kitchen of the Walkway Pub. " +
        "It's built quite similarly to the main room " +
        "itself, with the same wooden walls and low ceiling. " +
        "In the center of the room, a large wooden table " +
        "is covered in an assortment of pots, pans, spices, " +
        "and various cooking utensils. A couple of iron stoves " +
        "stand against one wall, and an open fireplace " +
        "sports a large spit for open-flame roasting.\n");

    add_prop(ROOM_I_INSIDE ,1);

    add_exit(ROOM + "pub.c", "east");
}

