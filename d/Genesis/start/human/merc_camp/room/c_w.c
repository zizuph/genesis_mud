/*
 * Primary Trainer for the Mercenary guild, by Morrigan 11/2001
 *
 * Adapted from code by Auberon Gwyneth on 19 February 2001
 */
inherit "/std/room";

#include "/d/Krynn/common/defs.h"
#include "../merc.h"
#include <stdproperties.h>
#include <macros.h>
#include "room.h"

object guard1, guard2;

public void
reset_room()
{
    if (!guard1)
    {
	guard1 = clone_object(MERC_CAMP_NPC + "merc_base");
	guard1->move(this_object());
    }

    if (!guard2)
    {
	guard2 = clone_object(MERC_CAMP_NPC + "merc_base");
	guard2->move(this_object());
    }

}

public void
create_room()
{
    set_short("West of Camp Center");
    set_long(OUTSIDE_DESC+OUT_TENT_DESC+CENTER_DESC_W);
    add_item(({"tent", "tents"}), "Tents surround the center of the camp.\n");
    add_exit(MERC_CAMP_ROOM + "c_w_w.c", "west", 0, 1, 0);
    add_exit(MERC_CAMP_ROOM + "c_nw_w.c", "north", 0, 1, 0);
    add_exit(MERC_CAMP_ROOM + "c_sw_w.c", "south", 0, 1, 0);
    reset_room();
}

