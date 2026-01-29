#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err12","north",0,2
#define EXIT2 ERE_DIR + "err14","east",0,1

void
create_er_room()
{

    area = "on";
    areaname = "the bank of the River Mitheithel";
    land = "Eriador";
    areatype = 5;
    areadesc = "path";
    grass = "green";

    extraline = "The river gurgles below the bank but seems too "+
    "deep to cross. In the distance across the river, the "+
    "peaks of the Weather Hills can be seen. To the north there "+
    "is a rocky, deep ravine that seems almost impossible to "+
    "travel through because of all the rocks and boulders. The "+
    "rocky bank of the river continues east. To the west a cliff "+
    "prevents all passage.";

    add_item("cliff","The walls of the cliff are extremely steep "+
      "and impossible to climb. There seems to be some scratchings "+
      "in the wall.\n");

    add_item(({"scratching","scratchings"}),"The scratchings are "+
      "in the shape of a heart with an arrow through it. Inside the "+
      "heart there are two names that were carved in happier times.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
}
