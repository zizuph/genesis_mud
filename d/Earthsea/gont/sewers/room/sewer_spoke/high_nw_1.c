/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_nw_1.c
 *
 *  This is a spoke room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "Between wooden buildings." -- Northwest Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road11
 *
 * What is above and nearby?
 * North: Road crossings. (city_road5)
 * South: Warehouse (x)
 * East: building (x)
 * West: building (x)
 * SE: Northwest side of the harbour. (city_road10)
 *
 * Stream flow comes in from the high_nw rooms
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "low_west_3")

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
       
    /* Room Item Section */

    
        /* city noises */
    add_tell("Through the small pipes, you can hear the hustle and bustle "
    + "of the city.\n");
    
        /* warehouse noises */
    add_tell("Through the small pipes, you can hear workers grumbling "
    + "about hauling heavy loads.\n");    
    
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_MAIN_TUNNEL + "low_west_3", "southeast", 0);
    add_exit(SEWER_SPOKE + "high_nw_2", "northwest", 0);
    
    set_flow_speed(5.0);
	set_downstream_dir("southeast");    
}   /* create_sewer_room */
	