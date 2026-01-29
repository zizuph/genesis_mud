/*
 * Narrow upstairs hallway in the vampire manor
 * Louie 2006
 */  
#pragma strict_types
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>

void
create_vamp_room()
{
    set_short("narrow hallway");
    set_long("This narrow hallway is very long and plain.  "+
        "To the north it appears to lead to open air, as you can "+
        "feel a breeze and hear the sound of water.  "+
        "To the south is the hall above the entry room of the "+
        "manor.  "+
        "\n");

    add_exit("upperhall1.c", "south");
    add_exit("balcony.c", "north");

    add_item(({"south","hall"}),
        "To the south is the hall above the entry room of the manor.\n");

    add_item(({"north","balcony","outside"}),
        "To the north appears to be a balcony in the open air.\n");
    
    add_item(({"hallway"}),
        "The hallway you are standing in is quite long, with nothing "+
        "in it.\n");
}
