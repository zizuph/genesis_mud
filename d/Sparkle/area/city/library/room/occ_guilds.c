/*
 * /w/petros/sparkle/library/room/occ_guilds.c
 *
 * West wing of the Genesis Library containing books about
 * occupational guilds
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
                            "occguilds" );
                            
     // Descriptions Section
    set_short("Stacks - occupational guilds");
    set_long("Along with the shelving and the books that you normally "
           + "expect to see in the stacks, you see artifacts that you "
           + "recognize as belonging to different occupational guilds "
           + "found in Genesis. These artifacts are placed decoratively "
           + "wherever space is found, usually in between the shelves, or "
           + "hanging high above them. Looking at the books, you realize "
           + "that you can find information about these occupational "
           + "organizations among the books here. The stacks continue to "
           + "the north and to the south."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "artifacts", "artifact", "guild artifact",
                 "guild artifacts", "glass cases", "glass case",
                 "case", "cases" }),
                  "Glass cases line the walls and each one contains "
                + "an artifact from a particular guild. You recognize a "
                + "Knight artifact, a Morgul artifact, a Ranger artifact, "
                + "a Neidar artifact, and an Army of Darkness artifact "
                + "among the cases.\n");

    add_item( ({ "knight artifact", "hilt", "ceremonial sword",
                 "finely crafted sword", "sword",
                 "finely crafted ceremonial sword" }),
                  "In one of the glass cases in between the space of "
                + "two shelves, you see a finely crafted ceremonial "
                + "sword. Engraved along its hilt, you see the words "
                + "\"Est Sularus Oth Mithas\".\n");

    add_item( ({ "morgul artifact" }),
                  "You see a parchment of paper with scrawled writing. "
                + "It is difficult to make out most of the writing, but "
                + "you can understand this portion:\n\n"
                + "    \"...Nine for Mortal Men doomed to die..\"\n\n"
                + "You wonder what it could mean.\n");

    add_item( ({ "ranger artifact", "cloak", "green hooded cloak",
                 "hooded cloak" }),
                  "Hanging high above the shelving you see a green hooded "
                + "cloak encased in a glass case. The cloak looks like "
                + "the ones that are worn by the Rangers of Middle "
                + "Earth.\n");

    add_item( ({ "neidar artifact", "axe", "dwarven waraxe",
                 "two-handed waraxe", "two-handed dwarven waraxe" }),
                  "Displayed between the spaces of two shelves, a glass "
                + "case contains a two-handed dwarven waraxe. The axe is "
                + "clearly made in a way to be used easily by the Hill "
                + "Dwarves of Iron Delving known as the Neidar Clan.\n");

    add_item( ({ "army of darkness artifact", "army artifact",
                 "trophy belt", "belt", "skulls", "skull" }),
                  "A rather morbid artifact is displayed within the glass "
                + "case. You see a trophy belt with many skulls hanging "
                + "from it. This belt is a replica of one often seen "
                + "worn by the Ogres of Emerald, among those who are "
                + "known as the Army of Darkness.\n");
                                
    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "racial_guilds", "north", 0);
    add_exit(LIBRARY_ROOM_DIR + "layman_guilds", "south", 0);
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

