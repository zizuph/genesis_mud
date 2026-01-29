/*
 *  faerun/underdark/upper/menzo/std/menzo_room.c
 *
 *  Standard room for Menzoberranzan and surroundings
 *
 *  Created by Wully, 12-2-2004
 *  Light added, 26-9-2005, Midnight
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/std/room";

inherit FAERUN_ROOM_TELL_BASE;
inherit FAERUN_ITEM_BASE;


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
void create_room()
{
	// Set defaults
	set_faerun_area("menzoberranzan");
    set_faerun_level(FL_UNDERDARK);

    add_prop(ROOM_I_LIGHT, 0);
    INDOORS;

    add_item(({"corridor"}),
        "This dark wide corridor on the first floor. The walls and ceiling of the corridor are swallowed up by the shadows and lost in the darkness.\n");
      
    add_item(({"trail", "light","blood" }),
        "There's a trail of soft crimson red light in the middle of the floor. It runs like a trail of blood in the direction of the corridor.\n"); 
    add_item(({"wall", "walls"}),
        "The walls of the wide corridor are lost in the dark shadows.\n"); 
    add_item(({"floor","floors", "ground"}), 
        "The floor has been swept clean probably by one of the hardworking students. A soft, crimson, red light makes the shiny floor glow with a strange red hue near the trail of light in the middle of the floor.\n"); 
    add_item(({"ceiling", "up"}),
        "The ceiling is curved inward and is dark. It is lost in the shadows and darkness above.\n");
    


	// Call the constructor
	create_menzo_in_room();
}
