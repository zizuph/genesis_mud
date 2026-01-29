#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Gateway lane");
    set_long("This is Gateway Lane you are currently travelling on, its "+
      "cobble-paved surface stretches west and east from here. Towering to "+
      "your north are the massive city walls of Kabal, while to the south "+
      "you can see a high stone wall surrounding a large and imposing "+
      "edifice. Animal refuse litters the ground.\n");

    add_item(({ "city walls", "walls" }),
      "Examining the wall closer you note the fine quality of the stone it "+
      "was built from. It can only have come from the Hespyre mountains "+
      "which lie east of the city. The walls themself rise to a height of "+
      "thirty feet.\n");

    add_item(({ "high stone wall", "stone wall", "wall" }),
      "You examine the high stone wall closer, it looks to be at least "+
      "fifteen feet in height and remarkably enough, there are no graffiti "+
      "marks or other signs of filth on its surface. Just over the top of "+
      "the wall you can see a dark, imposing edifice.\n");

    add_item(({ "edifice" }),
      "All you can tell from here is that the building is made out of dark "+
      "grey, almost black stone. Any other details are blocked out by the "+
      "high stone wall surrounding it.\n");

    add_item(({ "animal refuse", "refuse" }),
      "Bits of animal feces litter the street. The smell is overpowering, to say "+
      "the least.\n");

    add_exit(CVAN + "gateway/s1", "west");
    add_exit(CVAN + "alley_gate", "east");
}
