/*
 * /w/petros/sparkle/library/room/nw_stairwell.c
 *
 * Northwest Stairwell of the Genesis Library
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
    set_short("First floor northwest stairwell");
    set_long("The absence of books in this stairwell makes this a rather "
           + "unique place in the Library. Rather than leaving it to be "
           + "the dull place that most stairwells are, someone has taken "
           + "care to decorate it properly. Artwork lines the walls, each "
           + "telling the story of Sparkle in one way or another. Natural "
           + "light flows down from windows high above you. To the east, "
           + "you see the north wing of the Library."
           + "\n\n");

    add_item( ({ "stairwell", "northwest stairwell" }),
                  "You are in the northwest stairwell. There are stairs "
                + "here that lead you up to the second floor of the "
                + "Genesis Library."
                + "\n");      

    add_item( ({ "windows", "window", "light", "natural light" }),
                  "Sparkle light is pervasive even indoors because of "
                + "the windows high up above you. They let in the natural "
                + "light and it flows down from the dome-like ceiling "
                + "above and provides the artwork here with enough light "
                + "for your viewing enjoyment. You cannot see out the "
                + "windows from down here."
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
                + "on the walls, evenly spaced."
                + "\n");      

    add_item( ({ "paintings" }),
                  "The paintings are evenly spaced on the walls, "
                + "allowing one to stand before each one and admire "
                + "them. You see three particular paintings that catch "
                + "your interest as they describe the history of "
                + "this great city of Sparkle."
                + "\n");      

    add_item( ({ "first painting" }),
                  "You spend a few moments before the first painting. You "
                + "observe that the first painting depicts the creation of "
                + "the donut, with images of Lars and other Immortals. "
                + "You note the presence of Fatty and Styles as they "
                + "together form the very beginnings of Sparkle."
                + "\n");      
    
    add_item( ({ "second painting" }),
                  "You walk over to the second painting and stand before "
                + "it. The second painting shows the town of Sparkle, "
                + "before it became the city that it is today. Some parts "
                + "of the painting are recognizable, while for other "
                + "images you can only marvel at the history displayed "
                + "before you."
                + "\n");      

    add_item( ({ "third painting" }),
                  "You walk carefully over to the third painting and "
                + "observe it for a few minutes. It details the "
                + "construction of modern Sparkle, including the "
                + "construction of this Library and the Sparkle Branch of "
                + "the Gnomes of Genesis."
                + "\n");      

    // Room Item Section                              

    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "racial_guilds", "east", 0);
    add_exit(LIBRARY_ROOM_DIR + "upper_nw_stairwell", "up", 0);
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

