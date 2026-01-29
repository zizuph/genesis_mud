inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("amid the vast docks of Pelargir");
    set_long(BSN("This is an aged dock stretching out into the river "
      + "Anduin. The port city of Pelargir stretches out to the "
      + "northwest, and more docks continue to the north. The city "
      + "walls reach the bank of the Anduin just south of here. In "
      + "front of the walls, there is an old derelict warehouse. "
      + "Fish odor thickens the air here, though it's probably just "
      + "because this dock is downwind from the fishing docks."));
    add_dockships();
    add_anduin("docks");
    add_admiral("harbour");
    add_wall();
    add_item(({"house", "warehouse", }), BSN("The warehouse was "
      + "built against the city wall. It looks derelict and in need "
      + "of repairs. Probably once upon a time there was more traffic "
      + "here in the harbour. In any case, nowadays, noone seems to "
      + "have any use for the warehouse anymore."));

    add_exit(PELAR_DIR + "docks/dock8",      "northwest",0);
    add_exit(PELAR_DIR + "docks/warehouse9", "southwest",0);
}
