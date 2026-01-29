/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_nw_2.c
 *
 *  This is a spoke room of the sewers of Gont. This room has access to the street.
 *
 * According to the current Gont map:
 * What should be above me? 
 * "Road crossings." -- Northwest Gont
 * /d/Earthsea/gont/gont_city/rooms/city_street/city_road5
 *
 * What is above and nearby?
 * North: Road crossings. (city_road5)
 * South: Between wooden buildings. (city_road11)
 * East: Yard outside a wooden house. (yard)
 * West: Street between large stone buildings. (city_road6)
 * NE: Narrow street in the living quarters.(city_road4)
 *
 * Fork: Stream flow comes in from the a split in the high_nw rooms
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_SPOKE + "high_nw_1")

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
        + "in two upstream directions. Above, a small manhole is positioned "
        + "directly above you on the ceiling. A slight movement of "
        + "fresh air can be felt through this part of the tunnel. "
        + "A rusty ladder extends from a small ledge to the manhole above.");
    
    /* Room Item Section */     
    
    add_item( ({ "ladder" }),
          "The ladder is old and is covered in rust. It appears to be "
        + "fully functional. You could climb it up to the manhole.\n");   

    add_item( ({ "ledge", "small ledge" }),
          "The rusty ladder is bolted to this ledge. It appears to be "
        + "made of stone and is slightly elevated out of the water.\n"); 
  
    add_item( ({ "rust" }),
          "After years of being bolted here, anything made of metal "
        + "would be this rusty.\n");      
          
    add_item( ({ "manhole" }),
          "Directly above you, a round manhole seperates the street above "
        + "from the sewer. It is made of metal and seems to be in decent "
        + "shape.\n");
          
    /* city noises */
    add_tell("Through the small pipes, you can hear the hustle and bustle "
        + "of the city.\n");
    
    /* Properties Section */
    
    /* Exits Section */

    add_exit(SEWER_SPOKE + "high_nw_5", "northeast", 0);
    add_exit(SEWER_SPOKE + "high_nw_1", "southeast", 0);
    add_exit(SEWER_SPOKE + "high_nw_3", "west", 0);
    
    add_cmd_item(({ "ladder" }), "climb", "@@climb");
    
    set_flow_speed(5.0);
    set_downstream_dir("southeast");    
}   /* create_sewer_room */

    
/* 
 * Function name:       climb
 * Description  :       Allows players to access the surface
 * Arguments    :       ladder
 * Returns      :       1 - success, 0 - failure
 */
public int
climb ()
{
    write("You climb up the rusty iron ladder and push your way through the "
        + "manhole.\n");
/* not yet-- unopened area
 *    this_player()->move_living("climbing the rusty iron ladder",
 *      "/d/Earthsea/gont/gont_city/rooms/city_street/city_road5" );
        
/* not yet, but remember to add a room tell to city_road5
 * for arriving people */
        
    return 1;
}
