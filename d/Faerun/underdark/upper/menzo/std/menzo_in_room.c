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


inherit (FAERUN_STD + "faerun_room");

/*
 * Function name: create_menzo_room
 * Description  : Construct a room for Menzoberranzan
 */
void create_menzo_in_room()
{
}

/*
 * Function name: create_underdark_room
 * Description  : Construct a room for the underdark
 */
nomask void create_faerun_room(void)
{
	// Set defaults
	set_faerun_area("menzoberranzan");
    set_faerun_level(FL_UNDERDARK);

    add_prop(ROOM_I_LIGHT, 0);
    INDOORS;
    


	// Call the constructor
	create_menzo_in_room();
}
