/*
 * /d/Sparkle/area/city/gpub/room/template.c
 *
 * Part of Gayryn's Prodigal Pub in Sparkle.
 * 
 * This is just a template for individual rooms.
 * 
 * 
 *  
 */

#pragma strict_types



// Includes
#include <macros.h>
#include <stdproperties.h>
#include "../../defs.h"

// Defines

// Inheritance
inherit GPUB_ROOM_BASE;

// Global Variables

// Prototypes
public void             init();




/* 
 * Function name:       init
 * Description  :       Set specific add actions to this room.
 * Arguments    :       None
 * Returns      :       Nothing
 */
public void 
init() 
{
    ::init();  
} // init




/* 
 * Function name:       create_gpub_room
 * Description  :       Set specific descriptory data for this room.
 *                      Called from the gpub_room_base.c
 * Arguments    :       None
 * Returns      :       Nothing
 */
public void
create_gpub_room()
{
    // Descriptions Section
    set_short("");
    set_long(""
           + "");
 

	// Room Item Section                              
    add_item( ({"item name1", "item name2" }),
				"Item desc" +
				"\n");

                                           
    // Properties Section
    // (ROOM_I_INSIDE is added in the gpub_room_base.c file)

    

	// Exits Section
//    add_exit(GPUB_ROOM_DIR + "filename", "north", 0);

} 




/*
 * Function name:        reset_room
 * Description  :        Called when the room is reset.
 * Arguments    :        None
 * Returns      :        Nothing
 */
public void
reset_room()
{
} // reset_room





/*
 * Function name:        
 * Description  :        
 * Arguments    :        None
 * Returns      :        Nothing
 */