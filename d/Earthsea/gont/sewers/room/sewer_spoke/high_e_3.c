/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_e_3.c
 *
 *  This is a spoke room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * East cliff of the Armed Cliffs. -- East Gont
 * /d/Earthsea/gont/gont_city/rooms/e_cliff4
 *
 * What is above and nearby?
 * North: Harbour Captain's office. (harbour_capt)
 * South: x (x)
 * East: harbour (x)
 * West: cliffs? (x)
 * 
 *
 * Stream flow from high_e_4 only
 * Aeg MAR 2021
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

    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_MAIN_TUNNEL + "low_east_4", "northwest", 0);
    add_exit(SEWER_SPOKE + "high_e_4", "east", 0);


    
    set_flow_speed(5.0);
    set_downstream_dir("northwest");    
}   /* create_sewer_room */
    