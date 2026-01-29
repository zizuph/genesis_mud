/* 	forest3.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

void
create_room()
{
    set_short("Deep in a green forest");
    set_long("\n"+
             "In a forest.\n"+
             "The trees are older and significantly larger here. You think you\n"+
             "know which way to go but something has you a little disoriented.\n"+
             "");

    add_exit(THIS_DIR + "forest4","south");
    add_exit(THIS_DIR + "forest2","east");

    add_item(({"forest","trees" }),
             "The trees seem a little odd. They are definitely larger than\n"+
             "normal. The thick foliage plays tricks with the light and suddenly\n"+
             "it is not all that easy to see what is north and south. Yet there\n"+
             "is something else. You actually have a faint feeling of unease...\n"+
             "");
    add_item(({"foliage" }),
             "It looks normal but... Strange.\n"+
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
