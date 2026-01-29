#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Hallway");
    set_long("You are travelling down a hallway.\n"+
      "This hallway is utterly devoid of any furnishings whatsoever. The "+
      "only thing of note is the marble floor. The passageway continues to "+
      "the north and south.\n");

    add_item(({ "marble floor", "floor" }),
      "The ground is covered in bleach-white tiles of marble. The floor is "+
      "such a brilliant color that it nearly blinds you.\n");

    add_exit(CVAN + "company/s6", "north");
    add_exit(CVAN + "company/s4", "south");

    clone_object(CVAN + "door/kdoor")->move(TO);
}
