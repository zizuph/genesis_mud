/*
 * Base file for paths Grey Mountains
 * Finwe, September 2004
 */

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit HERB_SEARCH;
inherit "/d/Shire/std/room/room_tell";
inherit "/cmd/std/command_driver";
 
void create_field_room() {}

public void create_area_room()
{
	set_areadesc("grassy field");
	set_area("just east of");
	set_areaname("the foothills");
	set_land("the Misty Mountains");
	set_areatype(0);
	
	add_item(({"field", "grassy field"}), "The path is thin here, almost nonexistent, being swallowed up buy wild grass growing around.\n");
	add_item("ground", "The ground is covered in long flowing grass as far as the eye can see, even onto the lower foothills.\n");
	add_item("grass", "The grass is long, nearly knee high to a human, green at the marshy land nearer the river, but dry and yellow on towards the foothills.\n");
	
	create_field_room();
	add_std_herbs("field");
	
	set_room_tell_time(120+random(15));
	add_room_tell("A butterfly floats by on a breeze.");
	add_room_tell("Clouds pass by overhead.");
	add_room_tell("A long howling can be heard in the distance.");
	add_room_tell("A gentle wind blows across the fields, stirring the long grass.");
	add_room_tell("For a moment, not a sound can be heard.");
	
	add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
}

void
init()
{   
    ::init();
}

string field_desc1()
{
    return "To the west mountains fill the view, rising high over the tops of rugged looking foothills. In the distance, a river can be seen, and farther still the grim spectre of Mirkwood forest. Tall grass grows all around, in great abundance. ";
}

string field_desc2()
{
    return "The rolling foothills are very close, nestled at the bottom of the Misty Mountains. Tall grass grows all around, in great abundance. ";
}

string field_desc3()
{
    return "This is the beginning of the foothills. To the west, nothing but the daunting view of the Misty Mountains can be seen, running north and south. Tall grass grows all around, in great abundance. ";
}
