/*
 *  /d/Sparkle/area/city/sewer/room/main_tunnel/low_north_1.c
 *
 *  This is a main tunnel room of the sewers of Sparkle.
 *
 * Upstream: low_north_2.c
 * Downstream: pump.c
 * 
 * According to Styles' map:
 * What should be above me? 
 * A Road
 *
 * What is above and nearby?
 * Outside South Gate
 * Rock Crevice Inn
 * Temple of Granite
 * Bundur's Shields and Axes
 *
 * Aeg
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "pump")

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
	
    set_long_extra("A tunnel extends upward and downward with a gradual "
           + "slope. The walls and ceiling are crafted "
           + "with a post and lintel architecture style and are "
           + "in imperfect shape. The floor is made of stone and is "
           + "covered with downward flowing sewage.");
		   
    /* Room Item Section */                           

    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_MAIN_TUNNEL + "low_north_2", "north", 0);
    add_exit(SEWER_MAIN_TUNNEL + "pump", "southwest", 0);  
    
    set_flow_speed(5.0);
	set_downstream_dir("southwest");    
}   /* create_sewer_room */
