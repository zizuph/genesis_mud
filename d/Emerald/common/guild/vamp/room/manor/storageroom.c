/*
 * Storage room in the vampire manor
 * Louie 2006
 */  
#pragma strict_types
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>

void
create_vamp_room()
{
    set_short("empty storage room");
    set_long("This large room was once used to store a multitude "+
        "of food to be used in the kitchen northeast of here.  "+
        "It is now completely empty, with dozens of bare shelves "+
        "lining the walls.  "+
        "The entry hall of the manor lies to the west.  "+
        "\n");

    add_exit("entry.c", "west");
    add_exit("kitchen.c", "northeast");

    add_item(({"shelf","shelves","bare shelf","bare shelves",
        "walls","wall"}),
        "The shelves lining the walls of this room are completely "+
        "empty, yet strangely free of any dust or decay.\n");

    add_item(({"northeast","ne","kitchen"}),
        "The kitchen lies to the northeast.\n");

    add_item(({"west","hall","entry hall"}),
        "The entry hall of the manor lies to the west.\n");


}