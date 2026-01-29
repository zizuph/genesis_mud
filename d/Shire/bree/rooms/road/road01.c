/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_road_room()
{
    set_areadesc("busy");
    set_area("road");
    set_areaname("outside");
    set_land("Bree");

    add_bree_desc("The road runs east into the village of Bree. The " +
        "West Gate stands to the east. A large " +
        "hedge is visible in the distance, surrounded by a deep dike.\n");
    add_item(({"west gate", "gate"}),
        "The West Gate is sturdy looking. It stands to the east " +
        "and is opened during the day, and closed at night.\n");

    set_add_ger();
    set_add_outside_hedge();
    set_add_dike();

    add_exit(ROAD_DIR + "wgate", "east", "@@tree_east@@");
    add_exit(ROAD_DIR + "crossroad",  "west", "@@tree_west@@");
}

public void
enter_inv(object ob, object from)
{
	string *names;
	::enter_inv(ob, from);
	names = ob->query_names();
	if(ob->id(npc_name))
	{
		if (!move_alarm || !sizeof(get_alarm(move_alarm)))
		{
			move_alarm = set_alarm(50.0 + rnd() * 20.0, 0.0, &move_patrol(ob));
		}
	return;
	}
}

void tree_east()
{
//    tell_room(ROAD_DIR + "treetop.c", QCTNAME(TP) + " went east closer to Bree.\n");
    tell_tree("went east towards Bree.");
    tell_tree_fort("went east towards Bree.");
}

void tree_west()
{
//    tell_room(ROAD_DIR + "treetop.c", QCTNAME(TP) + " went west to the Crossroads.\n");
    tell_tree("went west to the Crossroads.");
    tell_tree_fort("went west to the Crossroads.");
}