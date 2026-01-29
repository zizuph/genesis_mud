#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser11","west",0,1
#define EXIT2 ERE_DIR + "ser13","northeast",0,1

void
create_er_room()
{
   
   area = "of";
   areaname = "the River Bruinen";
   land = "Eriador";
   areatype = 0;
   areadesc = "swift part";
   
   
     extraline ="The river is cold, making you feel quite "+
        "uncomfortable, and the water swirls about you making the "+
      "crossing difficult.  To the southwest, you can make out a "+
      "dense forest, and to the northeast, the Misty Mountains "+
      "loom over you.";
    add_item(({"river","River Bruinen","water"}),"The water "+
        "is cold, wet and filled with all sorts of life that "+
        "you would prefer not to think about.\n");
   add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");
    add_item(({"mountains","Misty Mountains"}),"The mountains "+
      "are just ahead of you to the northeast, and a journey "+
      "that way would probably be very long and tiring.\n");
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
}
