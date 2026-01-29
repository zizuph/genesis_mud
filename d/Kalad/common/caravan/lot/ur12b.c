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
      "which is so moist, water is dripping from it.\n");

    add_item(({ "tunnel" }), "The tunnel seems to grow colder to the west "+
      "and hotter to the east.\n");

    add_item(({ "walls", "wall", "ceiling" }), 
    "The entire tunnel is made out of the limestone rock.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur12a", "west");
    add_exit(CVAN + "lot/ur12c", "east");
}

void
init()
{
    ::init();
    write("Cool air greets you.\n");
}
