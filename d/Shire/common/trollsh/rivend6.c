/* File: /d/Shire/common/trollsh/rivend6.c */


#include "defs.h"
inherit "/d/Shire/common/lib/eastroad";	/*master object*/
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "sw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

create_eastroad()
{
    set_short("Great Eastroad");
    set_long(
	    "You are walking south of the great forest Trollshaws. "+
	    "The forest is dense here, but you can spot an opening "+
	    "to the north. The road bends a little southwest, so "+
	    "it's difficult to see what's hiding behind the bend.\n");

    add_item(({"eastroad", "road" }),
        "The road is wide and seems to be in constant use.\n");
    add_item(({"gravel"}),
	    "The gravel is rough and covers the road.\n");
    add_item(({"large trees", "trees"}),
        "Various tall firs and deciduous trees grow alongside " +
        "the road. They are tall, blocking the sky.\n");
    add_item("stunted trees",
        "They grow in various spots, dwarfed by their taller " +
        "neighbors. The stunted trees look like they have " +
        "survived the roughest treatment and defy the elements.\n");
    add_exit(STAND_DIR + "rivend7", "east", 0);
    add_exit(STAND_DIR + "rivend5a", "southwest", 0, 2);
    add_exit(STAND_DIR + "riv6no", "north", 0);
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