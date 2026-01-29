#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err12","east",0,1
#define EXIT2 ERE_DIR + "err22","west",0,1

void
create_er_room()
{

    area = "on the top of a deep";
    areaname = "ravine";
    land = "Eriador";
    areatype = 5;
    areadesc = "path";
    grass = "green";

    extraline = "To the west there is the face of a cliff with "+
    "an open, broken wooden door. Dark trees and heavy "+
    "underbrush prevent movement anywhere but "+
    "down to the ravine or through the open door.";

    add_item(({"walls","ancient walls","towers","ruined towers"}),"The "+
      "ancient walls and ruined towers are all that remain of an "+
      "old human civilization, destroyed in the war that "+
      "ended the North Kingdom.\n");

    add_item(({"campfire","small campfire"}),"The campfire is still warm "+
      "but there seems to be no indication of who was here.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
}
