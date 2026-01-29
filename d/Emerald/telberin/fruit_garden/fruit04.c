#include "../defs.h"

inherit FRUIT_ROOM;

void
create_fruit_garden()
{

     set_em_long("A delightful fruit garden spreads in front of your "+
        "eyes. This garden is filled with many fruits of different "+
        "types, colors and flavors. All hanging ripe and ready to be "+
        "picked in green branches of the trees and bushes. There are "+
        "yellow and crimson fruits that hang from the trees in this section "+
        "of the garden. As you glance around you see berry bushes "+
        "growing around the center of the garden along with a circle of "+
        "grey stone, grass, and emerald and ruby bushes.\n");

    set_up_fruits(0, ({"lemon","orange", "gooseberry", "strawberry"}));

    add_item(({"gooseberries", "gooseberry"}),
        "You look closer at the gooseberries. You find them to be very "+
        "ripe and ready for picking.\n");

    add_item(({"strawberries", "strawberry"}),
        "You look closer at the strawberries and you find them quite red "+
        "and ripe. In fact they are so ripe you can smell their sweetness "+
        "and you are tempted to pick one to have a taste.\n");

    add_item(({"berries", "berry bushes"}),
        "You can see gooseberries and strawberries growing thickly in "+
        "this section of the garden.\n");

    add_item(({"ruby bushes"}),
        "You take a closer look at the ruby bushes. They sparkle and "+
        "glitter in a gentle charming way. The shape and color of the "+
        "leaves resemble rubies all clustered together.\n");


    add_item(({"yellow-fingered fruit", "yellow-fingered tree", "citron tree"}),
        "These are special lemons. This fruit look like a yellow "+
        "five-fingered hand. They are called Fingered Citrons and "+
        "their fruit is sweet and taste like candied lemons. "+
        "Although the fruit looks weird, it tastes better that its "+
        "look.\n");

    add_item(({"yellow fruit", "yellow tree", "lemon tree"}),
        "These are lemons, bright yellow with a strong citrus smell "+
        "from a Dwarf lemon tree. These lemons are smaller than "+
        "the traditional ones, but they are sweeter and can be eaten "+
        "like a fruit. If you pick one of these lemons you "+
        "can either eat it or make a drink from it.\n");


    add_exit("fruit03", "west");
    add_exit("fruit05", "north");
    add_exit("fruit06", "northwest");

}
