#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Hallway");
    set_long("You are travelling along a hallway.\n"+
      "This passageway is utterly devoid of any furnishings. The only "+
      "noteable thing is the marble floor. The hallway continues to the "+
      "north and south.\n");

    add_item(({ "marble floor", "floor" }),
      "The ground is covered by expensive-looking marble tiles, each of which "+
      "is such a brilliant white that looking at them nearly blinds you.\n");

    add_exit(CVAN + "company/s7", "north");
    add_exit(CVAN + "company/s5", "south");

    clone_object(CVAN + "door/sdoor")->move(TO);
}
