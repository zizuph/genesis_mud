#pragma strict_types
#include "../defs.h"

inherit FRUIT_ROOM;

public int
exit_desc()
{
    write("You press your way through some thick odd looking vines.\n");
    return 0;
}

public void
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
    add_exit(ROOM + "pool", "north","@@exit_desc");
    add_exit("fru01_03", "east");
    add_exit("fru01_01", "west");

}
