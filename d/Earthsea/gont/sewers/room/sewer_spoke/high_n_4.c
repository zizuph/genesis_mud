/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_n_4.c
 *
 *  This is a spoke room of the sewers of Gont. 
 *
 * According to the current Gont map:
 * What should be above me? 
 * Narrow cobbled street. -- North Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road1a
 *
 * What is above and nearby?
 * North: Narrow cobbled street. (city_road1)
 * South: First floor of guard tower. (guard_tower1)
 * East: uncoded guard tower (x)
 * West: uncoded guard tower (x)
 * 
 *
 * This is one of the origin rooms for the sewer flow.
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_SPOKE + "high_n_3")

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
    set_long_extra("This appears to be the end "
        + "of an upper spoke of the sewer tunnels. Only pipes flow "
        + "into this area. One could assume that the small pipes lead "
        + "to individual building drain pipes. Larger pipes "
        + "might connect to other tunnels, through flooding basins, but "
        + "that cannot be confirmed from here.");
        
    /* Room Item Section */                           

        /* city noises */
    add_tell("Through the small pipes, you can hear the hustle and bustle "
    + "of the city.\n");  

        /* guard noises */
    add_tell("Through the small pipes, you hear the sounds of boots "
    + "marching.\n");
    add_tell("The loud clanging sound of a sword dropping to the ground can "
    + "be heard from above.\n");
    
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_n_3", "south", 0);
    
    set_flow_speed(5.0);
    set_downstream_dir("south");    
}   /* create_sewer_room */
    
    