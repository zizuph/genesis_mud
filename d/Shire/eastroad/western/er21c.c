#pragma save_binary
#pragma strict_types

#include "local.h"

inherit BASE_COMMON;
inherit EAST_ROAD;

#define IS_ELF_GR_TRAVELLER "/d/Shire/std/elf_gr_patrol.c"
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "s";
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
 
    extraline = "Green meadows cover the land. The rolling hills of " +
        "East Farthing are covered with grass and bushes. The road " +
        "wanders between them in a east-west direction. Some " +
        "farms dot the area.";
 
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

    add_exit(EAST_R_DIR + "er21b","west",0,2);
    add_exit(EAST_R_DIR + "er21d","east",0,2);
//   add_exit(EAST_R_DIR + "er21s1" , "south", "@@block_room@@");
    add_exit(EAST_R_DIR + "er21s1" , "south");
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

 
int
block_room()
{
    if (this_player()->query_wiz_level()) return 0;

    write("The Brandywine river has flooded, and blocked the way south.\n");
    return 1;
}