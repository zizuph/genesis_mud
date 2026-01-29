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
        + "pervades most of the Temple. A pair of braziers to the west and "
        + "east provides enough lighting to see that a small fresco on "
        + "the eastern wall is the only decoration in this room. The "
        + "hallway continues to the north and southeast from here.\n\n");

    try_item( ({ "brazier", "braziers", "platinum brazier", "platinum braziers",
        "tripod", "tripods", "bowl", "circular bowl" }),
        "The pair of braziers give off just enough lighting to see that they "
      + "are medium platinum-coated tripods with a circular bowl fastened on "
      + "top. In the bowls, flickering flames light the room, casting ever "
      + "dancing shadows everywhere.\n");

    try_item( ({ "shadows", "shadow", "dancingi shadows", "dancing shadow" }),
        "As you look upon the shadows you are reminded of a dance of life and "
      + "vitality, images of the earth and all living things growing from the "
      + "soil fill your mind.\n");

    try_item( ({ "fresco", "frescoes", "landscape", "landscapes" }),
        "This fresco depicts two landscapes. One of the landscapes is a "
      + "massive plateau ridged with mountains all caught in a massive "
      + "upheaval. In the depiction, the ground has been cracked by "
      + "tremendous fissures while mountains crumble and ravines of "
      + "destruction plummet toward a small village caught in the middle. "
      + "The other landscape reveals a verdant growing forest, sprouting "
      + "fauna and plant life in a variety few could possibly imagine. "
      + "Nearby the forest one can see villagers harvesting fields full of "
      + "crops.\n");
                    
    add_exit(ELEMENTALIST_TEMPLE + "middle6", "north");     
    add_exit(ELEMENTALIST_TEMPLE + "middle10", "southeast");
}
