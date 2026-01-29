/* File: /d/Shire/common/trollsh/rivend1.c */
#include "defs.h"
inherit "/d/Shire/common/lib/eastroad";	/*master object*/


inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "nw";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

create_eastroad()
{

    set_short("Great Eastroad");
    set_long(
	  "You are walking on the Great Eastroad going east of Bree. "+
	  "You are standing southeast of the Last Bridge, the path "+
	  "continues eastwards deeper into the Trollshaw. The forest "+
	  "is getting darker as you move on into it, and it "+
	  "looks a little frightening here. Lots of strange noises "+
	  "can be heard, but it is hard to make out where they come from.\n");

    add_item(({"eastroad", "road" }),
	"The road is narrower here then at the bridge. It looks " +
    "like it has been used a lot. \n");
    add_item(({"gravel"}),
	"The gravel is rough and covers the road.\n");
     add_item(({"large trees", "trees"}),
        "Various tall firs and deciduous trees grow alongside " +
        "the road. They are tall, blocking the sky.\n");
    add_item("stunted trees",
        "They grow in various spots, dwarfed by their taller " +
        "neighbors. The stunted trees look like they have " +
        "survived the roughest treatment and defy the elements.\n");
    add_item(({"bridge", "last bridge", "bridge of mitheithel"}),
        "It is made of stone and well worn. Arching over the " +
        "river, it provides a safe way to cross the river.\n");

   // "/d/Shire/common/trollsh/shaws16"->teleledningsanka();
    SOUTHEAST("rivend2");
    add_exit(ERE_DIR + "erb38", "northwest", 0);
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
