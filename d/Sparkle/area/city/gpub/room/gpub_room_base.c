/*
 *  /d/Sparkle/area/city/gpub/room/gpub_room_base.c
 *
 *  Base file for all GPub rooms
 *
 *  
 *  
 *  
 *  
 */

#pragma strict_types



// Includes
#include "../../defs.h"
#include "/d/Sparkle/sys/defs.h"
#include <stdproperties.h>

// Defines

// Inheritance
inherit SPARKLE_ROOM_BASE;

// Global Variables

// Prototypes
nomask void        create_sparkle();
public void        create_gpub_room();
public void        init();




/*
 * Function name:        create_sparkle
 * Descriptionn :        dummy routine for inheriting files
 */
nomask void
create_sparkle()
{
    // Call the base creation function for Gayryn's Pub
    create_gpub_room();

    // Add the try_items after create_gpub_room so that it will not
    // replace the items added by subclasses
    try_item( ({"pub", "gayryns pub", "gayryn's pub" }),
				"You are in a very old pub with a history dating all the " +
				"way back to the early days when Sparkle was founded." +
				"\n");
               
    try_item( ({"floor", "marble floor", "floors", "marble floors", "ground" }),
				"The floor in the pub is rather worn down even though a resent " +
				"atempt has been done to freshen it up." +
				"\n");
    
    try_item( ({"wall", "walls", "inner wall", "inner walls" }),
				"The inner walls cosist of a lower dark wood veneer and " +
				"a red velvet tapestry covering the upper part."
				"\n");
               


    // Properties Section
	add_prop(ROOM_I_INSIDE, 1);
    
	// add_prop(ROOM_S_MAP_FILE, "gpub_map.txt");
    
}




/*
 * Function name:        create_gpub_room
 * Descriptionn :        Constructor function that will be masked in
 *                       the explicit room file
 */
public void
create_gpub_room() { }





/*
 * Function name:        init
 * Description  :        Called when the room initates
 */
public void
init()
{
    ::init();
}





