#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Hallway");
    set_long("You are travelling down a hallway.\n"+
      "This passageway is utterly devoid of any furnishings. The only thing of "+
      "note is the marble floor. The hallway continues to the west and "+
      "east.\n");

    add_item(({ "marble floor", "floor" }),
      "The floor is covered with marble tiles, each tile being so "+
      "brilliantly white in color that it nearly blinds you.\n");

    add_exit(CVAN + "company/s43", "west");
    add_exit(CVAN + "company/s45", "east");
}
