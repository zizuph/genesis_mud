#pragma save_binary
#pragma strict_types

#include "local.h"

inherit BASE_COMMON;
inherit EAST_ROAD;
#define IS_ELF_GR_TRAVELLER "/d/Shire/std/elf_gr_patrol.c"
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "w";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }


 
void
create_er_room()
{
    area = "somewhere in";
    areaname = "East Farthing";
    land = "Eriador";
    areatype = 10;
    areadesc = "rolling hills";
    grass = "green";
 
    extraline = "The Great East Road passes through rolling hills and " +
        "meadows. They go on for miles to the north. Small farms dot " +
        "the fields in the distance, and bushes grow in scattered " +
        "groups everywhere. To the east is a bridge, and the Brandywine " +
        "river flowing beneath it.";
 
    add_item(({"bush","bushes"}),"The bushes are lush and green, full "+
        "of health and life.\n");
    add_item("landscape","All around you is green, growing and "+
        "vibrant.\n");
    add_item(({"brown road","road"}),"The road is brown from "+
        "mud having overtaken the grey pebbles and cobblestones in "+
        "places.\n");
    add_item(({"hill","hills","slim hill","slim hills"}),
        "The hills nearby are slight and rolling, very pleasant all in all.\n");
    add_item(({"meadows", "green meadows"}),
        "They are green and thick, and cover the land.\n");
    
    set_add_farms();
    set_add_stonebows_bridge_away();
    set_add_brandywine();

    add_exit(EAST_R_DIR + "er21d","west",0,2);
    add_exit(EAST_R_DIR + "stonebows","east",0,2);
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

