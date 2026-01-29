#include "../defs.h"

inherit FRUIT_ROOM;

void
create_fruit_garden()
{

     set_em_long("A delightful fruit garden spreads in front of your "+
        "eyes. This garden is filled with many fruits of different "+
        "types, colors and flavors. All hanging ripe and ready to be "+
        "picked in green branches of the trees and bushes. There are "+
        "bright orange and yellow fruits that hang from the trees in this "+
        "section of the garden with some ground covered vines. As you "+
        "glance around you see berry bushes growing around the center "+
        "of the garden along with a circle of grey stone, grass, and "+
        "emerald and blue sapphire bushes.\n");

    set_up_fruits(0, ({"lemon","orange", "blueberry", "melon"}));

    add_item(({"berry bushes", "berries", "blueberries"}),
        "In this section of the garden, blueberry bushes grow "+
        "thickly. The berries are ripe and mouth-watering.\n");

    add_item(({"covered vines", "vines"}),
        "You look closer at the vines and under a few of the green leaves "+
        "you see large emerald colored melons. You imediately recognize "+
        "them as pota-rah. Pota-rah is one of the sweetest of melons "+
        "found in Emerald. Within the emerald rind you can always find "+
        "tender, succulent red and pink flesh mingled with black and "+
        "emerald seeds.\n");

    add_item(({"blue bushes", "sapphire bushes"}),
        "You look closer at the blue sapphire bushes. They are quite "+
        "lovely with large pointed leaves with a touch of silver on their "+
        "tips.\n");

    add_item(({"yellow fruit", "yellow tree", "lemon tree"}),
        "These are lemons, bright yellow with a strong citrus smell, "+
        "from a miniture lemon tree. These lemons are different from "+
        "traditional ones because they are sweeter and can be "+
        "eaten like a fruit\n");

    add_item(({"bright orange fruit", "bright orange tree", "mandarin tree"}),
        "These are mandarin oranges. They have a bright orange colors "+
        "and a sweet citrus smell. The trees have plenty of fruits and "+
        "are easy to reach and pick.\n");

    add_exit("fruit04", "east");
    add_exit("fruit06", "north");
    add_exit("fruit02", "northwest");

}
