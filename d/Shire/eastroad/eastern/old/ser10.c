#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser9","northwest",0,1
#define EXIT2 ERE_DIR + "ser11","east",0,1

void
create_er_room()
{

    area = "just west of";
    areaname = "the River Bruinen";
    land = "Eriador";
    areatype = 1;
    areadesc = "path";


    extraline ="You can hear the water of the River Bruinen "+
    "flowing to the east.  Trolls must use this path a lot, as "+
    "there is a lot of trash lying around in the grass.";
    add_item(({"trash"}),"The trolls have left all sorts of garbage "+
      "and evidence of their stay here.  They definitely aren't the "+
      "neatest of creatures.\n");
    add_item(({"grass","grassy path","ground"}),"The grass here has "+
      "been walked over quite a bit recently and the grass is not "+
      "in the best of shape.  There is also a lot of trash left lying "+
      "around on it.\n");
    add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
}
