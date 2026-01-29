/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_n_3.c
 *
 *  This is a spoke room of the sewers of Gont. This room contains an access
 *  point to the surface.
 *
 * According to the current Gont map:
 * What should be above me? 
 * First floor of guard tower. -- North Gont
 * /d/Earthsea/gont/gont_city/rooms/guard_tower1
 *
 * What is above and nearby?
 * North: Narrow cobbled street. (../city_street/city_road1a)
 * South: uncoded guard tower (x)
 * East: uncoded guard tower (x)
 * West: uncoded guard tower (x)
 * NW, NE, SW, SE: First floor guard rooms (tower_nw1, etc.)
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
#define            FALL_LOCATION (SEWER_SPOKE + "high_n_2")

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
    
    set_long_extra("Above, a small vent, or "
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

        /* guard noises */
    add_tell("Through the small pipes, you hear the sounds of boots "
        + "marching.\n");
    add_tell("Through the small pipes, you hear someone say, 'Patrol duty "
        + "again? The captain has it out for me!'\n");
    add_tell("Through the small pipes, you hear someone ask, 'Did you hear "
        + "that Jensin lost his helmet? Ooooooooh, the captain is gonna be "
        + "mad!'\n");
    add_tell("The loud clanging sound of a sword dropping to the ground can "
        + "be heard from above.\n");

    
        
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_n_4", "north", 0);
    add_exit(SEWER_SPOKE + "high_n_2", "south", 0);
    
    add_cmd_item(({ "ladder" }), "climb", "@@climb");
    
    set_flow_speed(5.0);
    set_downstream_dir("south");    
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
