/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_sw_1.c
 *
 *  This is a spoke room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "Street northeast of a large park." -- Southwest Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road13.c
 *
 * What is above and nearby?
 * North: Earthsea Adventurers' Guild. (../gont_city/rooms/adv_guild)
 * South: x(x)
 * East: At the West Pier(../gont_city/rooms/city_street/city_road14)
 * West: x(x)
 * SW: Within a grove of oak trees(/d/Earthsea/gont/gont_city/rooms/park_1)
 * NW: A silent street. (../gont_city/rooms/city_street/city_road12)
 *
 * Fork: Stream flow comes in from the a split in the high_sw rooms
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "low_west_1")

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
    
    set_long_extra("The tunnel splits here, allowing for travel "
    + "in two upstream directions. Muffled sounds of the hustle and "
    + "bustle of the streets above can be heard through the small pipes.");

        /* street noises */
    add_tell("Through the small pipes, you hear drunken sailors singing "
    + "songs.\n"); 

        /* park noises */
    add_tell("Through the small pipes, songbirds can be barely heard "
    + "chirping and singing.\n");
    
    /* Room Item Section */                           

    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_sw_5", "northwest", 0);
    add_exit(SEWER_MAIN_TUNNEL + "low_west_1", "east", 0);
    add_exit(SEWER_SPOKE + "high_sw_2", "southwest", 0);

    
    set_flow_speed(5.0);
	set_downstream_dir("east");    
}   /* create_sewer_room */
	