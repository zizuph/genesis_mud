#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Hallway");
    set_long("You are travelling down a hallway.\n"+
      "This passageway is empty of any furnishings, the only thing of note "+
      "being the marble floor. The hallway stretches to the north and south, "+
      "while another smaller hallway leads east from here.\n");

    add_item(({ "marble floor" }),
      "The ground is covered in marble tiles that are a brilliant white in "+
      "color. The color is so bright that you cannot look at it for long "+
      "without your eyes hurting.\n");

    add_exit(CVAN + "company/s28", "north");
    add_exit(CVAN + "company/s34", "east");
    add_exit(CVAN + "company/s22", "south");

    clone_object(CVAN + "door/bdoor")->move(TO);
}
