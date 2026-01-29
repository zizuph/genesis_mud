/*
 * Recode Discussion Room
 *
 * This room will house a board where members of the Spirit Circle and the
 * Elemental Worshippers can discuss the recode that is happening in
 * 2016.
 *
 * Created by Petros, February 2010
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
    set_short("Discussion chamber");
    set_long("This chamber is rather bare, reflecting the nature of "
        + "the Creation before it has been filled. Here, members of "
        + "the Spirit Circle and the Elemental Worshippers can discuss "
        + "ideas regarding the upcoming guild recode."        
        + "\n\n");

    try_item( ({ "walls", "wall", "glowing walls", "glowing wall", "panels",
                    "broad panels" }),
              "The walls of this room are composed of very broad panels of "
              + "dark mahogany inlaid with numerous filaments of a sparkling "
              + "white crystalline material. The walls simply glow with a "
              + "somber soft glow.\n");

    try_item( ({ "wood", "mahogany", "crystalline", "filaments", "glow" }),
              "The sparkling white crystalline filaments interacting with the "
              + "dark colors of the mahogany wood come together bringing forth "
              + "a glow that seems to stem from deep within the very panels "
              + "themselves. The glow is continious and serves as constant "
              + "source of light through all hours for the day.\n");

    add_exit(ELEMENTALIST_TEMPLE + "stairwell2", "east"); 

    load_board();
}

public void
load_board()
{
    object bb;
    seteuid(getuid(this_object()));
    bb = clone_object(ELEMENTALIST_OBJS + "discuss_board");
    bb->move(this_object());
}
 
public int 
query_prevent_snoop()
{
    return 1;
}
 
