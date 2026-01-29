/*
	*Foothills of the Misty Mountains
	*Altrus, June 2005
*/
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;

void create_area_room()
{
	areadesc = "hilltop";
	area = "among";
	areaname = "the foothills";
	land = "the Misty Mountains";
	areatype = 0;
	extraline = "The hills here are dry, covered in a long grass. Bushes sprout among the hills here and there, and especially in and around the gullies. The Misty Mountains loom menacingly overhead, filling the view to the west. To the east, a wide expanse of field can be seen. The land grows marshy near the river, and further east the dark presence of Mirkwood Forest broods.\n";
	
	add_item(({"foothills", "hills"}), "The tumbled hills at the foot of the Misty Mountains rise all around you. They are rugged hills, full of gullies and covered in wild grasses.\n");
	add_item("gullies", "Some of them are deep, others mere shallow cuts in the hills, but they cover the foothills, making for a treacherous landscape even at this low level.\n");
	add_item("bushes", "They are really not much to speak of. Dry plants they are, most likely a sage of some sort. Whatever they may be they are short and sparse.\n");
	add_item(({"field", "fields", "expanse"}), "The fields stretch out east towards the river, ending in a marsh near. They come west even so far as to cover some of the lower foothills, great expanses of knee-high grass./");
	add_item("grass", "The grass is mostly dry, except where it grows nearest the river.\n");
	add_item(({"river", "anduin", "the great river", "great river"}), "The river, Anduin, appears as a thin ribbon in the distance.\n");
	add_item(({"mountains", "misty mountains"}), "The Misty Mountains dominate your view as you stand at their feet. Large boulders and rocks have tumbled down from the mountain and lay strewn about.\n");
	add_item(({"boulders", "rocks"}), "They must have fallen during an avalanche. Best be careful while travelling through here.\n");
	add_item(({"land", "lands"}), "The lands here about vary greatly, from the tall and threatening Misty Mountains, to the lower foothills covered in dry grass and low bushes, to the fields and marshes near the river.\n");
	add_item(({"forest", "mirkwood", "mirkwood forest", "greenwood", "greenwood forest", "greenwood the great", "wood", "the great wood", "taur e-ndaedelos"}), "It is a large carpet of dark trees and spread out to the east. The forest stretches north and sout, blocking your view beyond it.\n");
	add_item(({"large trees", "trees"}), "The trees are of the forest are difficult to look at, but they look ancient and twisted, and all look black colored.\n");
	
	add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room
	
	add_exit(DOOR_DIR + "hill1", "east");
	add_exit(DOOR_DIR + "hill4", "north");
	
	reset_shire_room();
}

void reset_shire_room()
{
}
