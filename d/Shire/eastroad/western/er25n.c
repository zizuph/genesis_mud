#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
#define IS_ELF_GR_TRAVELLER "/d/Shire/std/elf_gr_patrol.c"
inherit IS_ELF_GR_TRAVELLER;

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
       "the Great East Road. While to the east and west you see "+
	 "more hills.";
   
   add_item(({"surroundings","expanse","fields","shire"}),
	    "The hills stretch out to the north, east and west. To the south of "+
	    "You runs the Great East Road.\n");
   
   add_item(({"hills","hill",}),
	    "The hills themselves, while steep, look very rich and full "+
	    "of life.\n");

     set_add_bushes();
   
   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er25","south",0,2);
   add_exit(EAST_R_DIR + "er24n","west",0,2);   
   add_exit(EAST_R_DIR + "er26n","east",0,2);
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