/*
 *  faerun/underdark/upper/menzo/tierbreche/example_room.c
 *
 *  This is an example how to use the entire inherit tree, once you end up
 *  here, every level below will have had it's own room inherit, allowing
 *  constumisations on each level, if you add something to the default room
 *  it will automatically be used in all the rooms below. Currently it is
 *  used to set the region and level variables
 *
 *  Created by Midnight, 13-2-2004
 */

#include "defs.h"
#include <terrain.h>

inherit P_MENZO_TIERBRECHE + "base_room";

/*
 * Function name: create_tierbreche_room
 * Description  : Construct a room for the Tier Breche part of Menzoberranzan
 */
void create_tierbreche_room()
{
	set_short("tierbreche room");
	set_long("An example of a Tier Breche room.\n");

	// No need to call the set_region etc here, because they are already set
	// by the inherit tree.

	// Do set the terrain properties, this is hard to do on a higher level
	// as all rooms have their own properties, i've picked a few properties
	// as an example
	set_terrain(TERRAIN_UNDERGROUND	| TERRAIN_COOL | TERRAIN_CLUTTER);
}