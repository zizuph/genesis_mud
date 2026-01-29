#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "err8","west",0,1
#define EXIT2 ERE_DIR + "ser2","east",0,1

void
create_er_room ()
{
   
    area = "northeast of";
   areaname = "the Last Bridge";
   land = "Eriador";
   areatype = 5;
   areadesc = "path";
   grass = "green";

   extraline = "You are surrounded on all sides by trees, except "+
     "to the west, which has a road leading back to the Last Bridge "+
     "and to the east, where a path takes you closer to the Bruinen.";
   
   
   add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");
   add_item(({"path","rocky path"})," The path is rocky and also has "+
     "some twigs and leaves on it, that have fallen from the trees.\n");
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
}
