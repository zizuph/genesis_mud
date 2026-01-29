/*
 *  /d/Earthsea/gont/sewers/room/main_tunnel/low_east_4.c
 *
 *  This is a main tunnel room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "Just east of a long pier. " -- Southeast Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road21
 *
 * What is above and nearby?
 * NORTH: East part of the harbour. (city_road20) 
 * SOUTH: East part of the harbour area. (city_road33) 
 * EAST: Harbour Captain's office.
 *          (/d/Earthsea/gont/gont_city/rooms/harbour_capt) 
 * WEST: Halfway out on the East Pier. 
 *          (/d/Earthsea/ships/avenir_line/east_pier1)
 * NE: Between tall wooden buildings. (city_road28)
 * SE: East cliff of the Armed Cliffs. 
 *          (/d/Earthsea/gont/gont_city/rooms/e_cliff4)
 *  
 * Fork: Stream flow comes in from the main tunnel and from high_e rooms
 *  Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "low_east_1")

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

    set_long_extra("Two tributary tunnels of the sewers branches out "
              + "to the east and southeast. "
              + "The main tunnel runs upstream to the south "
              + "and downstream to the north.");
   
    /* Room Item Section */                           
    add_item( ({ "tributary", "tributary tunnel", "spoke", "branch",
                 "tributaries", "tributary tunnels" }),
             "Sewer systems are networks that move waste from high points "
           + "to the low point where it is expunged into the environment. "
           + "This tributary tunnel collects waste from part of the city "
           + "and dumps it into the main tunnel, here.\n");
           
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
    add_exit(SEWER_MAIN_TUNNEL + "low_east_3", "north", 0);
    add_exit(SEWER_MAIN_TUNNEL + "low_east_5", "south", 0);  
    add_exit(SEWER_SPOKE + "high_e_1", "east", 0);
    add_exit(SEWER_SPOKE + "high_e_3", "southeast", 0);

    
    set_flow_speed(5.0);
    set_downstream_dir("north");    
    
}   /* create_sewer_room */
