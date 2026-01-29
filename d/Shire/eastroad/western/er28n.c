#pragma save_binary
#pragma strict_types

#include "local.h"

#define IS_ELF_GR_TRAVELLER "/d/Shire/std/elf_gr_patrol.c"
inherit IS_ELF_GR_TRAVELLER;
inherit EAST_ROAD;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }
 
void
create_er_room()
{
    area = "close to";
    areaname = "the Great East Road";
    land = "Eriador";
    areatype = 1;
    areadesc = "field";
    grass = "green";
    
    extraline = "You are standing at the foot of many hills. "+
      "The hills go on for miles to the north. South of you is "+
	"the Great East Road. While to the east and the west you "+
	  "see more hills. ";
    
    add_item(({"surroundings","expanse","fields","shire"}),
	     "The hills stretch out to the north, east and west. To the "+
	     "south of you runs the Great East Road.\n");
    
    add_item(({"hills","hill",}),
	"The hills themselves, while steep, look very rich and full "+
	     "of life.\n");
    
    set_add_bushes();

    set_noshow_obvious(1);
    add_exit(EAST_R_DIR + "er28","south", "@@tree_south@@", 0,2);
    add_exit(EAST_R_DIR + "er27n","west", "@@tree_west@@", 0,2);   
    add_exit(EAST_R_DIR + "er29n","east", "@@tree_east@@", 0,2);

    reset_shire_room();
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

void
reset_shire_room()
{
   object stick;

   if(!present("stick"))
   {
     stick = clone_object(ER_OBJ + "stick");
     stick->move(TO);
   }
}

void tree_south()
{
    tell_tree_fort("went south onto the Great East Road.");
}

void tree_west()
{
    tell_tree_fort("went west in the fields and disappeared.");
}

void tree_east()
{
    tell_tree_fort("went east in the fields towards Bree.");
}
