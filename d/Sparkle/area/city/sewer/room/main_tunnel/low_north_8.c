/*
 *  /d/Sparkle/area/city/sewer/room/main_tunnel/low_north_8.c
 *
 *  This is a main tunnel room of the sewers of Sparkle.
 *
 * Upstream: low_north_9.c
 * Downstream: low_north_7.c
 * 
 * According to Styles' map:
 * What should be above me? 
 * /d/Sparkle/area/city/rooms/streets/center_f.c
 *
 * What is above and nearby?
 * Bank of Sparkle (ne)
 * Tower of Realms (se)
 * Church of Sparkle (n)
 * Genesis Library (s)
 * Adventure Guild (sw)
 *
 * Noteworthy exits:
 * Squeeze through gap--> access to library basement
 *
 * Aeg
 */
#pragma strict_types

/* Includes */
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include "../defs.h"

/* Defines */

/* Inheritance */
inherit MAIN_TUNNEL_BASE;

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
    set_long_extra("A tunnel extends east and west with classic "
            + "architecture. The walls and ceiling are crafted "
            + "with a post and lintel architecture style and are "
            + "in imperfect shape. The floor is made of stone and is "
            + "covered with downward flowing sewage. A rusty, blackened "
            + "metal grate spans a hole in the stone "
            + "of the southern tunnel wall.");
    /* Room Item Section */                           

    add_item( ({ "metal", "blackened metal", "grate" }),
        "The metal must be iron, due to the distinctive rusting that erodes "
      + "the grate. The frame is connected to the wall with four screws in "
      + "each corner. The whole image appears to be the gap-toothed grin of "
      + "a battle scarred warrior.\n");
      
    add_item( ({ "frame", "corner", "each corner" }),
        "The frame of the grate is rectangular and fixed to the wall with "
      + "iron screws. It precariously attached.\n");

    add_item( ({ "screw", "screws" }),
        "These pin the metal grate to the hole in the wall.\n");
    
    add_item( ({ "tooth", "teeth", "grin", "dirty grin", "gap-toothed grin", 
                "battle-scarred warrior", "warrior", "image" }),
        "Well, these aren't real teeth, nor a real grin, nor a warrior; "
      + "they are iron bars "
      + "that span the opening in the southern wall. They exist to keep "
      + "people from entering the southern tunnel. Rust covers every inch of "
      + "them.\n");
      
    add_item( ({ "bar", "bars" }),
        "They are iron bars that span the opening in the southern wall. They "
      + "exist to keep people from entering the southern tunnel. They are "
      + "covered in rust.\n");
      
    add_item( ({ "rust", "erosion", "distinctive rust" }),
        "The iron bars are constantly exposed to a dank environment, of "
      + "course they are going to be rusted. Due to this rust, some of "
      + "the bars are broken and missing; it might be possible to squeeze "
      + "through the gaps.\n");
      
    add_item( ({ "gaps", "gaps", "opening", "hole" }),
        "The gap in the metal grate might be large enough for you to "
      + "squeeze through.\n");
      

    /* Properties Section */

    add_tell("A rat crawls through a metal grate in the south wall, "
      + "falls into the water, and drowns.\nThe corpse of the rat floats "
      + "downstream.\n");
      
    add_tell("You hear muffled explosion through the northern tunnel wall. "
      + "It appears to come from the northeast, though the echos make the "
      + "epicenter difficult to pinpoint.\n");
      
    /* Cmd items */
    add_cmd_item(({"gap", "through the gap", "through gap",
                   "through the gaps", "in gap" }),
        "squeeze", "@@squeeze");

    /* Exits Section 
     *      Note: There is an exit to 
     *      /d/Sparkle/area/city/sewer/room/sewer6
     *      via squeeze()
     */
    add_exit(SEWER_MAIN_TUNNEL + "low_north_9", "west", 0);  
    add_exit(SEWER_MAIN_TUNNEL + "low_north_7", "east", 0);  
    
    set_flow_speed(5.0);
	set_downstream_dir("east"); 
	
}   /* create_sewer_room */

/* 
 * Function name:       squeeze
 * Description  :       This function performs 
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public int
squeeze()
{
    write("You squeeze through the gap in the bars of the grate.\n");
    this_player()->move_living("through the gap in the grate", 
               "/d/Sparkle/area/city/sewer/room/sewer6" );
    return 1;
} /* squeeze */
