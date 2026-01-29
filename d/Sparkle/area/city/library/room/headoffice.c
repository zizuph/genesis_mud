/*
 * /w/petros/sparkle/library/room/headoffice.c
 *
 * Office of the Head Librarian of Genesis Library, Nikolon
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
    set_short("Office of the Head Librarian");
    set_long("The inside of the Office of the Head Librarian is nothing "
           + "like how one would imagine it to be. Given the "
           + "librarian's job is to maintain order among the volumes of "
           + "books from all over Genesis, it would seem likely that the "
           + "office of such an important person would be orderly. There "
           + "is anything but order here, however. Papers litter the "
           + "floor and the desk. The walls are bare except for a few "
           + "loosely attached maps that are not hung properly. The owner "
           + "of this office must have a lot on his mind. To the "
           + "north you see the doorway back to the waiting room."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "office" }),
                 "This office is a complete mess, with mostly bare walls "
               + "and a bunch of papers littering the room."
               + "\n");

    add_item( ({ "papers", "paper" }),
                 "There's too much of a mess to really tell what the "
               + "contents of the papers say."
               + "\n");

    add_item( ({ "walls", "wall" }),
                 "You see a few maps on the walls, but not much else."
               + "\n");

    add_item( ({ "maps", "map", "loosely attached maps" }),
                 "The maps on the walls are loosely attached, with some "
               + "barely hanging onto the walls. They appear to be maps "
               + "of different lands in the Donut."
               + "\n");

    add_item( ({ "doorway" }),
                 "The doorway to the north is the way out of the office."
               + "\n");

    add_item( ({ "desk" }),
                 "The desk is supposed to be the workspace of the Head "
               + "Librarian, but with the amount of papers on it, you "
               + "doubt that anyone could do any work here."
               + "\n");
                                                                                          
    // Properties Section
    add_prop(ROOM_I_INSIDE, 1);
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "bedroom", "south", 0);

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
    if(!objectp(present("_head_office_door_in")))
    {
        clone_object(LIBRARY_OBJ_DIR 
                     + "head_office_door_i")->move(this_object());
    }
} // reset_room

