/* File: /d/Shire/common/trollsh/rivend8.c */

#include "defs.h"
inherit "/d/Shire/common/lib/eastroad";	/*master object*/
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }


create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	    "All that you can see around you is the thick bushes that "+
	    "block your view, but you can hear a river not far away. "+
	    "To your west the path goes towards Bree, and you can see "+
	    "the path going some northeast too. To your north you can spot "+
	    "some kind of opening in the forest.\n");

    add_item(({"eastroad", "road" }),
	    "The road is wide and seems to be in constant use.\n");

    add_item("opening",
        "A bit north of here you can spot an opening in the " +
        "forest. It looks impossible to go there since the " +
        "bushes are so dense.\n");
    add_item(({"gravel"}),
	    "The gravel is rough and covers the road.\n");
    add_item(({"large trees", "trees"}),
        "Various tall firs and deciduous trees grow alongside " +
        "the road. They are tall, blocking the sky.\n");
    add_item("stunted trees",
        "They grow in various spots, dwarfed by their taller " +
        "neighbors. The stunted trees look like they have " +
        "survived the roughest treatment and defy the elements.\n");
    
    add_exit(TROLLSH_DIR + "rivend9", "northeast", 0);
    add_exit(TROLLSH_DIR + "rivend7", "west", 0);
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