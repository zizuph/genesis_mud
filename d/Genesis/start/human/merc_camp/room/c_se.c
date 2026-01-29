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
#include <filter_funs.h>
#include "room.h"

object guard1, guard2, guard3;

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

}

int check_pass()
{
    object *guards = filter(FILTER_LIVE(all_inventory(this_object())),
	&->id("_mercenary_renegade_"));

    if (!sizeof(guards) || !CAN_SEE(guards[0], TP))
	return 0;

    if (!TP->query_prop(PLAYER_I_ATTACK_MERC_CAMP))
        return 0;

    write("The "+guards[0]->short()+" blocks your way as you attempt to pass.\n");
    say("The "+guards[0]->short()+" blocks "+QTNAME(TP)+"'s way as "+PRONOUN(TP)+
	" attempts to pass.\n");
    return 1;
}

public void
create_room()
{
    set_short("Just Outside Camp Center");
    set_long(OUTSIDE_DESC+OUT_TENT_DESC+CENTER_DESC_SE);
    add_item(({"tent", "tents"}), "Tents surround the center of the camp.\n");
    add_exit(MERC_CAMP_ROOM + "center.c", "northwest", "@@check_pass", 1, 0);
    add_exit(MERC_CAMP_ROOM + "c_se_e.c", "east", 0, 1, 0);
    add_exit(MERC_CAMP_ROOM + "c_se_s.c", "south", 0, 1, 0);
    reset_room();
}

