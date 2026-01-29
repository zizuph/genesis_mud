/*
    /d/Shire/waymeet/rooms/fields/field09.c

    Field in the farm north of Waymeet
    Perrigrine, February 2019
	
	Added trees and juniper berries
	Raymundo, January 2020
*/
#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit WAYM_LIB_DIR + "base_field.c";


void create_field()
{
    area = "near"; /* Distance from areaname */
    areaname = "Waymeet";
    land = "the Shire";
    areatype = 4;
    areadesc = "vegetable field";

    extraline = "These large vegetable fields provide produce for the village " +
        "of Waymeet. A row of trees provides a break from the wind here, saving " +
		"the soil from erosion. " +
		"You see cabbages, beets, carrots, and other essentials " +
        "spread around in careful rows. Amongst the rows you notice rather large " +
        "pawprints.";
	add_trees();
   
	
    add_exit(WAYM_FIELD_DIR + "field17","south");
    add_exit(WAYM_FIELD_DIR + "field01","north");
    add_exit(WAYM_FIELD_DIR + "field10","east");
}
public void
reset_shire_room()
{

    set_searched(0);
    
    if(!present("wolf"))
    {
        add_wolf();
    }
    veg_count = 0;
}

void init()
{
    ::init();
    add_action("pick_vegetable", "pick");
}
