/* 	grove.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("In a small grove");
    set_long("\n"+
             "Pine trees surround you in this little grove.\n"+
             "The valley continues east-west but a trail can be seen\n"+
             "leading off to the south.\n"+
             "");

    add_exit("giant_path","west");
    add_exit("trail_lo","south");
    add_exit("big_tree","east");

    add_item(({"trees","pine trees","tree" }),
             "");
    add_item(({"valley" }),
             "It is very rocky and the vegetation is generally sparse.\n"+
             "");
    add_item(({"trail" }),
             "Now where might that trail lead off to...\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

