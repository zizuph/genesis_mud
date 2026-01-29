/* 	peninsula.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("At the peninsula");
    set_long("\n"+
             "Out on a peninsula.\n"+
             "The view is very good from here and the fresh sea wind is quite\n"+
             "enjoyable. The peninsula extends a little further east out towards\n"+
             "the sea but the hillside is too steep to descend safely.\n"+
             "");

    add_exit ("moor3","west");

    add_item(({"peninsula","sea","hillside" }), "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

