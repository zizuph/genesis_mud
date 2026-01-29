
#include "../defs.h"

inherit WILD_ROOM;

void
create_wild_garden()
{

    set_em_long("A charming wildlife garden lays in front of you. "+
        "The design of this garden is imaginative. From here, you "+
        "see two creeks that flow to the the center of the garden. "+
        "Orange flowers mingle merrily with the green of leaves to "+
        "give a festive air to the weeds that surround the pond at "+
        "the center of the garden. Butterflies fly in and out of the "+
        "weeds's flowers to the delight of passersby. Between both "+
        "side of the iron gate, rodhodendrons and several types of "+
        "flowers embelish the garden. High above the garden some "+
        "beautiful buildings rise tall in the sky. You can troll into "+
        "the garden to enjoy the beauty of the premise or just sit "+
        "down and have some picnic with friends.\n");


    add_item(({"bushes", "butterfly bushes"}),
        "These are Butterfly bushes. As the name indicated, these "+
        "bushes attract all kinds of butterflies, besides bees and "+
        "even flies, but specially butterflies. They loves to drink "+
        "from the sweet nectar of its purple and yellow flowers.\n");

    add_item(({"purple flowers", "yellow flowers"}),
        "These purple and yellow flowers belong to the Butterfly "+
        "bushes that are in this section of the garden.\n");

    add_item("flowers",
        "In these section of the garden several bushes with purple and "+
        "yellow flowers adorn the place.\n");
        
    add_door_exit(GARDEN_GATE, "../tel07_11", "east");
    add_exit("bridge1", "southwest");
    add_exit("bridge2", "northwest");
}

