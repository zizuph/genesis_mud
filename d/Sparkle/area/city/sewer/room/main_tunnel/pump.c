/*
 *  /d/Sparkle/area/city/sewer/room/main_tunnel/pump.c
 *
 *  This is the water pump of the sewers of Sparkle. It is the
 *  final destination of any sliding items from the main tunnels.
 *
 * According to Styles' map:
 * What should be above me? 
 * For rent building
 *
 * What is above and nearby?
 * Temple of granite (east)
 * Road w/ river (west)
 * Road (north)
 * River (south)
 *
 *  Aeg
 */
#pragma strict_types

/* Includes */
#include "../defs.h"

#include <macros.h>
#include <stdproperties.h>

/* Defines */

/* Inheritance */
inherit MAIN_TUNNEL_BASE;

/* Global Variables */

/* Prototypes */
public void             init();
public void             create_tunnel_room();

/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();  
} // init

/* 
 * Function name:       create_tunnel_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_tunnel_room()
{
    // Descriptions Section
    set_short("Pump room");
    set_long("Pump room long."
           + "\n\n");
    set_long_extra("This is the pump station for the sewers of Sparkle."
		+ "");
		   
    // Room Item Section                              
                              
    // Properties Section

    
    // Exits Section
    
    add_exit(SEWER_MAIN_TUNNEL + "low_north_1", "northeast", 0);
    add_exit(SEWER_MAIN_TUNNEL + "low_northwest_1", "northwest", 0);
    add_exit(SEWER_MAIN_TUNNEL + "low_west_1", "west", 0);
    
    set_downstream_enabled(0); // pump is the end, so no need to stream downwards.
} // create_sewer_room
