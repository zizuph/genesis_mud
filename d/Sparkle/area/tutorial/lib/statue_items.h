/*
 *  /d/Sparkle/area/tutorial/lib/statue_items.h
 *
 *  This is a module that adds some common items to the statue rooms
 *  of the pre-creation.
 *
 *  Created March 2006, by Cooper Sherry (Gorboth) 
 */
#pragma strict_types

/*
 * Function name:        add_statue_items
 * Description  :        do this in a separate funciton so we can just
 *                       inherit this code and do it in similar rooms.
 */
public void
add_statue_items()
{
    add_item( ({ "here", "room", "area", "small room", "alcove" }), long);
    add_item( ({ "wall", "walls", "north wall", "northern wall",
                 "west wall", "western wall", "east wall", "eastern wall",
                 "south wall", "southern wall" }),
        "The walls of this room are fairly plain. An exit leads through"
      + " one of them back to the main chamber.\n");
    add_item( ({ "door", "doorway", "exit", "chamber", "main chamber",
                 "large chamber", "larger chamber" }),
        "A larger chamber is visible through a doorway here.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor here is bare, and looks freshly swept.\n");
    add_item( ({ "ceiling", "roof", "up" }),
        "The ceiling of this room is fairly plain. There are no"
      + " visible beams or framing.\n");
} /* add_statue_items */
