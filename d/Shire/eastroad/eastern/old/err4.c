#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR +"err10","northwest",0,1
#define EXIT2 ERE_DIR +"err6","southwest",0,1

void
create_er_room()
{

    area = "in";
    areaname = "The Angle";
    land = "Eriador";
    areatype = 8;
    areadesc = "heavy woods";
    grass = "green";

    extraline = "The Angle is created by the merging of the two "+
    "great rivers, Mitheithel and Bruinen. The Great East Road "+
    "zig zags between the rivers from the Last Bridge in the west "+
    "to the stone bridge, crossing the River Bruinen and leading "+
    "to Rivendell, in the east. Further west the road "+
    "continues through the Lone-lands and "+
    "circles around Weathertop and the Midgewater Marshes "+
    "eventually reaching Bree.\n";

    add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
}
