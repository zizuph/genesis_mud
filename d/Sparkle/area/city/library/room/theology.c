/*
 * /w/petros/sparkle/library/room/theology.c
 *
 * North Hallway leading east in the Genesis Library. Contains
 * books on Theology.
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
inherit (LIBRARY_ROOM_DIR + "library_base");

// Global Variables

// Prototypes
public void             init();
public void             create_library_stack();

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
 * Function name:       create_library_stack
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_library_stack()
{
    // Library Initialization Section
    create_genesis_library( ({ "theology" }), 
                            "" );

    // Descriptions Section
    set_short("Stacks - theology");
    set_long("Holy symbols and depictions of deities are prominently "
           + "featured in the displays found here. That this particular "
           + "area is the intersection between the east and south wings "
           + "of the library only serves to provide extra space to put "
           + "more displays. You cannot tell whether a couple of patrons here "
           + "are reading, asleep, or simply praying. The books here are "
           + "clearly books that will help one to better understand the "
           + "theology of a big place like the Donut of Genesis. You can "
           + "find your way either north or west from here."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "symbol", "holy symbol", "symbols", "holy symbols",
                 "cases", "display cases", "religious symbols",
                 "religious symbol", "paraphernalia",
                 "religious paraphernalia", "displays" }),
                  "Religious symbols and paraphernalia have been placed "
                + "carefully in separate display cases. Among them you "
                + "find a mandala, a black medallion, a celtic cross, a "
                + "pentagram, and a flowing white cloak. You feel great "
                + "power emanating from the objects that you see here."
                + "\n");

    add_item( ({ "intersection" }),
                  "This particular area intersects the east and south "
                + "wings of the Genesis Library."
                + "\n");

    add_item( ({ "east wing" }),
                  "The east wing continues to the north from here."
                + "\n");

    add_item( ({ "south wing" }),
                  "The south wing continues to the west from here."
                + "\n");

    add_item( ({ "mandala" }),
                  "The mandala is a small, black, round symbol. It is the "
                + "holy symbol carried by those of the Spirit Circle of "
                + "Psuchae."
                + "\n");                                

    add_item( ({ "black medallion", "medallion" }),
                  "The black medallion bears the symbols of a five-headed "
                + "dragon. It is the religious symbol that represents the "
                + "Queen of Darkness, Takhisis."
                + "\n");              
                
    add_item( ({ "celtic cross", "cross" }),
                  "You see a cross that has a circle around where "
                + "the two perpendicular parts cross. It is clearly "
                + "a celtic cross, like the ones found in the "
                + "beautiful land of Khalakhor."
                + "\n");      

    add_item( ({ "pentagram" }),
                  "The pentagram is one of the most easily recognizable "
                + "spiritual symbols. It is also used in many rituals "
                + "involving the spirits, and often used by the more "
                + "dark arts of Necromancy."
                + "\n");      

    add_item( ({ "flowing white cloak", "white cloak", "flowing cloak" }),
                  "The white cloak is elegant and pure white. Just "
                + "looking at it can make one's eyes hurt, almost like "
                + "looking directly into a light. You recognize the "
                + "cloak as being that worn by the Heralds of the Valar, "
                + "in Middle Earth."
                + "\n");      
                
    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "map_reference", "north", 0);
    add_exit(LIBRARY_ROOM_DIR + "poetry", "west", 0);
} // create_room

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

