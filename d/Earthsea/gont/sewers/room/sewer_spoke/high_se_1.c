/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_se_1.c
 *
 *  This is a spoke room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "Narrow street." -- southeast Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road24
 *
 * What is above and nearby?
 * North: warehouse (x)
 * South: x (x)
 * East: wall? (x)
 * West: Southeast corner of the harbour area. (city_road22)
 *
 * Stream flow comes in from the high_se room
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "low_east_5")

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
    
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_MAIN_TUNNEL + "low_east_5", "northwest", 0);
    add_exit(SEWER_SPOKE + "high_se_2", "east", 0);
    
    set_flow_speed(5.0);
	set_downstream_dir("northwest");    
}   /* create_sewer_room */
	