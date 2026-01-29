/*
 * Central Stairwell in the Basement
 * 
 * Created by Jaacar, July 2016
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes

// Global Variables

public void
create_temple_room()
{
    set_short("Basement Central Stairwell");
    set_long("Compared to the complex elegance of the main floor of the Elemental "
             + "Temple, you are quite surprised to find that this floor is "
             + "actually quite simple. The walls do not seem to be made of the "
             + "same grey rock material and there are no signs of the crystalline "
             + "veins that you have seen elsewhere in the Temple.\n\n");

    try_item( ({ "walls", "wall" }),
              "The walls are made of wood panels, lacquered over with a glossy paint. "
              + "Painted upon them are beautiful murals that depict the Elementals "
              + "interacting with their creation.\n");
     
    try_item( ({ "paint", "glossy paint", "mural", "murals", "beautiful murals",
                    "elementals", "creation", "painting" }),
        "There are murals on every available surface of this stairwell. The "
        + "Elementals are shown in various states of action.\n");
        
    try_item( ({ "staircase", "stairwell", "steps" }),
        "The black stairwell appears to have been grown rather than been "
      + "carved out of the inside of the pillar. Block wooden steps lead up to the "
      + "first floor of the Temple.\n");
    
    add_exit(ELEMENTALIST_TEMPLE + "middle2", "up");
//    add_exit(ELEMENTALIST_TEMPLE + "vault", "north");
    add_exit(ELEMENTALIST_TEMPLE + "hall3", "south");
}

public void
init()
{
    ::init();
}
