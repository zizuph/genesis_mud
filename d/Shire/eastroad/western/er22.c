
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
   area = "on";
   areaname = "the Great East Road";
   land = "Eriador";
   areatype = 8;
   areadesc = "the land";
 
   extraline = "South of here is a forest. North you see "+
   "hills and more hills. The road continues east to the "+
	"city of Bree. The road continues west to the Brandywine "+
	"river. Down the road on your west you see an inn. The inn "+
	"stands just before the Bridge of Stonebows.";
 
	add_item("forest","The forest does not seem that hard to "+
		"move through. You see the forest thinning out in the "+
		"west because of the Brandywine river. You notice that "+
		"is where the forest thins out at a bank of the river.\n");
	add_item(({"hill","hills"}),"The hills are non-ending. "+
		"To the northwest you see the Brandywine river meet "+
		"up with the hills.");
	add_item(({"river","brandywine","brandywine river"}),
		"The Brandywine Bridge is west of here. The river "+
		"looks deep cold wet and it also looks as if it is moving "+
		"swiftly. At least that is what it seems like.\n");
	add_item(({"bridge","stonebows","bridge of stonebows"}),"You "+
		"see that the Bridge of Stonebows is made out of stone. You "+
		"do notice an inn between you and the bridge.\n");
	add_item(({"inn","building"}),"The inn is a little ways down the "+
		"road. It looks like a nice place to stop and get some food or "+
		"drink.\n");
 
//   add_exit(EAST_R_DIR + "stonebows","west",0,2);
   add_exit(EAST_R_DIR + "stonebows","west","@@enter_shire@@",2);
   add_exit(EAST_R_DIR + "er23","east",0,2);
   add_exit(EAST_R_DIR + "er22n","north","@@north_msg@@",2,1);
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

void enter_shire()
{
    write("You cross the East Farthing border and enter the Shire.\n");
}