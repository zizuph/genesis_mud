#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Corner");
    set_long("You've reached the corner of the building.\n"+
      "From here empty hallways lead away towards the north and east. "+
      "Both hallways are exquisitely floored with expensive-looking marble "+
      "tiles.\n");

    add_item(({ "marble tiles", "tiles" }),
      "The ground is covered with marble tiles so brilliantly white that "+
      "it nearly blinds you.\n");

    add_exit(CVAN + "company/s5", "north");
    add_exit(CVAN + "company/s3", "east");
}
