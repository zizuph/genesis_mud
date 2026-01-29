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
      "From here empty hallways lead away towards the north and east. "+
      "Both hallways are exquisitely floored with expensive-looking marble "+
      "tiles.\n");

    add_item(({ "marble tiles", "tiles" }),
      "The ground is covered with marble tiles so brilliantly white that "+
      "it nearly blinds you.\n");

    add_exit(CVAN + "company/s83", "north", "@@move");
    add_exit(CVAN + "company/s77", "east");
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
