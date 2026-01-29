/* 	field8.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("A large field");
    set_long("\n"+
             "West end of a large field.\n"+
             "The ground is damp and muddy. To your east is a small pond but the soft\n"+
             "and swampy ground doesn't allow you to go that way. Access to the north \n"+
             "is cut off by a stream leading north to a waterfall. A path is leading\n"+
             "west from here into a narrow valley.\n"+
             "");

    add_exit("big_tree","west");
    add_exit("field4","south");

    add_item(({"ground","mud" }),
             "The ground is very muddy due to the nearby pond.\n"+
             "");
    add_item(({"pond" }),
             "A very nice little pond. With a few ducks it would be perfect.\n"+
             "");
    add_item(({"stream" }),
             "Oh it is too wide to jump. Maybe you can find a bridge.\n"+
             "");
    add_item(({"path" }),
             "");
    add_item(({"waterfall","valley" }),
             "You have to get closer to see any details.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
