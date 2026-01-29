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
 
void create_path_room() {}

public void create_area_room()
{
	set_areadesc("path");
	set_area("just east of");
	set_areaname("the foothills");
	set_land("the Misty Mountains");
	set_areatype(0);
	
	add_item(({"path", "ground"}), "The path is thin here, almost nonexistent, being swallowed up buy wild grass growing around.\n");
	
	create_path_room();
	add_std_herbs("hills");
 
	add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
}

void
init()
{   
    ::init();
}

string path_desc1()
{
    return "To the west mountains fill the view. Nearby, a river flows on its southern course, while Mirkwood forest looms in the distance to the east. The land is marshy as the river often floods the area nearby. ";
}

string path_desc2()
{
    return "To the west mountains fill the view, rising high over the tops of rugged looking foothills. In the distance, a river can be seen, and farther still the grim spectre of Mirkwood forest. ";
}

string path_desc3()
{
    return "The beaten dirt path meanders at the base of the foothills. Looming high overhead, the Misty Mountains dominate the view to the west. The sound of rushing water can be heard, and a small river can be seen north of here. Mirkwood forest can be seen east of here. ";
}

string path_desc4()
{
    return "Far to the west, the foreboding peaks of the Misty Mountains rise high. The flow of a river can be heard, and the river itself can be seen just to the east. Far in the distance, Mirkwood forest can be seen, a grim and brooding presence. ";
}
