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

object guard1, guard2, guard3, guard4;

public void
reset_room()
{
    if (!guard1)
    {
	guard1 = clone_object(MERC_CAMP_NPC + "merc_base");
	guard1->set_level(4);
        guard1->set_random_move(0);
	guard1->move(this_object());
    }

    if (!guard2)
    {
	guard2 = clone_object(MERC_CAMP_NPC + "merc_base");
	guard2->set_level(4);
        guard2->set_random_move(0);
	guard2->move(this_object());
    }

    if (!guard3)
    {
	guard3 = clone_object(MERC_CAMP_NPC + "merc_base");
	guard3->set_level(4);
        guard3->set_random_move(0);
	guard3->move(this_object());
    }

    if (!guard4)
    {
	guard4 = clone_object(MERC_CAMP_NPC + "merc_base");
	guard4->set_level(4);
        guard4->set_random_move(0);
	guard4->move(this_object());
    }
}

int exit_tent()
{
    write(TENT_EXIT);
}

public void
create_room()
{
    set_short("Inside a Large Tent");
    set_long(INSIDE_TENT_DESC+ " The tent is fairly large but plain, and does not "+
	"look very luxurious.\n");
    add_exit(MERC_CAMP_ROOM + "center.c", "out", "@@exit_tent", 1, 0);
    reset_room();
}

