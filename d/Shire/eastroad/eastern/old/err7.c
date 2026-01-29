#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err6","northwest",0,1
#define EXIT2 ERE_DIR + "err8","southwest",0,2

void
create_er_room()
{

    area = "near";
    areaname = "the Last Bridge";
    land = "Eriador";
    areatype = 8;
    areadesc = "heavy woods";
    grass = "green";

    extraline = "The Last Bridge, is not really the last bridge, "+
    "since further east is the stone bridge crossing the River "+
    "Bruinen. This close to the Last Bridge, the gurgling "+
    "sounds of the Mitheithel can be heard. The Great East "+
    "Road has turns, uphill, to the southwest and downhill, "+
    "to the northwest. Far to the east, lays the legendary "+
    "valley of Rivendell, nestled into the Misty Mountains. It "+
    "is said the home of Elrond can be found there.";

    add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");


    add_exit(EXIT1);
    add_exit(EXIT2);
}
