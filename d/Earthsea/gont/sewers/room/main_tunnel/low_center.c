/*
 *  /d/Earthsea/gont/sewers/room/main_tunnel/low_center.c
 *
 *  This is a main tunnel room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "North of a long pier." -- Central Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road17
 *
 * What is above and nearby?
 * NORTH: The Seaside Tavern (tavern) 
 * SOUTH: Halfway out on the North Pier. (north_pier1) 
 * EAST: Northeast part of the harbour. (city_road18) 
 * WEST: Northwest part of the harbour. (city_road16)
 * NW: 
 * SW: 
 *
 *  
 * Fork: Stream flow comes in from the main tunnel and from high_north rooms
 *  Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "low_west_4")

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

    set_long_extra("A tributary tunnel of the sewers branches north, "
              + "into the darkness. "
              + "The main tunnel runs upstream to the east "
              + "and downstream to the west.");
   
    /* Room Item Section */                           
    add_item( ({ "tributary", "tributary tunnel", "spoke", "branch" }),
             "Sewer systems are networks that move waste from high points "
           + "to the low point where it is expunged into the environment. "
           + "This tributary tunnel collects waste from part of the city "
           + "and dumps it into the main tunnel, here.\n");
           
        /* Harbor noises */   
    add_tell("Through the small pipes, you can hear the hustle and bustle "
           + "of the city.\n");
    add_tell("Through the small pipes, you can hear the muffled echo of "
           + "seagulls calling.\n");

        /* pub noises */
    add_tell("Through the small pipes, you hear drunken sailors singing "
           + "songs.\n");  
    
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_n_1", "north", 0);
	add_exit(SEWER_MAIN_TUNNEL + "low_east_1", "east", 0);
    add_exit(SEWER_MAIN_TUNNEL + "low_west_4", "west", 0);
  
    
    set_flow_speed(5.0);
	set_downstream_dir("west");    
}   /* create_sewer_room */
	