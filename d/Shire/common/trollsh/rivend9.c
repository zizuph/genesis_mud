/* File: /d/Shire/common/eastroad/rivend9.c */

#include "defs.h"
inherit "/d/Shire/common/lib/eastroad";	/*master object*/

inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "sw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }



object spider;

create_eastroad()
{

    set_short("Great Eastroad");
    set_long("Here the road narrows a bit, turning into a large "
            +"path. West of the path the Trollshaws loom "
            +"over their scary history. To the east you can hear "
            +"some trickling water from some river.\n");

    add_item(({"eastroad","road","path","large path","narrowing"}),
        "The road is wide and seems to be in constant use.\n");

    add_item(({"river","water","trickling water"}),
               "The trickling water from the east must be " +
               "coming from a river nearby.\n");
    add_item(({"gravel"}),
	    "The gravel is rough and covers the road.\n");
    add_item(({"large trees", "trees"}),
        "Various tall firs and deciduous trees grow alongside " +
        "the road. They are tall, blocking the sky.\n");
    add_item("stunted trees",
        "They grow in various spots, dwarfed by their taller " +
        "neighbors. The stunted trees look like they have " +
        "survived the roughest treatment and defy the elements.\n");
    add_exit(STAND_DIR + "rivend8", "southwest", 0);
    add_exit(STAND_DIR + "mpath1", "north", 0);
    
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