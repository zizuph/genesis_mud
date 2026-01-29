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
        "weeds's flowers to the delight of passersby. Rodhodendrons "+
        "enclosed the garden, and several types of flowers embelish "+
        "the garden. High above the garden some beautiful buildings "+
        "rise tall to the sky. You can troll into the garden to enjoy "+
        "the beauty of the premise or just sit down and have some "+
        "picnic with friends.\n");

    add_item("flowers",
        "In this section of the garden several shrubs of white, "+
        "lavender, and crimson lilacs adorn the place.\n");

    add_item(({"lilacs", "lilac", "white lilacs", "lavander lilacs",
        "crimson lilacs"}),
        "The gardeners have assembled a wonderful arrey of lilacs, "+
        "ranging from pure white to flaming crimson, with some "+
        "delicate shade of lavander. Clusters of tiny, fragant "+
        "flowers attract butterflies and bees alike.\n");

    add_exit("bridge2", "east");
    add_exit("bridge4", "west");
}
