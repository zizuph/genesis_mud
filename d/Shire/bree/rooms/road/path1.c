/*
 * Path behind the AG in Bree.
 * Raymundo, Jan 2020
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "defs.h"

inherit PATH_BASE;



void
create_path_room()
{
	add_bree_desc("The grass is deep here, nearly to your knees, despite "
		+ "the roof hanging over the path. A ways to the north, you see "
		+ "the Post Office, although to get there you'd need to go back "
		+ "to the main road. "
		+ "To the south you see the Adventurer's Guild. To the "
		+ "east, the path continues.\n");

	add_AG("north", "The roof hangs over the path some, creating "
		+ "shade.");
	add_item("post office", "The Post Office is where you can send letters "
		+ "to other denziens of the Donut.\n");
	add_item("roof", "It looks like a pretty standard roof. It hangs over "
		+ "the path, adding shade.\n");
	add_item( ({"shade", "shadows"}), "Thanks to the roof, you can walk "
		+ "here without being baked by the sun.\n");
    add_exit(ROAD_DIR + "broad06", "west");
	add_exit(ROAD_DIR + "path2", "east");

    reset_shire_room();
}



void
reset_shire_room()
{

}

