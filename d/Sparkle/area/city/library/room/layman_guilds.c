/*
 * /w/petros/sparkle/library/room/layman_guilds.c
 *
 * West wing of the Genesis Library with books containing
 * information about layman guilds
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
public void             create_library_stack();

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
    create_genesis_library( ({ "fighter", "spellcaster", "stealth", 
                               "general" }), 
                            "laymanguilds" );
    
    // Descriptions Section
    set_short("Stacks - layman guilds");
    set_long("A soft light illuminates the stacks here in the west wing "
           + "of the library. Among the books, you spot references to "
           + "layman guilds that can be found in Genesis. It is certainly "
           + "no surprise then, that you find depictions of these "
           + "organizations in the tapestries that are hung on both the "
           + "east and west walls. It is mostly silent here, except for "
           + "the occasional sound of a page turning by one of the "
           + "patrons. The stacks continue to the north and the south."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "light", "soft light" }),
                  "The light spreads out from the torches above "
                + "and gives off sufficient reading light for the "
                + "patrons here.\n");

    add_item( ({ "west wing", "wing" }),
                  "You are standing in the west wing where books on "
                + "the different organizations in the realm are stored. "
                + "Tapestries hang on the walls here.\n");

    add_item( ({ "tapestries", "walls", "wall", "east wall", 
                 "west wall" }),
                  "Besides the bookshelves along the wall, there are "
                + "tapestries hanging on the walls. You note three "
                + "tapestries that draw the most attention: a brown, "
                + "a red, and an orange one.\n");

    add_item( ({ "tapestry", "first tapestry", "brown tapestry" }),
                  "The most detailed of the tapestry depicts a warrior "
                + "of great reknown, Xorfin. Yet it was not Xorfin's "
                + "days as a warrior that fills up the most space nor "
                + "the most prominent place. Instead, it was Xorfin's "
                + "Cadet School of Gelan, the most prestigious school "
                + "for young adventurers to learn the arts of battle.\n");

    add_item( ({ "second tapestry", "red tapestry" }),
                  "Musical instruments, and images of the Muses cover the "
                + "second tapestry. They are the images of members of the "
                + "August Order of the Minstrels, powerful musicians whose "
                + "music can shape and affect the world around them.\n");

    add_item( ({ "third tapestry", "orange tapestry" }),
                  "Crouched figures hiding in the shadows, sneaking "
                + "around, and cutting purses in the tapestry make it "
                + "very clear that these are Thieves of the Cabal of "
                + "Hiddukel. Wary the traveller that comes across one "
                + "of these professionals.\n");

    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "occ_guilds", "north", 0);
    add_exit(LIBRARY_ROOM_DIR + "clubs_craft_guilds", "south", 0);
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

