

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_room()
{
    set_short("Old postal chamber");
    set_long("You have entered a small alcove here in the "+
        "temple. The grass is very short here, just barely "+
        "colouring the ground green. There are several small "+
        "booths along the southern wall. There is a skylight of sorts "+
        "in the ceiling through which you can see the bright sun "+
        "above you. This appears to have been a postal chamber "+
        "of sorts, no longer in active use. To the east you see a "+
        "chamber with some beds in it.\n");

    add_item(({"booth","booths"}),"The booths are seperated by "+
        "smooth rocks.\n");

    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_M_NO_ATTACK,1);

    add_exit(ELEMENTALIST_TEMPLE+"olds_chamber","northeast",0,1);
    add_exit(ELEMENTALIST_TEMPLE+"oldstartroom","east",0,1);
}
