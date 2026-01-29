#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Intersection");
    set_long("You've reached a small intersection of two hallways.\n"+
      "One hallway travels in a west-east direction while another "+
      "passageway heads northwards. Both hallways are empty of any "+
      "furnishings, with the only thing of note being their marble floor.\n");

    add_item(({ "marble floor", "floor" }),
      "The ground is covered in bleach-white marble tiles that look quite "+
      "expensive. The floor is such a brilliant white color that you are "+
      "nearly blinded from looking at it.\n");

    add_exit(CVAN + "company/s55", "west");
    add_exit(CVAN + "company/s67", "north");
    add_exit(CVAN + "company/s53", "east");
}
