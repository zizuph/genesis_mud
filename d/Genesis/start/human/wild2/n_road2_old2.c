/*      n_road2.c                       Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include "wild.h"



void
create_room()
{
    set_short("Dark road");
    set_long("\n"+
             "You're walking along a dark road. A little to the north"+
             " the land opens up considerably. Southeast across the stream lies Sparkle."+
             " To the west you see a low mountain range.\n"+
             "");

    add_exit(THIS_DIR + "n_road2a","north");
    add_exit(THIS_DIR + "n_road1","south");
    add_exit("/d/Sparkle/guilds/mercs/room/start", "east");

    add_item(({"mountains","mountain range","range","road","stream" }),
             "");
    add_item(({"bridge" }),
             "It seems to be very old.\n"+
             "");
    add_item(({"sparkle","Sparkle","village" }),
             "Sparkle is a small human village by the shore of Pensea.\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}


