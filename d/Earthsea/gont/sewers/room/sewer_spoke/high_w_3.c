/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_w_3.c
 *
 *  This is a spoke room of the sewers of Gont. 
 *
 * According to the current Gont map:
 * What should be above me? 
 * Uncoded wealthy manor  -- West Gont -- possibility for expansion
 * perhaps only accessable by the sewers?
 * 
 *
 * What is above and nearby?
 * NORTH: x (x)
 * SOUTH: x (x)
 * EAST: x (x) 
 * WEST: x (x)
 * SE: Below two high towers. (city_road7)
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
#define            FALL_LOCATION (SEWER_SPOKE + "high_w_2")

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
    set_short("Upper tunnel");
	
    set_long_extra("Only pipes flow "
        + "into this area and one could assume that the small pipes lead "
        + "to individual building drain pipes and such. Larger pipes "
        + "might connect to other tunnels, through flooding basins, but "
        + "that cannot be confirmed from here.");
		   
    /* Room Item Section */                           

    /* City noises */
    add_tell("Through the small pipes, you can hear the hustle and bustle "
    + "of the city.\n");
    
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_w_2", "southeast", 0);
    
    set_flow_speed(5.0);
	set_downstream_dir("southeast");    
}   /* create_sewer_room */
	