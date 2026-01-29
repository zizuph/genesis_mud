/*
 * Road leading to Causeway from Great East Road
 * -- Finwe, March 2005
 */

#include "local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit BASE_COMMON;
inherit EAST_ROAD;
#define IS_ELF_GR_TRAVELLER "/d/Shire/std/elf_gr_patrol.c"
inherit IS_ELF_GR_TRAVELLER;

static string  patrol_dir = "e";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_er_room()
{
    areadesc = "field";
    area = "west of";
    areaname = "the Brandywine river";
    land = "Eriador";
    areatype = 1;

    grass = "green";
    
    extraline = "The country lane runs north and south. It passes through " +
    "a field alongside the river. Plants grow everywhere, and line " +
    "the lane. The land is drier here and plants grow everywhere. There " +
    "is pier to the east.";

    set_add_plains();
    set_add_brandywine();
    set_add_road();
    set_add_plants();

    add_item(({"pier", "platform", "wooden platform"}),
        "It's a wooden platform that extends from the road out to " +
        "the river.\n");
    add_item(({"wood"}),
        "The wood is dark and sturdy. It was used to construct the pier.\n");

    add_exit(EAST_R_DIR + "er21s3","north",0,2);
    add_exit(EAST_R_DIR + "er21s5", "south",0,2);
    add_exit(EAST_R_DIR + "pier", "east",0,2);

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

public void reset_shire_room()
{
    ::reset_shire_room();

}
