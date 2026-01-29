/*
 *  /d/Sparkle/area/city/sewer/room/main_tunnel/low_north_13.c
 *
 *  This is a main tunnel room of the sewers of Sparkle.
 *
 * Upstream: low_north_14.c
 * Downstream: low_north_12.c
 * 
 * According to Styles' map:
 * What should be above me? 
 * For Rent
 *
 * What is above and nearby?
 * Outside West Gate (ne)
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
    set_long("The subterranean environment, being poorly lit, does not "
           + "instantly paint a complete picture. Allowing your eyes to "
           + "adjust "
           + "to the scene, darkness yields and details are revealed. "
           + "A tunnel extends upward and downward with classic "
           + "architecture. The walls and ceiling are crafted "
           + "with a post and lintel architecture style and are "
           + "in imperfect shape. The floor is made of stone and is "
           + "covered with downward flowing sewage."
           + "\n\n");
 
    /* Room Item Section */                           

    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_MAIN_TUNNEL + "low_north_14", "north", 0);  
    add_exit(SEWER_MAIN_TUNNEL + "low_north_12", "east", 0); 
	
    set_flow_speed(5.0);
	set_downstream_dir("east"); 
    
}   /* create_sewer_room */
