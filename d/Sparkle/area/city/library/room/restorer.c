/*
 * /w/petros/sparkle/library/room/restorer.c
 *
 * Office of the Genesis Library Restorer
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
object gastol_obj;

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
    set_short("Office of the Restorer");
    set_long("A distasteful odor pervades this extremely messy office. "
           + "Books are strewn everywhere your eyes can see, and there "
           + "appears to be no semblance of order or organization. Among "
           + "the large stacks of books, you see a small work area where "
           + "some pages are laid out separately. Next to the "
           + "pages are some bottles of liquid and some brushes. You "
           + "gather that this is where old and ancient books are "
           + "restored from their years of decay."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "odor", "distasteful odor" }),
                  "You lift your nose to sniff the air, trying to "
                + "identify the source of the odor. You think it might "
                + "be coming from the bottles of liquid."
                + "\n");  

    add_item( ({ "office", "messy office" }),
                  "Given what you have seen elsewhere in the Library, "
                + "you are rather surprised to find how messy this office "
                + "is. You suppose that this office has probably never "
                + "been cleaned since the Library was built."
                + "\n");      
                            
    add_item( ({ "books", "book", "titles", "title", "piles", "pile" }),
                  "Many books lie in separate piles, some old, some new. "
                + "Most of the titles that you see are unrecognizable to "
                + "you. They must be truly ancient texts."
                + "\n");  

    add_item( ({ "books", "book", "titles", "title", "stacks",
                 "stack", "large stacks", "large stack" }),
                  "Many books lie in separate piles, some old, some new. "
                + "Most of the titles that you see are unrecognizable to "
                + "you. They must be truly ancient texts."
                + "\n"); 

    add_item( ({ "work area", "area", "small work area",
                 "small area" }),
                  "The work area is the only place in the room that is "
                + "not completely filled with books. A few pages lie "
                + "carefully placed next to what can only be standard "
                + "materials used by the restorer."
                + "\n"); 

    add_item( ({ "pages", "page", "word", "words" }),
                  "Some of the pages are still wet from the recent work "
                + "that was done on them. You can tell that some of the "
                + "words on the pages are starting to become clearer, "
                + "even as you are looking at them."
                + "\n"); 

    add_item( ({ "materials", "bottles of liquid", "liquid", "liquids",
                 "material", "bottle of liquid", "bottle", "bottles" }),
                  "You are fairly certain that the distasteful odor you "
                + "smelled coming in here originated from the liquids in "
                + "those bottles."
                + "\n"); 

    add_item( ({ "brush", "brushes" }),
                  "The brushes are still wet from recent use, most "
                + "likely with the liquid on the books."
                + "\n"); 
                                
    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "upper_nw_stairwell", "north", 0);

    setuid();
    seteuid(getuid());
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
    gastol_obj = find_living("gastol");
    if (!gastol_obj)
    {
        gastol_obj = clone_object(LIBRARY_NPC_DIR + "gastol");

        gastol_obj->move(this_object(), 1);
        tell_room(this_object(),
            "A stocky gnome busies himself, barely paying attention to "
          + "anything around him.\n");
    }
} // reset_room


