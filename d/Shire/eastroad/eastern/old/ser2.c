#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser1","west",0,1
#define EXIT2 ERE_DIR + "ser3","east",0,1
#define EXIT3 ERE_DIR + "ser8","southeast",0,1

void
create_er_room ()
{
   
   area = "northeast of";
   areaname = "the Last Bridge";
   land = "Eriador";
   areatype = 5;
   areadesc = "path";
   grass = "green";
   
  extraline = "To the southwest, you can vaguely make out the Last "+
   "Bridge, and the road that leads to it.  To the east, the path "+
   "continues towards the Bruinen, although the path doesn't seem to be "+
   "in the best of shape.  The trees hang low over the path, scratching "+
   "you as you try to make your way, and there are twigs and large "+
    "brances scattered along the path, causing you to choose your "+
    "steps carefully.  You can see a slight opening in the trees "+
    "to the southeast.";
   

     add_item(({"twigs"}),"The twigs are scattered all along the "+
      "path.  They probably just died and fell off of the trees, or "+
      "were blown off by the wind.\n");

     add_item(({"branches","large branches"}), "The branches are "+
     "lying in the middle of the path.  They look too big and sturdy "+
     "to have fallen off by themselves, so you wonder who or what "+
     "broke them off.\n");

    add_item(({"path","rocky path"})," The path has twigs and "+
     "branches on it, as well as the rocks.  Luckily you are "+
     "sure-footed enough that is won't bother you.\n");

   add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
  add_exit(EXIT3);
}
