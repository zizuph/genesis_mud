/* 	field11.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"
#include S_DOMAIN_SYS_LINKS

void
create_room()
{
    set_short("A large field");
    set_long("\n"+
             "Dark road.\n"+
             "The mountains rise high like a wall to the north and a deep\n"+
             "crevice stops you from going east. You notice a small rift that\n"+
             "lets you pass to the north.\n");

    add_exit("field10","west",0, 0);
    add_exit("field7","south",0, 0);
    add_exit(S_LINK_DWARFHEIM_ROAD,"north",0);
    add_item(({"mountains","road","rift" }),
             "");
    add_item(({"crevice" }),
             "Better be careful. It's a long way down...\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

