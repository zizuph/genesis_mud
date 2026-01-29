/*
 * Elemental Clerics Discussion and Board Room
 *
 * This room will house a board where members of the Elemental
 * Clerics can discuss guild matters.
 *
 * Created by Petros, March 2014
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes
public void load_board();

// Global Variables

public void
create_temple_room()
{
    set_short("Elemental Clerics Board Room");
    set_long("This room is dedicated to the massive message board in the center of "
             + "this space. Compared to the rest of the Temple, this room is "
             + "quite spartan. The glowing walls certainly do a good job of "
             + "keeping the room well-lit so that members of the Elemental "
             + "Clerics can keep up to date with the latest discussions. To "
             + "the west is an archway that leads back to the central "
             + "stairwell.\n\n");

    try_item( ({ "walls", "wall", "glowing walls", "glowing wall", "panels",
                    "broad panels" }),
              "The walls of this room are composed of very broad panels of "
              + "dark mahogany inlaid with numerous filaments of a sparkling "
              + "white crystalline material. The walls simply glow with a "
              + "somber soft glow.\n");

    try_item( ({ "archway", "west", "stairwell", "central stairwell" }),
              "The archway leads west back to the central stairwell for the "
              + "third floor of this Temple.\n");

    try_item( ({ "wood", "mahogany", "crystalline", "filaments", "glow" }),
              "The sparkling white crystalline filaments interacting with the "
              + "dark colors of the mahogany wood come together bringing forth "
              + "a glow that seems to stem from deep within the very panels "
              + "themselves. The glow is continious and serves as constant "
              + "source of light through all hours for the day. Worshippers "
              + "can study the large board centered in the room at any time "
              + "with ease.\n");

    add_exit(ELEMENTALIST_TEMPLE + "stairwell3", "west"); 
    add_exit(ELEMENTALIST_TEMPLE + "ec_common", "common"); 

    load_board();
}

public void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(ELEMENTALIST_OBJS + "ec_board");
    bb->move(this_object());
}
 
public int 
query_prevent_snoop()
{
    return 1;
}
 
