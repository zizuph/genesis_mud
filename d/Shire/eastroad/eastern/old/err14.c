#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err8","east",0,1
#define EXIT2 ERE_DIR + "err13","west",0,1

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
    "Eastroad can be seen as is skirts around the Weather Hills "+
    "and the Midgewater Marshes. The bank of the river "+
    "continues to the east and west but large rocks and boulders "+
    "prevent any passage north.";

    add_item(({"walls","ancient walls","towers","ruined towers"}),"The "+
      "ancient walls and ruined towers are all that remain of an "+
      "old human civilization, destroyed in the war that "+
      "ended the North Kingdom.\n");

    add_item(({"campfire","small campfire"}),"The campfire is still warm "+
      "but there seems to be no indication of who was here.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
}
