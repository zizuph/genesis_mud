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
        + "pervades most of the Temple. A pair of braziers to the northeast "
        + "and west provides enough lighting to see that a small fresco on "
        + "the eastern wall is the only decoration in this room. The "
        + "hallway continues to the northwest and south from here.\n\n");

    try_item( ({ "brazier", "braziers", "copper brazier", "copper braziers",
        "tripod", "tripods", "bowl", "circular bowl" }),
        "The pair of braziers give off just enough lighting to see that they "
      + "are medium gold-coated tripods with a circular bowl fastened on "
      + "top. In the bowls, flowing flames brighten the room and cast waves "
      + "of shadow.\n");

    try_item( ({ "shadows", "shadow", "waves of shadow" }),
        "Focusing upon the shadows, you sense yourself gazing upon endless "
      + "seas and life-giving oceans. Thoughts of depth and meaning "
      + "flood your mind.\n");

    try_item( ({ "fresco", "frescoes", "scene", "scenery", "sceneries",
        "pair of sceneries", "small fresco", "small frescoes" }),
        "This fresco shows a pair of scenes. In the first scene, everything "
      + "portends of imminent disaster - a slow but rising tsunami is "
      + "closing on a village while flooding rivers ruin crops and oceans "
      + "are swallowing entire continents. In the second scene, life-giving "
      + "rains fall upon crops and small fishing boats dot the waters near "
      + "a seaside village.\n");
                         
    add_exit(ELEMENTALIST_TEMPLE + "middle3", "northwest");
    add_exit(ELEMENTALIST_TEMPLE + "middle7", "south"); 
}
