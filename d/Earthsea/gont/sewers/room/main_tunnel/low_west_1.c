/*
 *  /d/Earthsea/gont/sewers/room/main_tunnel/low_west_1.c
 *
 *  This is a main tunnel room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "At the West Pier." -- Southwest Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road14
 *
 * What is above and nearby?
 * NORTH: West side of harbour (../gont_city/rooms/city_street/city_road9) 
 * SOUTH: Below a high cliff (city_road15) 
 * EAST: Old Calia pier (/d/Earthsea/ships/calia_line/west_pier1) 
 * WEST: Street northeast of a large park (city_road13)
 *
 * Fork: Stream flow comes in from the main tunnel and from high_southwest
 * rooms
 * 
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "main_tunnel_dam")

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

    set_long_extra("A tributary tunnel of the sewers branches west, into "
              + "the darkness. The main tunnel runs upstream to the north "
              + "and downstream to the south.");
   
    /* Room Item Section */                           
    add_item( ({ "tributary", "tributary tunnel", "spoke", "branch" }),
             "Sewer systems are networks that move waste from high points "
           + "to the low point where it is expunged into the environment. "
           + "This tributary tunnel collects waste from part of the city "
           + "and dumps it into the main tunnel, here.\n");
           
    add_tell("Through the small pipes, you can hear the hustle and bustle "
           + "of the city.\n");
    add_tell("Through the small pipes, you can hear the muffled echo of "
           + "seagulls calling.\n");
           
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_MAIN_TUNNEL + "low_west_2", "north", 0);
    add_exit(SEWER_SPOKE + "high_sw_1", "west", 0);
	add_exit(SEWER_MAIN_TUNNEL + "main_tunnel_dam", "south", 0);  
    
    set_flow_speed(5.0);
	set_downstream_dir("south");    
}   /* create_sewer_room */
	