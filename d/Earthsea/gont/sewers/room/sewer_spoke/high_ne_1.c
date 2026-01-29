/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_ne_1.c
 *
 *  This is a spoke room of the sewers of Gont. This room has an access point to
 *  a warehouse.
 *
 * According to the current Gont map:
 * What should be above me? 
 * Inside a warehouse. -- Northeast Gont
 * /d/Earthsea/gont/gont_city/rooms/warehouse3
 *
 * What is above and nearby?
 * North: x (x)
 * South: x (x)
 * East: Jail (jailhouse)
 * West: East part of the harbour. (city_road19)
 *
 * Fork: Stream flow comes in from the a split in the high_ne rooms
 * Aeg MAR 2021
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */
#define            FALL_LOCATION (SEWER_MAIN_TUNNEL + "low_east_2")

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
        + "east and northeast, while the main tunnel runs downstream to "
        + "the west. Above, a small vent, or "
        + "grate is positioned on the upper wall. A slight movement of "
        + "fresh air can be felt through this part of the tunnel. "
        + "A rusty ladder extends from a small ledge to a hatch above.");
   
    /* Room Item Section */                           

    add_item( ({ "ladder" }),
          "The ladder is old and is covered in rust. It appears to be "
        + "fully functional. You could climb it up to the hatch.\n");   

    add_item( ({ "ledge" }),
          "The rusty ladder is bolted to this ledge. It appears to be "
        + "made of stone and is slightly elevated out of the water.\n"); 
  
    add_item( ({ "rust" }),
          "After years of being bolted here, anything made of metal "
        + "would be this rusty.\n");  
        
    add_item( ({ "door", "hatch", "small hatch", "service hatch" }),
          "This door is small. It is more of a hatch than a proper door. "
        + "It appears to be made of wood and is painted black. A latch "
        + "is present, but no lock, nor keyhole, can be seen.\n");   
     
     add_item( ({ "grate", "vent", "small grate" }),
          "A small metal grate is positioned on the upper wall, next "
        + "to the service hatch.\n");   

        /* warehouse noises */
    add_tell("Through the small pipes, you can hear workers grumbling "
        + "about hauling heavy loads.\n");
    
        /* city noises */
    add_tell("Through the small pipes, you can hear the hustle and bustle "
        + "of the city.\n");

        /* Harbor noises */   
    add_tell("Through the small pipes, you can hear the muffled echo of "
        + "seagulls calling.\n");
    
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_ne_2", "northeast", 0);
    add_exit(SEWER_MAIN_TUNNEL + "low_east_2", "west", 0);
    add_exit(SEWER_SPOKE + "high_ne_4", "east", 0);
    
    add_cmd_item(({ "ladder" }), "climb", "@@climb");
    
    set_flow_speed(5.0);
    set_downstream_dir("west");    
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
    write("You climb up the rusty iron ladder and push through the "
          + "small hatch.\n");
/* not yet-- unopened area
 *    this_player()->move_living("climbing the rusty iron ladder and "
 *        + "pushing through the hatch",
 *      "/d/Earthsea/gont/gont_city/rooms/guard_tower1" );
        
/* not yet, but remember to add a room tell to the guard_tower1
 * for arriving people */
        
    return 1;
}