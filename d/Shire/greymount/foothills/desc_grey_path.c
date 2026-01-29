/*
	*Desc file for the path to the Grey Mountains
	*Altrus, September 2005
*/
 
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";
inherit "/cmd/std/command_driver";

//
void add_foothills()
{
	add_item(({"foothills", "hills"}), "The low hills at the base of the Grey Mountains are rocky and mostly barren, only sparsely dotted with small plants.\n");
	add_item("plants", "There are various plants growning among the foothills here, but they are all short and thin, mostly dried out due to the barren landscape.\n");
}

//Mount Gundabad, somewhat distant
void add_gundabad_far()
{
	add_item(({"gundabad", "mount gundabad"}), "The forboding peak of Mount Gundabad rises higher than the other peaks in this region. It is difficult to see the top, due to the dense formation of clouds that seem to be perpetually gathered at the peaks of the Misty Mountains.\n");
	add_item(({"formation", "clouds"}), "The clouds are thick and hard to see through, but it is clear that the peaks of the mountains are covered in snow.\n");
}

//Mount Gundabad, close
void add_gundabad_close()
{
	add_item(({"gundabad", "mount gundabad"}), "This is where the ranges of the Grey and Misty Mountains converge, forming this enormous peak known as Mount Gundabad.\n");
	add_item(({"formation", "clouds"}), "The clouds are thick and hard to see through, but it is clear that the peaks of the mountains are covered in snow.\n");
}


//Mount Gundabad, very near
void add_gundabad_near()
{
	add_item(({"gundabad", "mount gundabad"}), "You have to look nearly straight up to see the dreaded peak of Mount Gundabad from here, so high does it reach into the sky. Its forboding heights are covered with a dense formation of clouds.\n");
	add_item(({"formation", "clouds"}), "The clouds are thick and hard to see through, but it is clear that the peaks of the mountains are covered in snow.\n");
}

//Adds in the Misty Mountains
void add_misty()
{
	add_item("misty mountains", "The Misty Mountains can be seen to the south and west of here, running north to form the peak of Mount Gundabad.\n");
	add_item("peaks", "The peaks are rugged, of varying heights, but they all rise high above you, shrouded in mist and cloud.\n");
}


//Grey Mountains, seen north of the viewer
void add_grey_north()
{
	add_item("grey mountains", "The Grey Mountains, though far lower than the Misty Mountains, are still quite formidable. Their barren slopes can be seen just north of here.\n");
	add_item("slopes", "The slopes of the Grey Mountains are rocky, mostly barren at higher regions.\n");
}

//Grey Mountains, seen northeast of the viewer
void add_grey_northwest()
{
	add_item("grey mountains", "The Grey Mountains can be seen quite easily to the northeast. Though not as high as the Misty Mountains, the two ranges meet in the northwest to form the giant peak of Mount Gundabad.\n");
	add_item("slopes", "The slopes of the Grey Mountains are rocky, mostly barren at higher regions.\n");
}

//View of the small langwell river, far
void add_langwell_far()
{
	add_item(({"langwell", "river langwell"}), "In the distance the river Langwell can be seen flowing east to join the Greylin in forming the Langflood.\n");
	add_item(({"langflood", "river langflood"}), "The river Langflood can not be seen from here.\n");
}

//View of the small langwell river, near
void add_langwell_near()
{
	add_item(({"langwell", "river langwell"}), "The cold waters of the Langwell river flow by here, rushing along their easterly route towards the beginning of the Langflood.\n");
	add_item(({"langflood", "river langflood"}), "The river Langflood can not be seen from here.\n");
}

//View of the small greylin river, far
void add_greylin_far()
{
	add_item(({"greylin", "river greylin"}), "The small river Greylin can be seen a far way off as it flows along its course to be joined with the Langwell river.\n");
}

//View of the small greylin river, near
void add_greylin_near()
{
	add_item(({"greylin", "river greylin"}), "The icy cold water of the Greylin streams past quickly on its way south.\n");
}

void add_rtells()
{
	set_room_tell_time(90+random(15));
	add_room_tell("A cold wind comes blasting from the east.");
	add_room_tell("Dark clouds pass by overhead.");
	add_room_tell("The long cry of a lone wolf sounds in the distance.");
	add_room_tell("The biting cold causes you to shiver.");
	add_room_tell("The sound of rushing water can be heard nearby.");
}
