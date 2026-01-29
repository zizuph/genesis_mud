#pragma save_binary
#pragma strict_types

#include "local.h"

#define IS_ELF_GR_TRAVELLER "/d/Shire/std/elf_gr_patrol.c"

inherit EAST_ROAD;
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "n";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }


void
create_er_room()
{

   area = "on";
   areaname = "the Great East Road";
   land = "Eriador";
   areatype = 8;
   areadesc = "the land near Bree";

   extraline = "East are the gates of the little village "+
     "Bree. The road also continues west to the rest of Shire. "+
       "To the north you see hills upon hills. South of you is "+
	 "a forest.";

   add_item("bree","Bree is too far to see from here. Perhaps "+
	    "if you go east you could see it better.\n");
   add_item("village","Bree is to the east. You can't "+
	    "see Bree itself, but you can see some smoke "+
	    "from the chimneys. You wonder how much farther "+
		"it is to Bree.\n");
   add_item(({"gates","gate"}),"You see in the distance the "+
		"gates of Bree. At night they are closed and you "+
	    "probably have to knock on the gates to get in. "+
	    "But during the day that should not be a problem.\n");
   add_item(({"hill","hills"}),"The hills countinue as far "+
	    "as you can see.\n");
   add_item("forest","The forests seems thick. But you think "+
	    "that you might be able to navigate your way "+
	    "through the forest.\n\nYou could be wrong though!\n");

    add_exit(EAST_R_DIR + "er29n","north", "@@tree_north@@", 2,1);
    add_exit(EAST_R_DIR + "er29s","south","@@tree_south@@", 2,1);
    add_exit("/d/Shire/bree/rooms/road/crossroad","east","@@tree_east@@");
    add_exit(EAST_R_DIR + "er28","west","@@tree_west@@");
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



void tree_east()
{
    tell_tree("went east to the Crossroads.");
    tell_tree_fort("went east to the Crossroads.");
}

void tree_west()
{
    tell_tree("went west towards the Shire.");
    tell_tree_fort("went west towards the Shire.");
}

void tree_north()
{
    tell_tree("went north into the fields next to the tree.");
    tell_tree_fort("went north into the fields next to the tree.");
}

void tree_south()
{
    tell_tree("went south into the fields south of the Crossroads.");
    tell_tree_fort("went south into the fields south of the Crossroads.");
}
