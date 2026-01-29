/*
 *  faerun/underdark/upper/menzo/tierbreche/base_room.c
 *
 *  The base room used in all the Tier Breche rooms.
 *
 *  Created by Midnight, 13-2-2004
 */

#include "defs.h"
#include <terrain.h>


inherit P_MENZO_STD + "menzo_room";

/*
 * Function name: create_tierbreche_room
 * Description  : Construct a room for the Tier Breche part of Menzoberranzan
 */
void create_tierbreche_room()
{
}

/*
 * Function name: create_menzo_room
 * Description  : Construct a room for Menzoberranzan
 */
nomask void create_menzo_room()
{
	set_faerun_location("tier breche");
	
	set_atmosphere_interval(2);
        add_atmosphere("You get the feeling someone is watching your every move.\n");
        add_atmosphere("You hear a wrathful roar nearby, followed by a chilling scream.\n");
        add_atmosphere("Water drips from above, but is instantly absorbed in the rock.\n");
        add_atmosphere("The soft magical light shifts slightly.\n");
        add_atmosphere("The air is filled with the echo of a dying scream.\n");
        set_terrain(TERRAIN_UNDERGROUND	| TERRAIN_COOL );

	// Construct the room
	create_tierbreche_room();
	
}