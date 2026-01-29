/*
 * Base room for orc side of the cave system under the grey mountains
 * Altrus, July 2005
*/
 
inherit "/d/Shire/std/room.c";
inherit "/d/Shire/std/room/room_tell";

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

/*
 *Cave descriptions
*/
string cave_desc1()
{
    return "You are standing in a dark tunnel somewhere underneath the Grey Mountains. The walls, or what you can make out of them in this darkness, seem naturally formed. There air is still and moist. ";
}

string cave_desc2()
{
    return "You are standing in a dark tunnel somewhere underneath the Grey Mountains. The walls look like they are naturally formed, but here and there you notice crude attempts at expanding the existing natural tunnels. ";
}

string cave_desc3()
{
    return "The tunnel here seems to be crudely carved out of the rock of the mountain. The passage is narrow, and the ceiling is low. The floor is littered here and there with debris. ";
}

string cave_desc4()
{
    return "The tunnels here clearly have been carved, using crude tools of some sort. Little care seems to have been given in their making. The inhabitants of these caves obviously have no inclination towards cleanliness, as debris has been strewn about along the sides of the tunnels. ";
}


string cave_desc5()
{
    return "The air is rank here, almost as if something has died and been rotting for a few days. The tunnels are fairly wide, allowing nearly three to walk abreast. The walls have been crudely fashioned, almost no symmetry or design gone into their making. ";
}

void set_rtells_cave()
{
	set_room_tell_time(120+random(15));
	add_room_tell("Water drips from the ceiling.");
	add_room_tell(".");
	add_room_tell(".");
	add_room_tell(".");
}