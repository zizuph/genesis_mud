/*
 * villa1/living.c
 *
 * Lilith - Feb 2022
 *
 */
#pragma strict_types

#include "villa1.h"
#include <stdproperties.h>

inherit V1 +"housebase";

#include <composite.h>

#define SEE_NORTH	({ V1 + "terrace_c", V1 + "pool" })
#define SEE_SOUTH	({ V1 + "front_hall" })

public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";

    return " where you can see "+
    COMPOSITE_LIVE(live) + ",";
}

public string
south_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";

    return ", where "+
    COMPOSITE_LIVE(live) + " is standing by a table";
}


/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */
void 
create_house_room()
{
    add_exit("front_hall", "south");
    add_exit("terrace_c", "north");

    room_add_object(HOBJ +"table_v1_living");
    room_add_object(HOBJ +"couch_v1_e");
    room_add_object(HOBJ +"couch_v1_w");

    set_short("lounging area");
    set_long(
      "This is a sheltered lounging area on the terrace of one "+ 
      "of the private villas overlooking the Sea of Sybarus. "+
      "Wooden beams form a flat roof ideal for the wisteria vine "+ 
      "that twines through the timbers and waves its feathery "+ 
      "leaves in the breeze. "+	
      "Two couches piled with cushions sit opposite each other, "+
      "and between them is a low table. "+
      "North is a terrace and a pool,@@north_view@@ while "+ 
      "south is the front hall of the villa@@south_view@@. "+	
      "The air is refreshing and scented with flowers and salt-tang.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_help_topic("here",  "/d/Avenir/houses/help/living_help");
    add_help_topic("room",  "/d/Avenir/houses/help/living_help"); 

    set_items_living();
    set_items_stone();
    set_items_outdoor();

    add_item(({"roof", "beams", "timbers", "structure", "up"}),
      "Wooden beams stretch between the east and west wings of the "+
      "villa, creating a sheltered space. A wisteria vine has twined "+
      "around the beams.\n");
    add_item(({"wisteria", "vine", "vines", "feathery leaves", "flowers"}),
      "Twining along the beams that shelter the space between the two "+
      "wings of the villa is an ancient wisteria with white flowers "+
      "that lend a subtle scent to the air.\n");	
    add_item(({"cushions", "cushion"}), 
      "There are emerald satin cushions on the east "+		
      "couch and azure silk cushions on the west one.\n");  
    add_item(({"living area", "lounging area"}),
      "This is the lounging area of the villa. There are some "+
      "couches here, and a table.\n");
    add_item(({"east"}), "A white onyx wall.\n");
    add_item(({"west"}), "A white onyx wall.\n");
    add_item(({"north"}), "You see the sea of Sybarus and some of "+
      "the islands.\n");
    add_item(({"south"}), "The front hall is there.\n");


    start_room_tells();			
    add_tell("The wisteria flowers overhead rustle in the breeze.\n");
}

