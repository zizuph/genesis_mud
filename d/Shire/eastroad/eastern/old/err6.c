#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err4","northeast", 0,1
#define EXIT2 ERE_DIR + "err7","southeast",0,2
#define EXIT3 ERE_DIR + "err20","east",0,1

void
create_er_room()
{

    area = "crossing";
    areaname = "The Angle";
    land = "Eriador";
    areatype = 8;
    areadesc = "heavy woods";
    grass = "green";

    extraline = "The Angle is created by the merging of the two "+
    "great rivers, Mitheithel and Bruinen. The Great East Road "+
    "winds on a very steep grade between the Last Bridge, leading "+
    "to the Lone-lands, and the stone bridge, crossing the River "+
    "Bruinen, to Rivendell. The sharp turns in the road and the "+
    "heavy woods prevent seeing very far in any direction. There "+
    "seems to be a fairly well traveled path, through the woods, "+
    "to the east.";

    add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
}
