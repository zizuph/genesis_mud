/*
 * South Gate of Bree
 * By Finwe, June  2002
 *
 * 2004/11/08 Last update
 * 2011/07/21 Lavellan - Updating to use fixed base rooms
 */

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit "/d/Shire/bree/stdgateroom.c";
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "s";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }


create_gateroom()
{
    set_short("Southern gate of Bree");
//    set_long("@@my_long");
    set_other_room(ROAD_DIR + "broad05");
    set_direction("west");

    set_add_dike();
    set_add_outside_hedge();
    set_add_ger();

    add_exit(ROAD_DIR + "shedge08",   "south");
    add_exit("/d/Shire/eastroad/eastern/erb2", "northeast");
    
}

//my_long() {
long_desc() {
  string str;

    if (gatestate) str = "The gates are open. ";
    else str = "The gates are closed to keep villains out. ";
    return "This is the southern most part of Bree, protected by " +
        "the South Gate. The land is clear of shrubs and growth, except " +
        "for a large hedge that runs south of here and encircles the " +
        "town. A deep dike has been dug alongside the hedge and " +
        "offers further protection to the town. The road runs northeast " +
        "into the wilds. " + str + "\n";
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
