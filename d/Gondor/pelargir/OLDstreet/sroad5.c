inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  cit;

void
create_room()
{
    set_short("south of Pelargir square");
    set_long(BSN("You are standing on a rough cobblestone street "
      + "in southern Pelargir. Above the city rooftops and the "
      + "large statue in the square to the northwest you can see "
      + "the Admiral's tower. To the south are the city gates through "
      + "which the road leaves Pelargir on its course towards Linhir "
      + "and Dol Amroth."));

    add_item("statue",BSN("The statue is rather tall and bulky but "+
       "other than that you cannot see details without getting "+
       "closer."));

    add_cobble();
    add_south_gate();
    add_admiral();
    add_wall();

    add_exit(PELAR_DIR + "street/s_gate_in", "south",0);
    add_exit(PELAR_DIR + "street/sroad4",    "northwest",0);
    
    cit = add_citizen(cit);
}

void
reset_room()
{
    cit = add_citizen(cit);
}

