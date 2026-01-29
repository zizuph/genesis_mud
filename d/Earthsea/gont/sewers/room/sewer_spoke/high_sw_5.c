/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_sw_5.c
 *
 *  This is a spoke room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "A silent street." -- Southwest Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road12
 *
 * What is above and nearby?
 * North: Travellers guild(x)
 * South: park(x)
 * East: x(x)
 * West: x(x)
 * SE: Street northeast of a large park. (city_road13)
 * NE: Three way crossing outside a large garden. (city_road8)
 *
 * Stream flow comes in from one upper room.
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_SPOKE + "high_sw_1")

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
    
/* This is the most boring room ever. Silent street above and nothing
 * noteworthy here. All details and sounds are inherited.
 */
	   
    /* Room Item Section */                           

    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_sw_6", "northwest", 0);
    add_exit(SEWER_SPOKE + "high_sw_1", "southeast", 0);

    
    set_flow_speed(5.0);
	set_downstream_dir("southeast");    
}   /* create_sewer_room */
	