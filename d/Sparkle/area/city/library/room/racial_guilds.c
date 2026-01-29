/*
 * /w/petros/sparkle/library/room/racial_guilds.c
 *
 * North wing of the Genesis Library with books containing
 * information about racial guilds in Genesis.
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines

// Inheritance
inherit (LIBRARY_ROOM_DIR + "library_base");

// Global Variables

// Prototypes
public void             init();

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
} // init

/* 
 * Function name:       create_library_stack
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_library_stack()
{
    // Library Initialization Section
    create_genesis_library( ({ "humans", "elves", "hobbits", "goblins", 
                      "dwarves", "gnomes", "special", "general" }), 
                      "racialguilds" );
    
    // Descriptions Section
    set_short("Stacks - racial guilds");
    set_long("In between individual bookshelves here are various "
           + "paintings of the different races of Genesis. A fleeting "
           + "look towards some of the books reveals that the stacks "
           + "here contain information about the different racial "
           + "guilds in Genesis. A soft light illuminates the "
           + "path that leads from the circulation desk east of you to "
           + "the stairwell to the west. Rows of books line the corridor "
           + "to the south of you."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "painting", "paintings", "art", "artwork" }),
                  "The paintings depict the different races "
                + "interacting with one another, some in peace, and "
                + "some at war. You are surprised by the minute details "
                + "that the artist went through to create this art.\n");

    add_item( ({ "details", "minute details" }),
                  "You look closely at the detailed depictions of the "
                + "various races. The painting looks so real that it "
                + "almost feels like the people are actually living "
                + "inside of the paintings.\n");

    add_item( ({ "light", "soft light" }),
                  "The light comes from the torches hanging loosely from "
                + "the walls.\n");

    add_item( ({ "torches", "torch" }),
                  "The torches are hanging loosely from the walls. You "
                + "think it is rather strange to have a burning fire so "
                + "near to flammable materials like the books here.\n");

    add_item( ({ "path", "north wing" }),
                  "The path you are on is part of the north wing of the "
                + "Genesis Library. It leads from the circulation desk "
                + "to the stairwell west of you.\n");
 
    add_item( ({ "corridor", "south corridor", "west wing" }),
                  "A corridor continues south from where you are. It "
                + "looks like the west wing of the Genesis Library, and "
                + "the number of books there is daunting.\n");
                
    add_item( ({ "desk", "circulation desk" }),
                  "The circulation desk is to your east.\n");
                
    add_item( ({ "stairwell" }),
                  "You see a set of stairs in the room to your west.\n");

    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "circulation", "east", 0);
    add_exit(LIBRARY_ROOM_DIR + "nw_stairwell", "west", 0);
    add_exit(LIBRARY_ROOM_DIR + "occ_guilds", "south", 0);
} // create_room

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
} // reset_room

