#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Corner");
    set_long("You've reached a corner of the building.\n"+
      "From here empty hallways head to the east and south. There is "+
      "absolutely no furnishings in either hallway, the only noteworthy "+
      "thing about either one is the marble floor.\n");

    add_item(({ "marble floor", "floor" }),
      "The ground is covered with bleach-white marble tiles that look "+
      "quite expensive. The color of the tiles is so bright that you are "+
      "forced to look away.\n");

    add_exit(CVAN + "company/s42", "east");
    add_exit(CVAN + "company/s40", "south");
}
