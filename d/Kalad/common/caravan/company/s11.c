#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Intersection");
    set_long("You reach a large intersection between two hallways.\n"+
      "Both hallways are utterly devoid of any furnishings having bare stone "+
      "walls. The only thing of note in either hallway is the marble floor. "+
      "One hallway heads in a west-east direction while the other passageway "+
      "heads south from here.\n");

    add_item(({ "stone walls", "walls" }), "The passage walls are built of "+
      "plain white stone.\n");

    add_item(({ "marble floor", "floor" }), "The ground is covered by "+
      "bleach-white marble tiles that are such a brilliant white color it "+
      "nearly blinds you when you look at them.\n");

    add_exit(CVAN + "company/s10", "west");
    add_exit(CVAN + "company/s28", "south");
    add_exit(CVAN + "company/s12", "east");
}
