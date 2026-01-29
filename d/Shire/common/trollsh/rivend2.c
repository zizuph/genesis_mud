/* File: /d/Shire/common/trollsh/rivend2.c */

#include "defs.h"
inherit "/d/Shire/common/lib/eastroad";	/*master object*/


inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "nw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

object troll;

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	     "You are walking on a path on the eastern part of the Trollshaws. "+
	     "The forest is getting darker the further in you move. To your northwest "+
	     "a small bridge can be seen. All around you are trees, quite thick, "+
	     "but not as thick as they look further inwards.\n");

    add_item(({"eastroad", "road" }),
        "The road is wide and looks well worn.\n");
    add_item("bridge", "It's hard to see any details of the " +
        "small bridge from this distance.\n");
    add_item(({"gravel"}),
	    "The gravel is rough and covers the road.\n");
    add_item(({"large trees", "trees"}),
        "Various tall firs and deciduous trees grow alongside " +
        "the road. They are tall, blocking the sky.\n");
    add_item("stunted trees",
        "They grow in various spots, dwarfed by their taller " +
        "neighbors. The stunted trees look like they have " +
        "survived the roughest treatment and defy the elements.\n");
    add_exit(STAND_DIR + "rivend3", "east", 0);
    add_exit(STAND_DIR + "rivend1", "northwest", 0);

    troll = clone_object(TROLLSH_DIR + "npc/conf_troll");
    troll->move(TO);
    
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

reset_rom()
{
   if(!troll)
   {  
       troll = clone_object(TROLLSH_DIR + "npc/conf_troll");
       troll->move(TO);
   }
}
