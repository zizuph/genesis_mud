/* Vladimir 8-09-94 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

void reset_room();

object orc, orc1, orc2;

void
create_room()
{
    set_short("Orc guardroom");
    set_long(
        "This is a crudely built room that is carved from stone that\n"
        + "lies around the fortress. There are four holes in the wall that\n"
        + "you think are supposed to be arrow slits that vary in levels. In\n"
        + "the middle of this dank room sits a small stone table.\n");
    add_item(({"slits", "arrow slits", "holes"}),
             break_string("These slits are spread at various levels along "+
                          "three of the four walls.\n", 70));

    add_item(({"table", "stone table", "small table", "small stone table"}),
             break_string("This is a small stone table. It has a very rough "+
                          "surface and seems uneven.\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("hall3", "south");
    reset_room();
}

void
reset_room()
{
    if(!orc)
    {
        orc = clone_object(S_LOCAL_NPC_DIR + "orc1");
        orc->arm_me();
        orc->move_living("xxx", TO);
    }
    if(!orc1)
    {
        orc1 = clone_object(S_LOCAL_NPC_DIR + "orc");
        orc1->arm_me();
        orc1->move_living("xxx", TO);
    }
    if(!orc2)
    {
        orc2 = clone_object(S_LOCAL_NPC_DIR + "orc");
        orc2->arm_me();
        orc2->move_living("xxx", TO);
    }
}

