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
        + "pervades most of the Temple. The room is lit by a pair of "
        + "braziers, flames flickering shadows all over the place and "
        + "highlighting a large detailed fresco on the northern wall. The "
        + "hallway continues to the west and southeast from here.\n\n");

    try_item( ({ "brazier", "braziers", "copper brazier", "copper braziers",
        "tripod", "tripods", "bowl", "circular bowl" }),
        "The pair of braziers give off just enough lighting to see that they "
      + "are medium blackened gold-coated tripods with a circular bowl fastened on "
      + "top. In the bowls, sparking flames light the room, bathing the room "
      + "in a shower of shadow.\n");

    try_item( ({ "shadows", "shadow", "shower of shadow" }),
        "As you look upon the shadows you sense eternity touching you, "
      + "feelings of constant birth and death permeate you.\n");

    try_item( ({ "fresco", "frescoes", "humanoids", "humanoid", 
        "large fresco", "large frescoes", "northern wall" }),
        "This fresco depicts two humanoids. One of the humanoids is a small "
      + "newborn infant, held in a pair of shadowy hands. The other humanoid "
      + "is ancient, lying in a deathbed with gentle silvery hands reaching "
      + "towards it. Behind the humanoids, a faint pentacle shimmers a soft "
      + "ever present glow, illuminating their faces.\n");
                   
    add_exit(ELEMENTALIST_TEMPLE + "middle2", "west");
    add_exit(ELEMENTALIST_TEMPLE + "middle5", "southeast"); 
}
