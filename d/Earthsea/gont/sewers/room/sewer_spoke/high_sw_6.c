/*
 *  /d/Earthsea/gont/sewers/room/sewer_spoke/high_sw_6.c
 *
 *  This is a spoke room of the sewers of Gont. There is an access point to
 *  the surface here. This will need to be for HUMANS ONLY (Traveller's guild)
 *
 * According to the current Gont map:
 * What should be above me? 
 * Cellar (travellers guild) -- Southwest Gont
 * /d/Earthsea/travellers/room/cellar
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
#define            FALL_LOCATION (SEWER_SPOKE + "high_sw_5")

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
        + "that cannot be confirmed from here. Above, a small vent, or "
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

        /* Travellers' noises */
    add_tell("Through the small grate, you can hear people talking "
        + "about their adventures.\n");

    add_tell("Through the small grate, you can hear the shuffle of "
        + "feet and general carrying-on.\n");   
    
    add_tell("You hear, through the small grate, two people arguing "
        + "about routes and maps.\n"); 

    add_tell("You hear a hushed voice through the small grate say, "
        + "'Soft wood? Yeah, the ocean waves soften wood.' A second voice "
        + "says, 'Good, I'll check the beach at low tide.'\n");

    add_tell("Through the small grate, you hear a heavy cask or barrel "
        + "sliding across the floor.\n");       
    
    /* Properties Section */
    
    /* Exits Section */
    add_exit(SEWER_SPOKE + "high_sw_5", "southeast", 0);
    
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
    write("You climb up the rusty iron ladder.\n");
/* not yet-- unopened area -- HUMANS ONLY
 *    this_player()->move_living("climbing the rusty iron ladder",
 *      "/d/Earthsea/travellers/room/cellar" );
        
/* not yet, but remember to add a room tell to the cellar
 * for arriving people */
        
    return 1;
}
