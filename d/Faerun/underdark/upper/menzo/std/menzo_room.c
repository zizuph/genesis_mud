/*
 *  faerun/underdark/upper/menzo/std/menzo_room.c
 *
 *  Standard room for Menzoberranzan and surroundings
 *
 *  Created by Wully, 12-2-2004
 *  Light added, 26-9-2005, Midnight
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>


inherit (UNDER_STD_DIR + "room");

/*
 * Function name: create_menzo_room
 * Description  : Construct a room for Menzoberranzan
 */
void create_menzo_room()
{
}

/*
 * Function name: create_underdark_room
 * Description  : Construct a room for the underdark
 */
nomask void create_upperdark_room()
{
	// Set defaults
	set_faerun_area("menzoberranzan");
    add_prop(ROOM_I_LIGHT, 0);
    set_faerun_level(FL_UNDERDARK);
    INDOORS;


	// Call the constructor
	create_menzo_room();
}
