#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR +"err2","east",0,1
#define EXIT2 ERE_DIR +"err3","south",0,1
#define EXIT3 ERE_DIR +"err4","southeast",0,2

void
create_er_room()
{

    area = "not far"; /* Distance from areaname */
    areaname = "Rivendell";
    land = "Eriador";
    areatype = 8;
    areadesc = "wooded area";
    grass = "green";

    extraline = "This is the last stretch of the Great East Road "+
    "running between Bree to the west and the legendary Rivendell "+
    "to the east. This portion of the road is between The Last "+
    "Bridge, spanning the River Mitheithel, and the stone bridge "+
    "spanning the River Bruinen. The road is steep, rising to the "+
    "west and dropping sharply as it approaches Rivendell to the "+
    "east. Heavy woods and sharp bends in the road prevent the "+
    "traveler from seeing what lies beyond.\n";

    add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
    add_exit(EXIT3);
}
