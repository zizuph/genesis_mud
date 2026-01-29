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
        + "and west provides enough lighting to see that a small fresco on "
        + "the eastern wall is the only decoration in this room. The "
        + "hallway continues to the south and northeast from here.\n\n");

    try_item( ({ "brazier", "braziers", "copper brazier", "copper braziers",
        "tripod", "tripods", "bowl", "circular bowl" }),
        "The pair of braziers give off just enough lighting to see that they "
      + "are medium copper-coated tripods with a circular bowl fastened on "
      + "top. In the bowls, blazing flames light the room, spouting ever "
      + "flickering shadows everywhere.\n");

    try_item( ({ "shadows", "shadow", "dancing shadows", "dancing shadow" }),
        "As you look upon the shadows you sense a crescendo of chaos and "
      + "passion, images of the flame and all light shining upon all fills "
      + "your mind.\n");


    try_item( ({ "fresco", "frescoes", "scenes", "scene",
        "small fresco", "small frescoes" }),
        "This fresco depicts two scenes. In one of the scenes, a raging "
      + "thunderstorm is crossing a vast area. A massive funnel of wind "
      + "and cloud is raining bolt upon bolt of lightning on everything "
      + "underneath it. Entire forests, villages, and all of the dwellers "
      + "are torn apart and swallowed whole along its path of destruction. "
      + "The other scene shows Creation, and the changing of the seasons "
      + "as clear white skies persist.\n");
      
                   
    add_exit(ELEMENTALIST_TEMPLE + "middle1", "northeast");
    add_exit(ELEMENTALIST_TEMPLE + "middle6", "south"); 
}
