#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/herbsearch.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err1","east",0,1
#define EXIT2 ELVVILL_DIR + "villrm1","up",0,2

void
create_er_room()
{

    int i;
    area = "not far from"; /* Distance from areaname */
    areaname = "Rivendell";
    land = "Eriador";
    areatype = 7;
    areadesc = "small clearing";
    grass = "green";

    extraline = "There is a small campfire, still warm, in the "+
    "middle of the clearing. The surrounding trees seem to "+
    "teeming with sounds of life. There is a rope ladder hanging "+
    "from one of the larger trees.";

    add_item(({"tree","trees","larger tree"}),"The "+
      "trees surrounding the clearing seem to be teeming with sounds "+
      "of life. The largest tree has a rope ladder hanging from one "+
      "of its branches.\n");

    add_item(({"campfire","small campfire"}),"The campfire is still warm "+
      "but there seems to be no indication of who was here.\n");

    add_exit(EXIT1);
    add_exit(EXIT2);
}
