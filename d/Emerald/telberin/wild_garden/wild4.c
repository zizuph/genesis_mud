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
        "enclosed the garden from the outside world and some aromatic "+
        "trees embelish the garden. High above the garden some "+
        "beautiful buildings rise tall to the sky. You can troll into "+
        "the garden to enjoy the beauty of the premise or just sit "+
        "down and have some picnic with friends.\n");

    add_item("trees",
        "The gardeners of this garden chose carefully these trees. "+
        "They are Frangipani, beloved trees for caterpillars, "+
        "butterflies and bees alike. Their large, fragant pink flowers "+
        "are the favorite of perfumist. The trees are of normal size, "+
        "with big green leaves. They are beautiful to look at and a "+
        "delight for visitors.\n");
    

    add_exit("bridge3", "southeast");
    add_exit("bridge4", "northeast");
}
