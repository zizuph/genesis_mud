#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 0);

    set_short("Deep tunnel");
    set_long("You can barely see within this dark and "+
      "extremely damp tunnel. The walls are made of what appears to be "+
      "limestone, or some such porous rock. This explains the ceiling, "+
      "which is so moist, water is dripping from it.\n"+
      "A ladder leads up from here.\n");

    add_item(({ "tunnel" }), "It seems to grow warmer to the east.\n");

    add_item(({ "ladder" }), "A small wooden ladder with rungs made out of "+
      "hemp rope. It seems to lead straight up into the ceiling.\n");

    add_item(({ "walls", "wall", "ceiling" }), 
    "The entire tunnel is made out of the limestone rock.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur12", "up");
    add_exit(CVAN + "lot/ur12b", "east");
}

void
init()
{
    ::init();
    write("Cold air assaults you!\n");
}
