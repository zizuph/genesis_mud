#pragma strict_types

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

object  citizen;

void
create_room()
{
    set_short("North/South Pelargir street");
    set_long(BSN("This cobblestone street leads north and "+
       "south through the city of Pelargir. Houses line the sides "+
       "of the street, and just to the south you can see the gates to "+
       "the Admiral's white tower. To the north a few side streets "+
       "lead off into different parts of Pelargir, and the main road "+
       "crosses a bridge towards the Pelargir city gates."));

   add_cobble();
   add_admiral();

   add_item(({"bridge","gates","streets"}),BSN("If you "+
      "would really like a good look, you should get closer."));
    add_exit(PELAR_DIR + "street/groad3","north",0);
    add_exit(PELAR_DIR + "street/groad1","south",0);

    citizen = add_citizen(citizen);
}

void
reset_room()
{
    citizen = add_citizen(citizen);
}

