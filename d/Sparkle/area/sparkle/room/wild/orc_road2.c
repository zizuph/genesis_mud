/* 	orc_road2.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Orc road");
    set_long("\n"+
        "Orc road.\n"+
        "The road leads westwards into the woods and east towards the sea.\n"+
        "You are in the east end of a valley where it opens up into wider\n"+
        "areas. To your north are some low mountains and south is a steep hill.\n"+
        "");

    add_exit ("orc_road3","west");
    add_exit ("orc_road1","east");

    add_item(({"road","woods","valley","valley","hill" }),
        "");
    add_item(({"sea","Pensea","pensea" }),
        "Yes, you can see the sea. It's over there between the \n"+
        "land and the sky.\n"+
        "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

