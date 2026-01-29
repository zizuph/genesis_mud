/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_sw_4.c
 *
 *  This is a spoke room of the sewers of Gont.
 *
 * According to the current Gont map:
 * What should be above me? 
 * Gardener's guildshed -- Southwest Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/x
 *
 * What is above and nearby?
 * x (east)
 * x (north)
 * x (south)
 * Garden wall room (west)
 *
 * This is one of the origin rooms of the stream flow
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_SPOKE + "high_sw_3")

/* Inheritance */
inherit SPOKE_TUNNEL_BASE;


/* Global Variables */

/* Prototypes */
public void             init();
public void             create_tunnel_room();
public int              pull();

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
    set_short("Upper tunnel");
    
    set_long_extra("The tips of roots can be seen piercing through cracks "
        + "in the ceiling and upper walls. The lower walls are damp with "
        + "a variety of slimy mosses and algae. This appears to be the end "
        + "of an upper spoke of the sewer tunnels. Only pipes flow "
        + "into this area and one could assume that the small pipes lead "
        + "to individual building drain pipes and such. Larger pipes "
        + "might connect to other tunnels, through flooding basins, but "
        + "that cannot be confirmed from here.");
           
    /* Room Item Section */                           
    add_item( ({ "tips", "tips of roots", "roots", "trees", "plants",
                 "root" }),
          "Roots finding their way into tunnels, such as this, is not rare. "
        + "What makes this different is that the roots seem to have "
        + "no interest in actually reaching this fetid water. It is "
        + "almost as if they entered the tunnel, assessed the situation, "
        + "and were unable to beat a hasty retreat. The tree, unable to "
        + "withdraw, merely left the vestigial roots, which now dangle "
        + "in your face.\n");
        
    add_item( ({ "cracks", "crack", "upper walls" }),
          "A quick assessment of the cracks caused by the roots leads "
        + "you to believe that you are not in danger. It does not appear "
        + "that the structural integrity of the tunnel is compromised "
        + "by the invading roots.\n");
        
    add_item( ({ "lower walls", "lower wall" }),
          "The lower walls are damp from their close proximity to to the "
        + "flowing sewage. Any splash or disruption that you cause in "
        + "the water results in the subterranian mosses and algae getting "
        + "wet. Unlike the roots above, these plants seem to flourish with "
        + "the sewage.\n");
        
    add_item( ({ "mosses", "algae" }),
          "Algae and a variety of mosses populate the lower sections of "
        + "the walls. They are slimy to the touch.\n");

        /* park noises */
    add_tell("Through the small pipes, songbirds can be barely heard "
        + "chirping and singing.\n");
    
        
    add_cmd_item(({"roots"}), "pull", "@@pull");
    add_cmd_item(({"roots"}), "tug", "@@pull");
    
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_sw_3", "southeast", 0);
    
    set_flow_speed(5.0);
	set_downstream_dir("southeast");    
}   /* create_sewer_room */
	
/* 
 * Function name:       pull
 * Description  :       This allows for players to pull or tug
 * Returns      :       1 - allow tugging, 0 - nothing
 */
public int
pull()
{
    write("You tug on some of the larger roots. They seem firmly "
	       + "attached to the trees above.\n");
    say(QCTNAME(this_player()) + " tugs at some of the larger roots "
    + "that pierce through the ceiling.\n");
    return 1;
}
