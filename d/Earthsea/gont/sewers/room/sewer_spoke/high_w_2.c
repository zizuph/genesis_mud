/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_w_2.c
 *
 *  This is a spoke room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "Below two high towers." -- Southwest Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road7
 *
 * What is above and nearby?
 * NORTH: wealthy home (x)
 * SOUTH: Travellers guild (x)
 * EAST: buildings (x) 
 * WEST: wealthy home (x)
 * SE: Three way crossing outside a large garden. (city_road8)
 * NE Street between large stone buildings. (city_road6)
 *
 * Stream flow comes in from one source
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_SPOKE + "high_w_1")

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
    
    /* park noises */
    add_tell("Through the small pipes, songbirds can be barely heard "
    + "chirping and singing.\n");
    
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_w_1", "southeast", 0);
    add_exit(SEWER_SPOKE + "high_w_3", "northwest", 0);
    
    set_flow_speed(5.0);
	set_downstream_dir("southeast");    
}   /* create_sewer_room */
	