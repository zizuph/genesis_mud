#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser2","west",0,1
#define EXIT2 ERE_DIR + "ser4","east",0,1
#define EXIT3 ERE_DIR + "ser15","northwest",0,1

void
create_er_room()
{
   
   area = "west of";
   areaname = "the River Bruinen";
   land = "Eriador";
   areatype = 5;
   areadesc = "path";
   grass = "green";
   
   
    extraline ="You can hear the sound of running water to the "+
      "east signifying that you must be getting closer to the "+
      "Bruinen, and luckily it looks as though the forest is "+
      "somewhat less dense.  To the west, the path looks much less "+
      "inviting due to the heavy woods.  There is a clearing to the "+
      "northwest that looks like it is used very frequently."+
       "Perhaps it would be a good place to stop for a while.";
    add_item(({"path","rocky path"}),"The path has some twigs and "+
       "leaves on it and seems to be in quite good shape, compared "+
       "to some of the other paths nearby that you have travelled.\n");
    add_item(({"clearing"}),"The clearing looks well used, "+
      "although you cannot tell from here if there is still "+
       "anybody or anything there.\n");
    add_item(({"trees","treetops","woods","heavy woods"}), "The "+
      "trees and woods seem to be teeming with life. Sounds of "+
      "music and laughter come from all directions.\n");
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);
}
