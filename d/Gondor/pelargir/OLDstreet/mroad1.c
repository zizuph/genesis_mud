inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

object  citizen;

void
create_room()
{
    set_short("on Harlond Street in Pelargir");
    set_long(BSN("Harlond Street is entering a crossroads south of "
      + "here and just northeast of a bridge spanning the Sirith "
      + "River. To the north, it leads through the northern city "
      + "gate to the road that connects the Harlond and Pelargir."));

    add_cobble();
    add_northside();

    add_sirith();
    add_north_gate();
    add_wall();

    add_lighthouse("north");

    add_exit(PELAR_DIR + "street/n_gate_in","north",0);
    add_exit(PELAR_DIR + "street/ngbcross","south",0);

    citizen = add_citizen(citizen);
}

void
reset_room()
{
    citizen = add_citizen(citizen);
}

