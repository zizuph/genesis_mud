#include "../defs.h"

inherit FRUIT_ROOM;

void
create_fruit_garden()
{

     set_em_long("A delightful fruit garden spreads in front of your "+
        "eyes. This garden is filled with many fruits of different "+
        "types, colors and flavors. All hanging ripe and ready to be "+
        "picked in green branches of the trees and bushes. There are "+
        "red and bright orange fruits that hang from the trees in this "+
        "section of the garden. As you glance around you see berry "+
        "bushes growing around the center of the garden along with a "+
        "circle of grey stone, grass, and emerald and red bushes.\n");

    set_up_fruits(0, ({"cherry","orange", "raspberry"}));

    add_item(({"berry bushes", "berries"}),
        "In this section of the garden, raspberry bushes grow "+
        "thickly. The berries are ripe and mouth-watering.\n");

    add_item(({"red bushes"}),
        "You look closer at the red bushes and are intrigued by the bright "+
        "red folds in the leaves which forms a pattern which looks like an "+
        "elven guard. You are amazed at how they appear to glisten with "+
        "a mysterious red dew.\n");

    add_item(({"red dew", "leaves"}),
        "You carefully inspect the deep blood red dew on the leaves. "+
        "It appears to be thick and has a sweet smell.\n");

    add_item(({"red fruit", "red tree", "cherry tree", "cherries"}),
        "These are cherries, dark red and sweet smelling. The "+
        "fruit look delicious and so easy to pick. They will make "+
        "a fine addition for a picnic meal.\n");

    add_item(({"bright orange fruit", "bright orange tree", "mandarin tree"}),
        "These are mandarin oranges. They are bright orange in colors "+
        "and have a sweet citrus smell. The trees have plenty of "+
        "fruits and are easy to reach and pick.\n");

    add_exit("fruit06", "east");
    add_exit("fruit01", "northeast");
    add_exit("fruit03", "southeast");
}
