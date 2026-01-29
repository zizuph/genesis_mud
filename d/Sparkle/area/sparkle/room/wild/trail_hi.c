/* 	trail_hi.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Upper part of a trail");
    set_long("\n"+
             "You are standing at the top of a long trail.\n"+
             "The trail descends steeply down the mountainside to the east.\n"+
             "Looking west you see a swirling mist forming in the air.\n"+
             "Your nose itches due to a faint smell of sulphur...\n"+
             "");

    add_exit ("geyser","west");
    add_exit ("trail_lo","east");

    add_item(({"trail","mountainside" }),
             "");
    add_item(({"mist" }),
             "It feels like water vapor and the damp air is actually quite warm here.\n"+
             "");
    add_item(({"sulphur" }),
             "You can't see any sulphur around here.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

