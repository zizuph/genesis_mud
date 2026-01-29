/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_nw_4.c
 *
 *  This is a spoke room of the sewers of Gont. 
 *
 * According to the current Gont map:
 * What should be above me? 
 * Uncoded building  -- Northwest Gont
 * 
 *
 * What is above and nearby?
 * North: x (x)
 * South: x (x)
 * East: building (x)
 * West: building (x)
 *
 * This is one of the origin rooms for the sewer flow.
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_SPOKE + "high_nw_3")

/* Inheritance */
inherit SPOKE_TUNNEL_BASE;


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
} /* init */

/* 
 * Function name:       create_tunnel_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_tunnel_room()
{
    /* Descriptions Section */
	
    set_long_extra("This appears to be the end "
        + "of an upper spoke of the sewer tunnels. Only pipes flow "
        + "into this area. One could assume that the small pipes lead "
        + "to individual building drain pipes. Larger pipes "
        + "might connect to other tunnels, through flooding basins, but "
        + "that cannot be confirmed from here.");
		   
    /* Room Item Section */                           

    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_nw_3", "southeast", 0);
    
    set_flow_speed(5.0);
	set_downstream_dir("southeast");    
}   /* create_sewer_room */
	