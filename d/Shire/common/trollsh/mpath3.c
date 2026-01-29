/* File: /d/Shire/common/eastroad/mpath3 */

#include "defs.h"
#include <ss_types.h>

inherit "/d/Shire/common/lib/rom";
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "s";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

create_rom()
{

    set_short("On the Great East Road near the Trollshaws");
    set_long("You are on the Great East Road along the river " +
		"Bruinen. To the west is the great forest Trollshaws. " +
		"It is said that the forest is packed with trolls. " +
		"@@exa_bark@@\n");

    add_item(({"path", "path", "great east road", "road"}),
        "This is a road by the river Bruinen. The road follows " +
        "the river upstream.\n");
    add_item(({"river","bruinen","water"}),
        "This is the mighty river Bruinen. It doesn't seem " +
        "possible to cross here, maybe further south.\n");
    add_neg(({"swim", "enter", "dive", "jump"}),
        "[into] [in] [over] [across] [the] 'river' / 'bruinen' / 'Bruinen'",
        "You notice that the water is freezing cold, hence, you " +
        "would not even try it.\n");


    add_item(({"mud"}),
        "This is a brown sticky mud. It's obviously made by the "+
        "water from the Bruinen.\n");

    add_item(({"marks","barque","bark","tree"}),
	"@@exa_barque@@");

    NORTHEAST("mpath4");
    SOUTH("mpath2");
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

string
exa_bark()
{
      if (TP->query_skill(SS_AWARENESS) >30)
            return "On one of the trees you notice some marks on the bark.\n";  
         else
            return "The river is getting smaller the closer you get to \n"+
                   "the Misty Mountains.\n"; 
                             
}
string
exa_barque()
{
    if (TP->query_skill(SS_TRACKING) + WIS(TP) + INT(TP) > 300 - random(50))
  return "The marks in the bark seem to have been made by a club. "+
      "Apparently some fighting has taken place here, perhaps even some "+   
      "trolls were involved, as there is known to be a LOT of trolls "+
      "living in the forest.\n";
 else
   return "Just some odd markings in the bark.\n";
}


/* This is the original code from 61-65 I found here. I'm replacing the
 * string, if you hate it, you can replace what you had here originally :)
 * Mayhem.
	return "It looks like marks after a club. It have obviously been "
             + "some fighting here, probably after some troll, since the "
             + "forest is know to inhabit a LOT of trolls. \n";
    else
	return "It looks like large marks in the bark! \n";
 */
