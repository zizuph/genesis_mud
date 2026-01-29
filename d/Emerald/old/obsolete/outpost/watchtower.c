#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;

void
create_outpost_outside_room()
{
    set_short("In the watchtower.");
    set_long("You are standing inside the watchtower in the center of the " +
       "outpost. From here it is easy to see every area of the camp including " +
       "both the southern and northern gates. A large bell hangs from the " +
       "ceiling of the tower. The only exit you see is down a ladder through " +
       "a hole in the floor.\n");

    add_item( ({"floor" }),
        "Below your feet is a wooden platform which forms the floor for the tower. " +
        "The wood has been shaped and cut into boards which fit tightly together. " +
        "There is a square hole cut into the middle of the platform with a ladder " +
        "securely fastened to the west side of the hole.\n);

    add_item( ({"camp"}),
        "Four rough, wooden buildings stand inside the walls of the outpost. Two " +
        "of those buildings, one on each side of the camp, are rather large, while " +
        "the two other buildings are much smaller structures. There are towers in " +
        "each corner and in the center of the camp.\n");
 
    add_item( ({"watchtower"}),
        "Made of wood, the watchtower is covered with a thin, sloped roof to " +
        "protect the guards on duty from foul weather and the harsh midday " +
        "sun. The floor has a hole cut into the middle, providing access to " +
        "the yard below via a wooden ladder. A large, iron bell hangs from the " +
        "ceiling.\n");

    add_item( ({"hole"}),
        "A small hole is cut into the middle of the floor of the platform. " +
        "Upon the north side of the hole, the top of a wooden ladder is secured " +
        "with steel brackets.\n");

    add_item( ({"steel bracket", "steel brackets", "bracket", "brackets"}),
        "Solid steel brackets on each side of the ladder secure its top to the side " +
        "of the hole.\n");

    add_item( ({"ladder", "wooden ladder", "rungs", "steps" }),
        "A small, wooden ladder is secured to the north side of the hole. Each side of " +
        "the ladder is secured to the side of the hole with steel brackets. Large, wide " +
        "steps show the wear of frequent use, but look well maintained and secure.\n");

    add_item( ({"gate" , "gates", "northern gates", 
                "northern gate", "southern gate", "southern gates"}),
        "Thick wooden gates stand in the middle of the northern and southern walls. " +
        "Reinforced with steel, they look as though it would take a massive amount " +
        "of force to open them once they are closed.\n");
    
    add_item( ({"bell"}),



    
    add_exit("yard_08","down");
}
