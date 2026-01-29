/*
 * Road leading to Causeway from Great East Road
 * -- Finwe, March 2005
 */

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
    areadesc = "field";
    area = "west of";
    areaname = "the Brandywine river";
    land = "Eriador";
    areatype = 1;

    grass = "green";
    
    extraline = "The country lane runs north and south. The field is " +
    "damp from the last time the river flooded. The river flows south " +
    "alongside the lane. Bushes and trees grow alongside the lane.";

    set_add_plains();
    set_add_brandywine();
    set_add_road();
    set_add_plants();
    
    add_exit(EAST_R_DIR + "er21s1","north",0,2);
    add_exit(EAST_R_DIR + "er21s3","south",0,2);
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
