/*
 *  /d/Gondor/rohan/isengard/storerm2.c
 *
 *  Opus, June 1997
 *
 *  Copyright   1997 by Robert Miller
 *
 *  Modification log:
 */

#pragma strict_types

#include "defs.h"

inherit ISEN_ROOM;

#include <macros.h>
#include <stdproperties.h>

//Prototypes
string  getmold();


public void
create_isengard()
{
    set_short("inside the second storeroom");
    set_long(BSN(
       "This is a large rooms that seems to be used for storage. Some "+
       "crates are stacked throughout the room. The only way out of the "+
       "room is back into the guardroom from which you came."));
        
    add_item( ({"wall", "walls"}), BSN(
        "The walls are damp to the touch and are giving off a foul odor. "+ 
        "Mold can be seen growing on the walls in various places."));
    add_item( "ceiling", BSN(
        "High above, the ceiling of the room is perfectly "+
        "rounded making it difficult to tell where the ceiling ends and "+
        "the wall begins."));
    add_item( ({"floor", "ground"}), BSN(
        "From taking a closer look at the strong, black rock that makes up "+
        "this entire area, its hard to imagine how the floor could have "+
        "been so smoothly carved."));
    add_item( ({"crate", "crates"}), BSN(
        "A number of crates have been stacked into groups throughout "+
        "the room. They have been labeled as either food, equipment, or "+
        "tobacco. In the far corner a few empty crates can be spotted."));
    add_item( ({"empty crate", "empty crates"}), BSN(
        "These wooden crates have been tossed into a corner so they are "+
        "out of the way. The tops have been torn off and the contents "+
        "emptied to be used elsewhere."));
    add_item( ({"food", "food crates", "food crate"}), BSN(
        "These crates are stacked together against a wall and have the "+
        "word food stenciled across the front and top."));
    add_item( ({"supplies", "supplies crate", "supply crate", "supply crates"}), BSN(
        "These crates have been neatly stacked against a far wall and have "+ 
        "been marked supplies on the front and top."));
    add_item( ({"tobacco", "tobacco crate", "tobacco crates"}), BSN(
        "These crates have been stacked closest to the door leading back "+
        "into the guardroom for easiest accessability. The crates have been "+
        "clearly marked tobacco on the front and top."));
    add_item( ({"odor", "foul odor", "smell", "awful smell"}), BSN(
        "This sickening stench fills the room from the mold growing on "+ 
        "the walls.")); 
    add_item( ({"mold", "green mold"}), BSN(
        "Various parts of every wall has some of this green, fuzzy mold "+
        "growing upon it. The mold lets off an awful smell."));
    add_item( ({"rock", "black rock", "smooth rock",
        "smooth black rock"}), BSN(
            "This strange black rock makes up the entire area. It has been "+
            "constructed to create this room."));
    add_cmd_item( "wall", ({"touch", "feel"}), BSN(
       "You notice that the walls are very damp to the touch and have bits "+
       "of mold growing in various spots on them."));
    add_cmd_item( "mold", ({"touch", "feel"}), BSN(
        "The mold feels slimy and a bit sticky."));
    add_cmd_item( "mold", ({"get", "take"}), getmold());
    
    add_exit(ISEN_DIR + "guardrm", "northeast", 0);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
}

string
getmold()
{
   // will be used in the near future so that a player can actually
   // get the mold from the walls.

}

