#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err10","north",0,1
#define EXIT2 ERE_DIR + "err5","southwest",0,2

void
create_er_room()
{

    area = "close to";
    areaname = "the Great East Road";
    land = "Eriador";
    areatype = 5;
    areadesc = "narrow path";
    grass = "green";

    extraline = "The path winds through somber country of "+
    "dark trees and sullen hills. Glimpses of ancient walls and "+
    "ruined towers can sometimes be caught by the wary traveler.";

    add_item(({"walls","ancient walls","towers","ruined towers"}),"The "+
      "ancient walls and ruined towers are all that remain of an "+
      "old human civilization, destroyed in the war that "+
      "ended the North Kingdom.\n");

    add_item(({"campfire","small campfire"}),"The campfire is still warm "+
      "but there seems to be no indication of who was here.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
}
