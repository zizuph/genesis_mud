/*
 * hall1.c
 *
 * Skippern 20(c)02
 *
 * A large hall inside a noble house.
 *
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

#include <stdproperties.h>

void
create_inside()
{
    set_short("a large hall");
    set_long("This large hall divides the mansion into two wings, the main wing " +
		"to the northeast with the living room and the social area of the mansion, " +
		"and the kitchen and servants quarters to the southwest. A large arched " +
		"doorway leads northwest into the garden. At the end off the hall a door " +
		"leads southeast into a quiet lounge. The hall itself is tall, with " +
		"red drapes hanging from the ceiling covering the granite walls behind.\n");
	add_item( ({ "wall", "walls", "drape", "drapes", "red drape", "red drapes" }),
		"Red drapes hangs from the ceiling covering the sturdy granite walls behind " +
		"them. The drapes seems to be made of some sturdy, but finly woven material, " +
		"with fine gold-thread embroideries along the edges.\n");
	
	
    add_exit(DOL_HILLS + "j-11/garden1", "northwest", 0, 1); // garden
    add_exit(DOL_HILLS + "j-11/hall2", "northeast", 0, 1); // living room
    add_exit(DOL_HILLS + "j-11/hall3", "southeast", 0, 1); //lounge
    add_exit(DOL_HILLS + "j-11/hall4", "southwest", 0, 1); // kitchen

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
}


