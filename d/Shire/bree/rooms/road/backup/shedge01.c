/*
 * Hedge outside of Bree
 * By Finwe, June  2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit ROAD_BASE;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "n";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }
 
void
create_road_room()
{
//    set_areadesc("small");
//    set_area("path");
//    set_areaname("outside the hedge");
//    set_land("Bree");

    add_my_desc("You are on a path that runs between a dike to " +
        "your east and a hedge to the west. The hedge is tall, " +
        "blocking your view.\n");

    set_add_hedge_road();
    set_add_bushes();
    set_add_dike();

    add_exit(ROAD_DIR + "wgate", "north", "@@tree_north@@");
    add_exit(ROAD_DIR + "shedge02", "south", "@@tree_south@@");

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

void tree_north()
{
    tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) +" heads north to Bree.\n");
}

void tree_south()
{
    tell_room("/d/Shire/bree/rooms/road/treetop_fort.c", QCTNAME(TP) +" heads south along the hedge outside Bree.\n");
}