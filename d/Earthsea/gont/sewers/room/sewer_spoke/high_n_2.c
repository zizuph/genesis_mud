/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_n_2.c
 *
 *  This is a spoke room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "Bedroom" -- North Gont
 * /d/Earthsea/gont/gont_city/rooms/pub_sleep_room
 *
 * What is above and nearby?
 * North: First floor of guard tower. (guard_tower1)
 * South: The Seaside Tavern. (tavern)
 * East: building (x)
 * West: building (x)
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
#define            FALL_LOCATION (SEWER_SPOKE + "high_n_1")

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

        /* bedroom noises */
    add_tell("You think you hear the faint sound of someone snoring.\n");
    add_tell("You hear the rhythmic thumping of something wooden hitting "
        + "something hard, such as stone.\n");
    add_tell("You hear a muffled scream through the small pipes.\n");
    
        /* pub noises */
    add_tell("Through the small pipes, you hear drunken sailors singing "
        + "songs.\n");     
        
    /* guard noises */
    add_tell("Through the small pipes, you hear the sounds of boots "
        + "marching.\n");
    
    /* Properties Section */
    
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_n_3", "north", 0);
    add_exit(SEWER_SPOKE + "high_n_1", "south", 0);

    
    set_flow_speed(5.0);
	set_downstream_dir("south");    
}   /* create_sewer_room */
	