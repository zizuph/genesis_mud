/*
 * Primary Trainer for the Mercenary guild, by Morrigan 11/2001
 *
 * Adapted from code by Auberon Gwyneth on 19 February 2001
 */
inherit "/std/room";

#include "../merc.h"
#include "room.h"

object guard1, guard2, campfire;

public void
reset_room()
{
    if (!campfire)
    {
	campfire = clone_object(MOBJ + "firewood");
	campfire->set_burn_time(36000);
	campfire->move(this_object());
    }

}

int enter_building()
{
    if (IS_MERC(TP))
	write("You feel at home as you enter the Mercenary Halls.\n");
       else
        write("You enter the rustic building.\n");
}

int enter_tent()
{
    write(TENT_ENTER);
}

public void
create_room()
{
    set_short("Center of Camp");
    set_long(OUTSIDE_DESC+
	"Paths converge here in the center of the camp, entering tents "+
	"to the northwest, northeast, southwest, and southeast. A large "+
	"building fills the area to the north. The entrance to the camp "+
	"can be reached by taking the west path.\n");
    add_item("building", OUT_BUILDING_DESC);
    add_item(({"tent", "tents"}), OUT_TENT_DESC);
    add_item(({"path", "paths"}), "Many paths converge here, heading in "+
	"all directions.\n");
    add_exit(MROOM + "join.c", "north", "@@enter_building", 1, 0);
    add_exit(MROOM + "train.c", "west", 0, 1, 0);
    add_exit(MROOM + "train2.c", "east", 0, 1, 0);
    add_exit(MROOM + "train3.c", "south", 0, 1, 0);
    add_exit(MROOM + "bank.c", "northwest", "@@enter_tent", 1, 0);
    add_exit(MROOM + "inn.c", "southwest", "@@enter_tent", 1, 0);
    add_exit(MROOM + "shop.c", "northeast", "@@enter_tent", 1, 0);
    add_exit(MROOM + "smith.c", "southeast", "@@enter_tent", 1, 0);
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
	ob->id("_mercenary_guild_guard_"))
    {
        set_alarm(2.0, 0.0, "campfire_is_ashes", ob);
	return;
    }

    if (campfire->query_burn_time() < 3600 && ob->id("_mercenary_guild_guard_"))
    {
        set_alarm(2.0, 0.0, "campfire_is_low", ob);
	return;
    }

    if ((!campfire || environment(campfire) != this_object()) &&
	ob->id("_mercenary_guild_guard_"))
    {
        set_alarm(2.0,0.0, "campfire_is_gone", ob);
	return;
    }

    if (campfire->query_lit() == 0 && ob->id("_mercenary_guild_guard_"))
    {
	set_alarm(1.0, 0.0, "campfire_not_lit", ob);
	return;
    }
}
