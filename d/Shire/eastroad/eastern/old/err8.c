#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err7","northeast",0,1
#define EXIT3 ERE_DIR + "err14","west",0,1
#define EXIT2 ERE_DIR + "ser1","east",0,1

void
create_er_room()
{

    area = "just north of";
    areaname = "the Last Bridge";
    land = "Eriador";
    areatype = 8;
    areadesc = "heavy woods";
    grass = "green";

    extraline = "Directly south is the Last Bridge crossing the "+
    "River Mitheithel. Across the bridge the Great East Road "+
    "continues westward, through the Lone Lands and skirting "+
    "around the Weather Hills and the Midgewater Marshes, "+
    "eventually reaching Bree. To northeast, the road takes a "+
    "zig zagging, steep downhill path, through a heavily wooded "+
    "area, leading to the River Bruinen and the Rivendell plateau.";

    add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
}
