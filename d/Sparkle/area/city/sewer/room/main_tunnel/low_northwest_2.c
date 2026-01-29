/*
 *  /d/Sparkle/area/city/sewer/room/main_tunnel/low_northwest_2.c
 *
 *  This is a main tunnel room of the sewers of Sparkle.
 *
 * According to Styles' map:
 * What should be above me? 
 * A Road 
 *
 * What is above and nearby?
 * For rent (north, south)
 * Road (east, west, southeast)
 *
 *  Aeg
 */
#pragma strict_types

/* Includes */
#include "../defs.h"

#include <macros.h>
#include <language.h>
#include <stdproperties.h>

/* Inheritance */
inherit MAIN_TUNNEL_BASE;

/* Global Variables */

/* Prototypes */
public void             create_tunnel_room();

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
    add_exit(SEWER_MAIN_TUNNEL + "low_northwest_3", "west", 0);
    add_exit(SEWER_MAIN_TUNNEL + "low_northwest_1", "east", 0);
    
    set_flow_speed(5.0);
	set_downstream_dir("east"); 	
	
}   /* create_sewer_room */




