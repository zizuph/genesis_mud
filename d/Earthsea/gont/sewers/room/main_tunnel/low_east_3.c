/*
 *  /d/Earthsea/gont/sewers/room/main_tunnel/low_east_3.c
 *
 *  This is a main tunnel room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "East part of the harbour." -- Southeast Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road20
 *
 * What is above and nearby?
 * NORTH: East part of the harbour. (city_road19) 
 * SOUTH: Just east of a long pier. (city_road21) 
 * EAST: Buildings (x) 
 * WEST: Water (x)
 *
 *  
 * Stream flow comes in from the main tunnel only
 *  Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "low_east_2")

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
    set_short("Lower main tunnel");

    set_long_extra("The main tunnel runs upstream to the south "
              + "and downstream to the north.");
   
    /* Room Item Section */
              
        /* Harbor noises */   
    add_tell("Through the small pipes, you can hear the hustle and bustle "
           + "of the city.\n");
    add_tell("Through the small pipes, you can hear the muffled echo of "
           + "seagulls calling.\n");
           
        /* warehouse noises */
    add_tell("Through the small pipes, you can hear workers grumbling "
           + "about hauling heavy loads.\n");
           
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_MAIN_TUNNEL + "low_east_2", "north", 0);
	add_exit(SEWER_MAIN_TUNNEL + "low_east_4", "south", 0);  
    
    set_flow_speed(5.0);
	set_downstream_dir("north");    
}   /* create_sewer_room */
	