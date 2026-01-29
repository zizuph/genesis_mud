#include "../default.h"
inherit CVAN_ROOM;

#include <ss_types.h>

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Corner");
    set_long("You've reached a corner.\n"+
      "From here empty hallways head to the east and south. There are "+
      "absolutely no furnishings in either hallway, the only noteworthy "+
      "thing about either one is the marble floor.\n");

    add_item(({ "marble floor", "floor" }),
      "The ground is covered with bleach-white marble tiles that look "+
      "quite expensive. The color of the tiles is so bright that you are "+
      "forced to look away.\n");

    add_exit(CVAN + "company/s75", "east");
    add_exit(CVAN + "company/s83", "south", "@@move");
}

int
move()
{
    if(TP->query_base_stat(SS_DIS) < 76)
    {
	write("You lack the will to continue further.\n");
	say(QCTNAME(TP) + " lacks the will to go further.\n");
	return 1;
    }
    write("You bravely continue onward.\n");
    say(QCTNAME(TP) + " bravely continues onward.\n");
    return 0;
}
