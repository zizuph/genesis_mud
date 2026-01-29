/*
 * /w/petros/sparkle/library/room/clubs_craft_guilds.c
 *
 * South wing in the Genesis Library containing books about
 * the Clubs and Craft Guilds of Genesis.
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
public void             create_library_stack();
public void             init();
public void             reset_room();
public string           sparkle_short();
public varargs string   sparkle_long();

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
 * Function name:       create_library_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_library_stack()
{
    // Library Initialization Section
    create_genesis_library( ({ "clubs", "crafts", "general" }), 
                            "clubscraftsguild" );
 
    // Room Item Section                              
    add_item( ({ "intersection", "section" }),
                  "This intersection allows for more display space than "
                + "is normally seen in other stacks. You see an increased "
                + "number of displays here.\n");

    add_item( ({ "west wing", "west corridor" }),
                  "The west wing goes up north from here.\n");

    add_item( ({ "south wing", "south corridor" }),
                  "The south wing continues to the east from here.\n");

    add_item( ({ "wing", "wings", "corridor", "corridors" }),
                  "Would you like to examine the west wing or the south "
                + "wing?\n");

    add_item( ({ "artwork", "stunning artwork" }),
                  "Artwork lines the walls and spaces in every area of "
                + "the library as far as you can see in both directions. "
                + "You see paintings, tapestries, and other types of "
                + "displays.\n");

    add_item( ({ "scent" }),
                  "Scent is something that is very hard to examine. You "
                + "do however, spot some herbal life in a case that you "
                + "suspect the scent comes from.\n");

    add_item( ({ "displays", "display" }),
                  "Each area of the stacks seems to have its own type of "
                + "display that shows off the content of the books in the "
                + "area. Looking around, you see a shimmering case, a "
                + "large anchor, and a mithril necklace. There are also "
                + "other trinkets, no doubt from the various clubs of "
                + "the land.\n");

    add_item( ({ "shimmering case", "case", "small red berry", "berry",
                 "herb", "whitehorn", "small white horn", "white horn",
                 "small horn", "horn", "small berry" }),
                  "Inside the shimmering case, you see lots of different "
                + "kinds of plant life. One of the more prominent herbs "
                + "that you see is a small red berry, known as suranie, a "
                + "very good herb for restoring mental vitality. Another "
                + "looks like a small white horn, called whitehorn, which "
                + "is one of the best healing herbs in the land. This "
                + "display was clearly placed here to honour the "
                + "Gardeners of Gont."
                + "\n");

    add_item( ({ "suranie" }),
                 "A small red berry that is known for its particularly "
               + "good ability to restore mental vitality."
               + "\n");                

    add_item( ({ "whitehorn" }),
                 "A small white horn, often found in the lands of "
               + "Terel, which is known to be one of the best healing "
               + "herbs in the land."
               + "\n");                

    add_item( ({ "large anchor", "words", "anchor" }),
                  "This anchor sits prominently in the center of the "
                + "room, forcing passerbys to have to walk carefully "
                + "around it. Engraved along the side are the words, \""
                + "Mariners of Genesis\".\n");

    add_item( ({ "necklace", "mithril necklace", "information" }),
                  "An amazingly crafted necklace hangs inside one of "
                + "the displays. You recognize it as one that is "
                + "normally seen worn by some of the best Smiths in the "
                + "land. The information in the display seems to "
                + "indicate that these smiths can be found in Bree.\n");
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "layman_guilds", "north", 0);
    add_exit(LIBRARY_ROOM_DIR + "poetry", "east", 0);
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

/*
 * Function name:        sparkle_short
 * Description  :        provide a short description for locations
 *                       in the City of Sparkle
 * Deturns      :        string -- the short description
 */
public string
sparkle_short()
{
    return "Stacks - clubs and craft guilds";
} // sparkle_short


/*
 * function name:        sparkle_long
 * description  :        provides a long descriptions for locations
 *                       in the city of Sparkle
 * returns      :        the room description
 */
public varargs string
sparkle_long()
{
    return "The intersection between the west wing and the south wing "
           + "of the Library presents an unobstructed view down both "
           + "corridors. The sheer number of books on the shelves in "
           + "addition to the stunning artwork that accompanies each room "
           + "in the stacks is a wonder to behold. Your nose catches the "
           + "scent of something unique as you stand in this room. "
           + "Looking at the various displays here, you realize that "
           + "this section contains books about various craft guilds "
           + "found in Genesis as well as numerous clubs that are "
           + "available for one to join."
           + "\n\n";
} // sparkle_long
