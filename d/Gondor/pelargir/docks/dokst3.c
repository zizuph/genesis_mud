inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  thief;

void
reset_room()
{
    thief = add_citizen(thief, PELAR_DIR + "npc/yngthief");
}

void
create_room()
{
    set_short("along Sailor's Boulevard");
    set_long(BSN("This is Sailor's Boulevard. Many shops extend along "
      + "the street, mostly frequented by sailors and travellers. To "
      + "the west there is some kind of shop and to the north and "
      + "south the street continues on. The fresh air rolls in from "
      + "the river to the east, where you can see many people "
      + "scurrying about the docks of Pelargir."));
    add_dockships();
    add_cobble();
    add_anduin("city");
    add_item(({"shop","shops"}), BSN("There are quite a few "
      + "interesting shops along the boulevard. The shop just west of "
      + "here seems to sell charms and trinkets mostly, though for "
      + "some reason the shopkeeper hasn't ever gotten around to opening it."));

    add_exit(PELAR_DIR + "docks/dokst2","north",0);
    add_exit(PELAR_DIR + "docks/dock4","east",0);
    add_exit(PELAR_DIR + "docks/dokst4","south",0);
    
    reset_room();
}

