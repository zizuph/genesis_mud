/*
 * /w/petros/sparkle/library/room/bedroom.c
 *
 * Bedroom of the Head Librarian of Genesis Library, Nikolon
 *
 * Created by Petros, April 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines

// Inheritance
inherit LIBRARY_ROOM_BASE;

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
 * Function name:       create_library_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_library_room()
{
    // Descriptions Section
    set_short("Bedroom of the Head Librarian");
    set_long("A very simple bed sits against the wall on the south side of "
           + "this room. The room is dimly lit by a couple of torches. Not "
           + "much else occupies this room besides the bed, and even the "
           + "bed is quite bare. Whoever sleeps here must not spend very "
           + "much time here at all. The only way out is to the north, "
           + "back to the office."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "bed", "simple bed" }),
                 "The bed looks big enough to fit one person. The frame "
               + "is made of sturdy wood, and the mattress is very thin, "
               + "almost like a mat."
               + "\n");

    add_item( ({ "wall", "south wall" }),
                 "The only wall that is different from any of the other "
               + "walls is the south wall. It is not bare like the others "
               + "because it has a bed set against it."
               + "\n");

    add_item( ({ "torches", "torch", "light" }),
                 "The light here is very dim compared with the rest of "
               + "the Library. The torches provide just enough light "
               + "to see, but is probably not good for the eyes to read "
               + "under."
               + "\n");

    add_item( ({ "north", "office" }),
                 "The office is back to the north."
               + "\n");
                                                                                          
    // Properties Section
    add_prop(ROOM_I_INSIDE, 1);
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "headoffice", "north", 0);

} // create_library_room

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

