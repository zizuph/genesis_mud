inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  sailor;

void
reset_room()
{
    sailor = add_citizen(sailor, PELAR_DIR + "npc/sailor");
}

void
create_room()
{
    set_short("along Sailor's Boulevard in Pelargir");
    set_long(BSN("This is a short street that runs along the docks in "
      + "Pelargir, known as Sailor's Boulevard. The street continues "
      + "to its end north of here, and runs past several buildings to "
      + "the south. Peals of bawdy laughter and sailor songs ring "
      + "from a building to the west, and the many docks of Pelargir "
      + "extend along the shore to the east."));
   add_item("building",BSN("The building to the west seems "+
      "to be a popular hangout for sailors and dock workers, "+
      "probably a pub."));
   add_dockships();
  add_cobble();
   add_exit(PELAR_DIR + "docks/dokst","north",0);
   add_exit(PELAR_DIR + "misc/sailor_pub","west",0);
   add_exit(PELAR_DIR + "docks/dokst2","south",0);
   add_exit(PELAR_DIR + "docks/dock2","east",0);

    reset_room();
}
