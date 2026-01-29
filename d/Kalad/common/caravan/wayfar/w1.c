#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Bedroom");
    set_long("You are inside a lavish bedroom.\n"+
      "This room is even more extravagantly decorated then the previous "+
      "one. Dominating the center of it is a large silken bed. At the far "+
      "end of the bedroom is a large redwood cabinet.\n");

    add_item(({ "bed" }), "A large king-sized bed. The covers are made out of "+
      "the finest of silks.\n");

    add_item(({ "cabinet" }), "A large cabinet made of one of the great "+
      "redwood trees from the Hespyre mountains. It looks quite aged.\n");

    add_exit(CVAN + "wayfar/white", "north");
}
