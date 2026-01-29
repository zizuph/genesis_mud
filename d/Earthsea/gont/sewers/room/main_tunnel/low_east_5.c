/*
 *  /d/Earthsea/gont/sewers/room/main_tunnel/low_east_5.c
 *
 *  This is a main tunnel room of the sewers of Gont. This is the highest
 *  most spot on the lower main tunnel. The smugglers warehouse is nearby.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "East part of the harbour area." -- Southeast Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road33
 *
 * What is above and nearby?
 * NORTH: Just east of a long pier. (city_road33) 
 * SOUTH: Southeast corner of the harbour area. (city_road22) 
 * EAST: Inside a warehouse. (warehouse4) 
 * WEST: Water (x)
 * 
 *
 *  
 * Stream flow comes in from the high_se spoke only
 *  Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "low_east_4")

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

    set_long_extra("This is the highest most spot of the main tunnel. "
            + "The current flows downstream to the north and a tributary "
            + "pours sewage in from the southeast.");
   
    /* Room Item Section */
                         
    add_item( ({ "tributary", "tributary tunnel", "spoke", "branch" }),
             "Sewer systems are networks that move waste from high points "
           + "to the low point where it is expunged into the environment. "
           + "This tributary tunnel collects waste from part of the city "
           + "and dumps it into the main tunnel, here.\n");

        /* Smuggler noises */           
    add_tell("Through one of the small pipes, you can hear someone yelling "
           + "at someone else about a late shipment.\n");       
    add_tell("Through one of the small pipes, you can hear someone talking "
           + "about the importance of secrecy.\n");
           
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
    add_exit(SEWER_MAIN_TUNNEL + "low_east_4", "north", 0);
    add_exit(SEWER_SPOKE + "high_se_1", "southeast", 0);  
    
    set_flow_speed(5.0);
    set_downstream_dir("north");    
}   /* create_sewer_room */
    