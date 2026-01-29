/*
 *  /w/petros/sparkle/library/room/library_room_base.c
 *
 *  This will be the base file for every library room
 *
 *  Created April 2008, by Petros
 */
#pragma strict_types

#include "defs.h"
#include "/d/Sparkle/sys/defs.h"
#include <stdproperties.h>

inherit SPARKLE_ROOM_BASE;

/* Global Variables */

/* Prototypes */
nomask void        create_sparkle();
public void        create_library_room();
public void        init();

/*
 * Function name:        create_sparkle
 * Descriptionn :        dummy routine for inheriting files
 */
nomask void
create_sparkle()
{
    // Call the base creation function for libraries
    create_library_room();

    // Add the try_items after create_library_room so that it will not
    // replace the items added by subclasses
    try_item( ({ "library", "genesis library" }),
                 "You stand in the Genesis Library of Sparkle, one of "
               + "the bedrocks of the City of Sparkle."
               + "\n");
               
    try_item( ({ "floor", "marble floor", "floors", "marble floors",
                 "ground" }),
                 "The floor in the library is made of marble tiles that "
               + "gleam and shine. You can even see your reflection "
               + "in the marble."
               + "\n");
    
    try_item( ({ "wall", "walls" }),
                 "The walls of the Genesis Library are made of marble. "
               + "Here you see torches evenly spaced placed rather "
               + "high hanging from the walls."
               + "\n");
               
    try_item( ({ "torch", "torches" }),
                 "The torches on the walls provide ample reading light."
               + "\n");
    
    try_item( ({ "fire", "burning fire" }),
                 "Each torch is lit by burning fire. You find it rather "
               + "strange to see such fires so close to books."
               + "\n");

    try_item( ({ "ceiling", "patterns", "square recessed patterns",
                 "recessed patterns", "pattern", "square recessed pattern",
                 "recessed pattern" }),
                 "The ceiling of the Library is very high, giving a vast "
               + "sense of space. The ceiling has square recessed "
               + "patterns on it, much like what you would see at a "
               + "museum."
               + "\n");
    
    try_item( ({ "marble", "stone" }),
                 "The Genesis Library is constructed completed out of "
               + "well hewn marble. The marble is of the highest "
               + "quality, and must have taken quite a lot of work to "
               + "build such a massive building out of it."
               + "\n");
               
    try_item( ({ "room", "library" }),
                 "You are standing in one of the rooms of the carefully "
               + "constructed and very beautiful Genesis Library of "
               + "Sparkle."
               + "\n");

    try_item( ({ "library stack", "stack" }),
                 "Do you mean stacks?"
               + "\n");

    try_item( ({ "library stacks", "stacks" }),
                 "The library stacks are filled with books. Everywhere "
               + "you look, you only see more and more books."
               + "\n");

    // Properties Section
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "library_map.txt");
    
} // create_sparkle

/*
 * Function name:        create_library_room
 * Descriptionn :        dummy routine for inheriting files
 */
public void
create_library_room()
{
    
} // create_library_room


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
} // init
