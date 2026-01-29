#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser3","west",0,1
#define EXIT2 ERE_DIR + "ser5","northeast",0,1

void
create_er_room ()
{
   
   area = "just off of";
   areaname = "the River Bruinen";
   land = "Eriador";
   areatype = 5;
   areadesc = "bank";
   
   
    extraline ="There are trees on all sides of you, except to "+
      "west, where there is a path, and to the northeast, where "+
      "the River Bruinen is flowing.  There is no bridge over the "+
       "river, but luckily the currents do not appear to be very "+
       "strong or fast.";
    add_item(({"river","River Bruinen","water"}),"The water "+
       "looks like it is cold, so it will be uncomfortable "+
       "to cross, even though it is possible.\n");
     add_item(({"bank","banks","rocky bank"}),"The rocks on the bank "+
        "are worn down, probably from the water of the river when "+
        "it rises and overflows onto them.\n");
   add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
}
