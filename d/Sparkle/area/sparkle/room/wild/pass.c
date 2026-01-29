/* 	pass.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Mountain pass");
    set_long("\n"+
             "Dark road.\n"+
             "You move down the middle of a high narrow mountain pass.\n"+
             "The sounds of your passing echoes off the walls amplifying the sound to\n"+
             "a roar. This is a perfect place for an ambush. If anyone would like to\n"+
             "hit you, now is the time. The road continues north through the pass\n"+
             "and south onto a field.\n"+
             "");

    add_exit ("field9","south");

    add_item(({"road","field" }),
             "");
    add_item(({"mountain pass","pass","walls" }),
             "The walls rise several hundred metres on both sides of the pass\n"+
             "and the distance between them is seldom more than 5 - 10 metres.\n"+
             "Even a giant would feel small in here.\n"+
             "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

