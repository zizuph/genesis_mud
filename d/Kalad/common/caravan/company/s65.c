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
      "being the marble floor. The passage continues to the north and south "+
      "while another smaller hallway lies to the west.\n");

    add_item(({ "marble floor", "floor" }), "The ground is covered in marble "+
      "tiles of such a brilliant white color, that you fear you may suffer "+
      "blindness if you stare any longer.\n");

    add_exit(CVAN + "company/s66", "west");
    add_exit(CVAN + "company/s64", "north");
    add_exit(CVAN + "company/s52", "south");

    clone_object(CVAN + "door/tcdoor")->move(TO);
}
