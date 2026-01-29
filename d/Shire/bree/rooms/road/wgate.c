/*
 * 2002/06/25 Last update
 * 2011/07/21 Lavellan - Updating to use fixed base rooms
 */

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit "/d/Shire/bree/stdgateroom.c";
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }


create_gateroom() 
{
    set_short("Western gate of Bree");
    set_other_room(ROAD_DIR + "broad01");
    set_direction("east");
    add_exit(ROAD_DIR + "nhedge01", "north", "@@tree_north@@");
    add_exit(ROAD_DIR + "shedge01", "south","@@tree_south@@");
    add_exit(ROAD_DIR + "road01", "west","@@tree_west@@");
    set_add_ger();
}

long_desc() 
{
    string str;

    if (gatestate) 
        str = "The gates are open. ";
    else 
        str = "The gates are closed to keep villains out. ";

    return "You are standing in front of the western gates of "+
         "the little village Bree. " + str + "The village lies east while "+
         "the Great East Road is to the west.\n";
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
    tell_tree_fort("went north along the hedge at Bree");
}
void tree_south()
{
    tell_tree_fort("went south along the hedge at Bree");
}
void tree_west()
{
    tell_tree_fort("went west from Bree.");
}
