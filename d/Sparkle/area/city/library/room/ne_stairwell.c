/*
 * /w/petros/sparkle/library/room/ne_stairwell.c
 *
 * Northeast stairwell in the Genesis Library. This room
 * is on the first floor, and leads up to Nikolon the Head
 * Librarian's main office.
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
    set_short("First floor northeast stairwell");
    set_long("There is nothing ordinary about this particular stairwell. "
           + "Whereas normal stairwells are boring by most standards, the "
           + "stairwell you currently occupy is more like a room in a "
           + "museum. The "
           + "staircase here is made of the same marble material that "
           + "most of the Library is constructed with. Even the railings "
           + "themselves are exquisite. Far above one can see natural "
           + "light flowing through the windows close to the dome-like "
           + "ceiling."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "stairwell", "northeast stairwell" }),
                  "You are in the northeast stairwell. There are stairs "
                + "here that lead you up to the second floor of the "
                + "Genesis Library."
                + "\n");      

    add_item( ({ "windows", "window", "light", "natural light" }),
                  "Sparkle light is pervasive even indoors because of "
                + "the windows high up above you. They let in the natural "
                + "light and it flows down and provides the artwork "
                + "here with enough light for enjoyment. You cannot "
                + "see out the windows from down here."
                + "\n");      

    add_item( ({ "ceiling", "dome-like ceiling" }),
                  "A mural with clouds and celestial objects has been "
                + "painted into the dome-like ceiling above."
                + "\n");      

    add_item( ({ "stairs", "stair", "staircase" }),
                  "The marble stairs are eloquently hewn, with each step "
                + "carved in a way that makes it easily accessible for "
                + "both small and big people. The railings of the stairs "
                + "look very expensive, but add a nice touch. The stairs "
                + "themselves wind in a circular fashion upwards towards "
                + "the second floor."
                + "\n");     
                
    add_item( ({ "railing", "railings" }),
                  "The railings are constructed of pure gold, and "
                + "are quite smooth and cool to the touch. The polishing "
                + "on it is exquisite and it is clear that it is "
                + "regularly cared for."
                + "\n");     

    add_item( ({ "artwork", "walls" }),
                  "The combination of the artwork along the walls and "
                + "the lack of books in the stairwell make this room "
                + "look more like a museum gallery than a part of the "
                + "Genesis Library. You see various paintings hanging "
                + "on the walls, evenly spaced. "
                + "\n");      

    add_item( ({ "paintings", "painting" }),
                  "The paintings are beautiful pieces of artwork, mostly "
                + "scenic impressionist ones. They show the beautiful "
                + "scenery around the continent of Sparkle, the center "
                + "of the Donut."
                + "\n");     
                
    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "guides_tutorials", "west", 0);
    add_exit(LIBRARY_ROOM_DIR + "upper_ne_stairwell", "up", 0);
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

