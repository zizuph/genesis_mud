inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
   set_short("on an east-west road");
   set_long(BSN("You are at the base of an aged lighthouse. "+
      "The river courses around this outcropping of land to the east "+
      "and you can hear the currents swirling dangerously "+
      "below among the rocks. Back to the west you can enter the "+
      "city proper. Gazing back towards the city you can make out the "+
      "Admiral's tower."));
   add_item(({"river","anduin river","anduin"}),BSN(
      "From this vantage you have a beautiful view of the river. "+
      "To the north The Anduin seems to march inexorably towards you "+
      "as it flows into and around the stretch of rock you stand upon. "+
      "To the south the rock provides a shelter of sorts from the river's "+
      "current, letting the ships dock peacefully at Pelargir."));
   add_lighthouse("north");
   add_towers();
   add_admiral();
   add_exit(PELAR_DIR + "street/nroad5","west",0);
   add_exit(PELAR_DIR + "docks/light1","in",0);
}

