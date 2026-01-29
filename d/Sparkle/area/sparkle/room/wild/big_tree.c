/* 	big_tree.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Under a BIG tree");
    set_long("\n"+
             "A large green oak is towering high up above you.\n"+
             "Amazed by the size of this tree you realize that is must be\n"+
             "very old. The trail continues through the valley and more trees\n"+
             "can be seen to the west.\n"+
             "");

    add_exit("grove","west");
    add_exit("field8","east");

    add_item(({"valley","trail" }),
             "");
    add_item(({"tree","oak","oak tree","green oak" }),
             "It would take at least 3 men or 15 dwarves to embrace it.\n"+
             "Something, maybe woodwork of some kind, can be seen up there\n"+
             "if you strain your eyes to see. However, the tree might be\n"+
             "difficult to climb...\n");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_cmd_item( ({ "oak", "tree" }), "climb", "@@climb" );

}

string
climb(string str)
{
    return "You don't have what it takes to do that.\n";
}

