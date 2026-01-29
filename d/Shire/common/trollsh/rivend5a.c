/* File: /d/Shire/common/trollsh/rivend5.c */
#include "defs.h"
inherit "/d/Shire/common/lib/eastroad";	/*master object*/
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "sw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

object troll;

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	    "You are walking in the middle of the great forest Trollshaws. "+
	    "This is a dark and gloomy place. The sun seldom or never shines "+
	    "here.\n");

    add_item(({"eastroad", "road" }),
	    "The road is narrow and seems to be used a lot.\n");
    add_item(({"gravel"}),
	    "The gravel is rough and covers the road.\n");
    add_item(({"large trees", "trees"}),
        "Various tall firs and deciduous trees grow alongside " +
        "the road. They are tall, blocking the sky.\n");
    add_item("stunted trees",
        "They grow in various spots, dwarfed by their taller " +
        "neighbors. The stunted trees look like they have " +
        "survived the roughest treatment and defy the elements.\n");
    add_exit(TROLLSH_DIR + "rivend6", "northeast", 0);
    add_exit(TROLLSH_DIR + "rivend5", "southwest", 0);

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