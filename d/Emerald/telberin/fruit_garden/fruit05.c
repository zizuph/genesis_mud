#include "../defs.h"

inherit FRUIT_ROOM;

void
create_fruit_garden()
{

     set_em_long("A delightful fruit garden spreads in front of your "+
        "eyes. This garden is filled with many fruits of different "+
        "types, colors and flavors. All hanging ripe and ready to be "+
        "picked in green branches of the trees and bushes. There are "+
        "crimson and white cream fruits that hang from the trees in "+
        "this section of the garden. As you glance around you see "+
        "berry bushes growing around the center of the garden along "+
        "with a circle of grey stone, grass, and emerald and pink "+
        "bushes.\n");

    set_up_fruits(0, ({"lemon","plum", "logan berry", "peach"}));

    add_item(({"berry bushes", "logan berries", "berries"}),
        "In this section of the garden, logan berries bushes grow "+
        "thickly. The berries are ripe and mouth-watering.\n");

    add_item(({"pink bushes"}),
        "On a closer inspection of the pink bushes you discover what "+
        "appeared to be one leaf was actually a cluster of five small "+
        "tender leaves. They join together to form a perfect union which "+
        "gives the illusion of a singular leaf.\n");

    add_item(({"white cream fruit", "white cream tree", "cream fruit"}),
        "These are white peaches, another very juicy fruit. The  aroma "+
        "of these peaches is softer than traditional peaches. The fuzzy "+
        "skin is like velvet and has a soft pale orange color, almost "+
        "white like sweet cream. The trees have low branches that make "+
        "picking the fruits very easy.\n");

    add_item(({"crimson fruit", "crimson tree", "blood plum tree"}),
        "These are Blood Plums. The fruit's skin is like bright red "+
        "blood. The fruit is smaller than the regular plums, but "+
        "they are very juicy and tasty. The trees have plenty of "+
        "fruits and they are easy to reach and pick.\n");

    add_exit("fruit06", "west");
    add_exit("fruit04", "south");
    add_exit("fruit01", "northwest");


}
