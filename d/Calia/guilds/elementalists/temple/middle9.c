/*
 * Middle Circle of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes

public void
create_temple_room()
{
    set_short("Elemental Temple Middle Circle");
    set_long("This is one of the hallways in the middle circle of the "
        + "Elemental Temple of Calia. The walls are made from the typical "
        + "grey stone with the same crystalline veins and coating that "
        + "pervades most of the Temple. A pair of braziers to the northwest "
        + "and southeast provides enough lighting to see that a small fresco on "
        + "the eastern wall is the only decoration in this room. The "
        + "hallway continues to the north and southwest from here.\n\n");
                   
    try_item( ({ "brazier", "braziers", "copper brazier", "copper braziers",
        "tripod", "tripods", "bowl", "circular bowl" }),
        "The pair of braziers give off just enough lighting to see that they "
      + "are medium silver-coated tripods with a circular bowl fastened on "
      + "top. In the bowls, wavering flames cause shadows to dance "
      + "everywhere.\n");

    try_item( ({ "shadows", "shadow", "dancing shadows" }),
        "Looking at the dancing shadows brings upon a storm of rushing "
      + "sensations which overcome you. Pictures of endless sky and all "
      + "things living under it fill your mind.\n");

    try_item( ({ "fresco", "frescoes", "landscape", "landscapes", "land mass",
        "land masses", "small fresco", "small frescoes" }),
        "This fresco depicts two land masses. Gazing closer, you notice that "
      + "one is completely ablaze; every forest, village, and township "
      + "is lit up like a bonfire. Wildfires are spreading across the "
      + "landscape, consuming everything in a raging firestorm. The other "
      + "land mass is bathed in a warm somber light, and you notice a "
      + "small child smiling into the sky and basking in the glowing "
      + "life-giving warmth.\n");
      
    add_exit(ELEMENTALIST_TEMPLE + "middle7", "north");     
    add_exit(ELEMENTALIST_TEMPLE + "middle11", "southwest");
}
