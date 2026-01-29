#include "defs.h"
inherit OUTPOST_INSIDE_ROOM;

void
create_outpost_inside_room()
{
    set_short("In the southwestern tower.");
    set_em_long("You are inside the southwestern tower of the outpost. " +
       "From up here, the entire camp is layed out before your eyes. " +
       "Mountains rise up on the western and eastern sides of the outpost. " + 
       "The sharp pointed tops of the wooden wall enclosing the camp thrust " +
       "from the ground below and slightly obscure your view of the " +
       "surrounding countryside. The only exit you see is down a ladder " +
       "through a hole in the floor.\n");

    add_item( ({"tops", "pointed tops", "wooden wall", "wall"}),
        "Thick logs, sharpened to a point, stand vertically side by side " +
        "forming a wall around the camp. The logs are lashed together with " +
        "rope, driven deep into the ground, and reinforced with large rocks. " +
        "You notice a set of gates built into the southern wall off to your east.\n");

    add_item( ({"floor" }),
        "Below your feet is a wooden platform which forms the floor for the tower. " +
        "The wood has been shaped and cut into boards which fit tightly together. " +
        "There is a square hole cut into the middle of the platform with a ladder " +
        "securely fastened to the east side of the hole.\n");

    add_item( ({"camp"}),
        "Four rough, wooden buildings stand inside the walls of the outpost. Two " +
        "of those buildings, one on each side of the camp, are rather large, while " +
        "the two other buildings are much smaller structures. There are towers in " +
        "each corner and in the center of the camp.\n");
 
    add_item( ({"mountains", "mountain", "foothills", "foothill"}),
        "The smaller peaks of the Blackwall mountain range rise on the eastern and " +
        "western sides of the camp. Thick trees cover the foothills of the mountains, " +
        "but higher up you notice patches of snow and ice ringing their summits.\n");

    add_item( ({"tower"}),
        "Made of wood, this tower is covered with a thin, sloped roof to " +
        "protect the guards on duty from foul weather and the harsh midday " +
        "sun. The floor has a hole cut into the middle, providing access to " +
        "the yard below via a wooden ladder.\n");

    add_item( ({"view", "countryside", "surrounding countryside"}),
        "This outpost has been constructed in the middle of a pass in the mountains. " +
        "Pine trees dot the slopes of the foothills, though those trees closest to " +
        "the outpost have been cleared to provide a clear view from the towers. To the " +
        "north, you notice a winding path leading further into the mountains, while " +
        "southwards, a similar path leads back towards civilization.\n");

    add_item( ({"hole"}),
        "A small hole is cut into the middle of the floor of the platform. " +
        "Upon the east side of the hole, the top of a wooden ladder is secured " +
        "with steel brackets.\n");

    add_item( ({"steel bracket", "steel brackets", "bracket", "brackets"}),
        "Solid steel brackets on each side of the ladder secure its top to the side " +
        "of the hole.\n");

    add_item( ({"ladder", "wooden ladder", "rungs", "steps" }),
        "A small, wooden ladder is secured to the east side of the hole. Each side of " +
        "the ladder is secured to the side of the hole with steel brackets. Large, wide " +
        "steps show the wear of frequent use, but look well maintained and secure.\n");

    add_item( ({"gate" , "gates", "front gates", "southern gates", 
                "southern gate", "front gate"}),
        "Thick wooden gates stand in the middle of the southern wall. Reinforced with " +
        "steel, they look as though it would take a massive amount of force to open " +
        "them once they are closed.\n");

    
    add_exit("yard_13","down");
}
