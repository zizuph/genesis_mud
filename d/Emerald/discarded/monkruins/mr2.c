/*
 * MR2.c 
 * Ruins of Kamesh
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

void
create_room()
{
    set_short("A narrow path through ruined buildings");
    set_long("   The cold, ocean wind blows east-west across the "+
	     "path and between the ruined stone buildings, creating "+
	     "a high-pitched wailing sound which sends a chill down "+
	     "your spine. There are broken, crumbled stone buildings "+
	     "all around. None of them have roofs of any kind, and most "+
	     "of them have holes in their walls. One or two of the smaller "+
	     "buildings are missing entire walls. There is a gray, wet fog "+
	     "here which masks the true colors of everything in its "+
	     "dulling shadow. The path continues to the north where the "+
	     "fog thickens. There are more ruins to the west, and to "+
	     "the south there is a large, dark "+
	     "shape which could be another building. The fog to the "+
	     "south obscures it so much that you cannot tell.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"buildings", "broken buildings", "crumbled buildings",
		"ruins", "ruined buildings"}),
	     "The ruins of these buildings are impressive. You notice "+
	     "one building which may have been the dormitory or something "+
	     "similar. Dozens of little walls stand alone atop the "+
	     "foundation of the roofless building. The buildings would "+
	     "have been amazing in their prime. Most of the ruins are "+
	     "tall, sprawling stone structures with simple, yet elegant "+
	     "designs.\n");

    add_item("walls",
	     "Some of the walls of the ruined buildings are cracked, some "+
	     "have holes in them, and some even have walls which are "+
	     "crumbled and missing entirely. You begin to wonder if this "+
	     "place fell to ruin naturally or if something happened to "+
	     "cause this destruction.\n");

    add_item( ({"fog", "mist", "gray fog", "wet fog"}),
	     "The gray, wet fog dampens the ordinarily brilliant "+
	     "colors of the surroundings so that everything appears to "+
	     "be a shade of blue or gray. The ground and stone is moist with "+
	     "droplets left by the hanging mist.\n");

    add_item( ({"building", "shape", "large shape", "dark shape",
		"large dark shape"}),
	     "After peering through the mist at the large, dark shape "+
	     "you eventually determine that it is a building. Although "+
	     "you notice something very peculiar about it indeed. It is "+
	     "completely intact!\n");

    add_exit(MONKRUIN_DIR + "mr1", "north");
    add_exit(MONKRUIN_DIR + "mr3", "west");
    add_exit(TEMPLE_DIR + "path4", "south");
}

