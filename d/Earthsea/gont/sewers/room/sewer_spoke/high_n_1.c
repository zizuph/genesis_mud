/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_n_1.c
 *
 *  This is a spoke room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "The Seaside Tavern." -- North Gont
 * /d/Earthsea/gont/gont_city/rooms/tavern
 *
 * What is above and nearby?
 * North: Bedroom (/d/Earthsea/gont/gont_city/rooms/pub_sleep_room)
 * South: North of a long pier. (city_road17)
 * East: building (x)
 * West: building (x)
 * 
 *
 * Fork: Stream flow comes in from the a split in the high_n rooms
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "low_center")

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
    set_long_extra("Two tributary tunnels of the sewers branch out to the "
          + "north and northeast, while the main tunnel runs downstream to "
          + "the south. Loud voices and laughter can be heard in this "
          + "part of the tunnel. The noises themselves are not loud,"
          + "but through all of the muffling and echoing of the pipes "
          + "you can deduce that they are loud at the source. The smell "
          + "of the part of the tunnel is different. It could not be "
          + "described as better or worse, necessarily, just different.");
   
    /* Room Item Section */    
    
    add_item( ({ "smell", "smells", "stench" }),
          "The smell of the tunnel is different here. It could be described "
          + "as being more complex. Aromas of cooked meat and the smell of "
          + "spices are "
          + "mixed with the common stench of the sewers. This olfactory "
          + "mixture is more of an abomination than anything else.\n");
    add_item( ({ "tributary", "tributary tunnel", "branch tunnel", 
                 "branch" }),
          "The upstream branches extend into the darkness. You notice that "
          + "the current is slightly slower upstream.\n");  
          
        /* Harbor noises */   
    add_tell("Through the small pipes, you can hear the hustle and bustle "
        + "of the city.\n");
    add_tell("Through the small pipes, you can hear the muffled echo of "
        + "seagulls calling.\n");

        /* pub noises */
    add_tell("Through the small pipes, you hear drunken sailors singing "
        + "songs.\n");
    add_tell("Through the small pipes, the sound of breaking glass can "
        + "be heard.\n");
    add_tell("Through the small pipes, you hear a man say, 'Order up!'\n");
    add_tell("Through the small pipes, a loud crash can be heard.\n");    
    
    /* Properties Section */
    
    /* Exits Section */

    add_exit(SEWER_SPOKE + "high_n_2", "north", 0);
    add_exit(SEWER_SPOKE + "high_n_5", "northeast", 0);
    add_exit(SEWER_MAIN_TUNNEL + "low_center", "south", 0);
    
    set_flow_speed(5.0);
    set_downstream_dir("south");    
}   /* create_sewer_room */
    