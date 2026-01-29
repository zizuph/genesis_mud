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

    add_my_desc("The hedge and dike suddenly angle to the " +
        "southeast and go straight north here. The hedge is tall " +
        "and made up of all types of thick trees.\n");

    set_add_hedge_road();
    set_add_bushes();
    set_add_dike();

    add_exit(ROAD_DIR + "shedge01", "north");
    add_exit(ROAD_DIR + "shedge03", "southeast");

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

