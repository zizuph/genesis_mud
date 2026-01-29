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

object guard1, guard2, guard3, guard4, campfire;

public void
reset_room()
{
    if (!campfire)
    {
	campfire = clone_object(MOBJ + "firewood");
	campfire->set_burn_time(36000);
	campfire->move(this_object());
    }

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

int enter_tent()
{
    object *guards = filter(FILTER_LIVE(all_inventory(this_object())),
	&->id("_mercenary_renegade_"));

    if (!sizeof(guards) || !CAN_SEE(guards[0], TP))
    {
	write(TENT_ENTER);
	return 0;
    }

    if (!TP->query_prop(PLAYER_I_ATTACK_MERC_CAMP))
    {
	write(TENT_ENTER);
        return 0;
    }

    write("The "+guards[0]->short()+" blocks your way as you attempt to pass.\n");
    say("The "+guards[0]->short()+" blocks "+QTNAME(TP)+"'s way as "+PRONOUN(TP)+
	" attempts to pass.\n");
    return 1;

}

public void
create_room()
{
    set_short("Center of Camp");
    set_long(OUTSIDE_DESC+
	"Paths converge here in the center of the camp, entering tents "+
	"to the north, east, south, and west. The entrance to the camp "+
	"is back to the south a ways.\n");
    add_item(({"tent", "tents"}), OUT_TENT_DESC);
    add_item(({"path", "paths"}), "Many paths converge here, heading in "+
	"all directions.\n");
    add_exit(MERC_CAMP_ROOM + "tent_n.c", "north", "@@enter_tent", 1, 0);
    add_exit(MERC_CAMP_ROOM + "tent_w.c", "west", "@@enter_tent", 1, 0);
    add_exit(MERC_CAMP_ROOM + "tent_e.c", "east", "@@enter_tent", 1, 0);
    add_exit(MERC_CAMP_ROOM + "tent_s.c", "south", "@@enter_tent", 1, 0);
    add_exit(MERC_CAMP_ROOM + "c_nw.c", "northwest", 0, 1, 0);
    add_exit(MERC_CAMP_ROOM + "c_sw.c", "southwest", 0, 1, 0);
    add_exit(MERC_CAMP_ROOM + "c_ne.c", "northeast", 0, 1, 0);
    add_exit(MERC_CAMP_ROOM + "c_se.c", "southeast", 0, 1, 0);
    reset_room();

    guard2->command("light campfire");
}

public void
campfire_is_gone(object ob)
{
    tell_room(this_object(), "As "+QTNAME(ob)+" enters, "+PRONOUN(ob)+
	" stares in bewilderment at the empty area in the room where "+
	"a campfire should be burning. Shrugging to "+OBJECTIVE(ob)+
	"self, "+PRONOUN(ob)+" gathers enough wood for another campfire.\n", ob);
    campfire = clone_object(MOBJ + "firewood");
    campfire->set_burn_time(7200);
    campfire->move(this_object());
    ob->command("light campfire");
}

public void
campfire_is_ashes(object ob)
{
    tell_room(this_object(), "As "+QTNAME(ob)+" enters, "+PRONOUN(ob)+
        " notices the fire has gone out, and gathers enough wood for "+
	"another campfire.\n", ob);
    campfire->remove_object();
    campfire = clone_object(MOBJ + "firewood");
    campfire->set_burn_time(7200);
    campfire->move(this_object());
    ob->command("light campfire");
}

public void
campfire_is_low(object ob)
{
    tell_room(this_object(), "As "+QTNAME(ob)+" enters, "+PRONOUN(ob)+
        " notices the fire beginning to burn low and gathers some wood to "+
	"keep it burning.\n", ob);
    campfire->add_burn_time(1800);
}

public void
campfire_not_lit(object ob)
{
    tell_room(this_object(), "As "+QTNAME(ob)+" enters, "+PRONOUN(ob)+
        " notices the campfire is not lit.\n", ob);
    ob->command("light campfire");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (campfire->query_burn_time() <= 5 && campfire->query_lit() == 0 &&
	ob->id("_mercenary_renegade_"))
    {
        set_alarm(2.0, 0.0, "campfire_is_ashes", ob);
	return;
    }

    if (campfire->query_burn_time() < 3600 && ob->id("_mercenary_renegade_"))
    {
        set_alarm(2.0, 0.0, "campfire_is_low", ob);
	return;
    }

    if ((!campfire || environment(campfire) != this_object()) &&
	ob->id("_mercenary_renegade_"))
    {
        set_alarm(2.0,0.0, "campfire_is_gone", ob);
	return;
    }

    if (campfire->query_lit() == 0 && ob->id("_mercenary_renegade_"))
    {
	set_alarm(1.0, 0.0, "campfire_not_lit", ob);
	return;
    }
}
