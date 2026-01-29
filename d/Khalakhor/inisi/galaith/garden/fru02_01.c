#include "../defs.h"

inherit FRUIT_ROOM;

void
create_fruit_garden()
{

    set_long("An enchanting fruit garden rests quietly within the "+
      "protective fold of towering pines. There are different sizes "+
      "and shapes of fruit all around you. Some fruits are ripe and "+
      "ready to be picked among the bushes and trees, and some are "+
      "not quite ready to be sampled. There is a simple stone path "+
      "that winds its way through the various plants and vines.\n");
    set_up_fruits(0, ({"cherry","blueberry", "blackberry"}));
    add_item(({"bushes", "blackberries", "blueberries", "berries"}),
      "There are blueberry and blackberry bushes growing along "+
      "side the path.\n");
    add_item(({"red fruit", "red tree", "cherry tree"}),
        "Sweet dark cherries grow in a few scattered cherry trees.\n");
    add_exit("fru01_01", "north");
    add_exit("fru03_01", "south");

}