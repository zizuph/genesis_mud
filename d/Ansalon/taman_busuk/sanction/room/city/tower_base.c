#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCINROOM;


void
create_sanction_room()
{
    set_short("At the base of a stone tower");
    set_long("@@long_descr");

    add_item(({"tower","stone tower","base"}),
      "You presently stand at the base of a stone tower.\n");
    add_item(({"guard","lone guard"}),
      "A lone guard stands silently by the door. His " +
      "sullen look gives you the impression he doesn't " +
      "want to talk.\n");
    add_item("door","A sturdy door leads out to the east.\n");
    add_item("stairway","A stairway leads up to the roof of " +
      "the tower.\n");

    add_exit(SCITY + "tower_roof","up",0);
    add_exit(SCITY + "street8","east",0);
}


string
long_descr()
{
    return "You stand at the base of a stone tower. Due " +
    "to its proximity to the lava stream outside, this " +
    "tower is deserted except for a lone guard at the door. " +
    "A stairway leads up from here.\n";
}
