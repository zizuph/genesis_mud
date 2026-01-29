/*
 * North-South Road between Waymeet to Sarn Ford
 * By Finwe, January 2020
 */

#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "../defs.h"

inherit "/d/Shire/ns_road/std/base_road.c";

#define RUFFIN_NPC    NS_NPC_DIR + "ruffian" 
#define MAX_NPCS 3

static object *npc = allocate(MAX_NPCS);

void
create_road_room()
{
    set_areadesc("well travelled road");
    set_area("in central");
    set_areaname("Southfarthing");
    set_land("the Shire");
    set_areatype(0);

    set_vbfc_extra(road_desc3);
    set_extraline("The " + areadesc + " travels north into the Shire " +
        "and south as it crosses the fields of Southfarthing.");

    set_add_southfarthing();
    set_add_farms();
    add_longbottom_descr();

    add_exit(NS_RM_DIR + "road13", "north", "@@check_exit@@");
    add_exit(NS_RM_DIR + "road11", "south", "@@check_exit@@");

    reset_shire_room();
}

void reset_shire_room()
{
    set_searched(0);

    object ruffian;
    int npc_count;


    if(!present("ruffian"))
    {
        npc_count = random(MAX_NPCS);

        if(npc_count == 0)
            npc_count = 3;
        add_npc(RUFFIN_NPC, MAX_NPCS);
    }
}
