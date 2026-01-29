#include "../defs.h"

inherit FRUIT_ROOM;

void
create_fruit_garden()
{

    set_em_long("A delightful fruit garden spreads in front of your "+
        "eyes. This garden is filled with many fruits of different "+
        "types, colors and flavors, all hanging ripe and ready to be "+
        "picked in green branches of the trees and bushes. There are "+
        "red and orange-yellow fruits that hang from the trees in this "+
        "section of the garden. As you glance around you see berry "+
        "bushes growing around the center of the garden along with a "+
        "circle of grey stone, grass, and emerald and onyx bushes. An "+
        "iron gate serves as the access to the garden and the Royal "+
        "Circle.\n");

    set_up_fruits(0, ({"cherry","peach", "blackberry"}));

    add_item(({"onyx bushes"}),
        "You look closer at the onyx bushes and you are amazed at the "+
        "quality of the dark leaves. You would expect them to be thick "+
        "and rough, but you find instead they are soft and pliable to the "+
        "touch.\n");

    add_item(({"berry bushes", "blackberries", "berries"}),
        "In this section of the garden, blackberry bushes grow. "+
        "thickly. The berries are ripe and mouth-watering.\n");

    add_item(({"red fruit", "red tree", "cherry tree"}),
        "These are cherries, dark red and sweet smelling. The fruit "+
        "look delicious and so easy to pick. They will make a fine "+
        "addition for a picnic meal.\n");

    add_item(({"orange-yellow fruit", "orange-yellow tree", "peach tree"}),
        "These are peaches, orange-yellow and fuzzy skinned. They "+
        "are perfectly ripe and ready to be eaten. The branches of "+
        "the trees, are just the right height for easy picking.\n");

    add_door_exit(TELBERIN_FRUIT_GARDEN_DIR + "garden_gate",
                  "/d/Emerald/telberin/royal_circle04",
                  "east", 0, 0, 1);
    add_exit("fruit06", "south");
    add_exit("fruit02", "southwest");
    add_exit("fruit05", "southeast");
}
