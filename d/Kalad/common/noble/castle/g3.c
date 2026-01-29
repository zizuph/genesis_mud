// Sarr,
// Fysix, recoded, March 1998

#include "default.h"

inherit NOBLE_ROOM;

void
create_noble_room()
{
    set_short("In the castle courtyard");
    set_long("You stand in a grassy courtyard right before "+
    "the large castle that dominates the Noble district. "+
    "The castle doors stand right in front of you, leading "+
    "into the castle. A statue stands here, surrounded by "+
    "colourful flowers.\n");
    add_item(({"walls","castle"}),"The castle walls are made of grey stone "+
    "brick and mortar. As you gaze up, you see that they don't "+
    "reach very high up, but the towers do. You see many little "+
    "windows facing out of the walls.\n");
    add_item("bushes","Neat trimmed bushes.\n");
    add_item("flowers","Many wonderful flowers of different colors.\n");
    add_item("statue","A giant statue of a warrior, armoured in "+
    "formal fullplate. He holds a giant sword in his hands.\n");

    add_exit(NOBLE + "wayfarer/s8", "north", 0, 0);
    add_exit(NOBLE + "castle/g4", "east", 0, 0);
    add_exit(NOBLE + "castle/g2", "west", 0, 0);

    clone_object(NOBLE + "castle/door1")->move(TO);
}

