#pragma save_binary

inherit "/d/Shire/eastroad/std/er_base";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 ERE_DIR + "ser6","southwest",0,1
#define EXIT2 "/d/Rhovanion/common/shirelink","southeast",0,1
#define EXIT3 ERE_DIR + "ser21","northeast",0,1

void
create_er_room()
{
   
   area = "in";
   areaname = "the Misty Mountains";
   land = "Eriador";
   areatype = 5;
   areadesc = "trail";
   
    extraline ="You are surrounded by the almost vertical sides "+
      "of the mountains as you make your way along the narrow "+
      "trail through them.  You can vaguely make out the River "+
      "Bruinen to the southwest, and just ahead to the northeast "+
      "is Wilderland.  There is a small trail leading to the "+
      "northeast, and you can see a large shadow coming from something "+
"on it. The mountain trail continues to the southeast.";
    add_item(({"shadow","large shadow"}),"The shadow is large "+
      "and shapeless.\n");
    add_item(({"mountains","Misty Mountains"}),"The mountains "+
      "are not far from you to the southwest, and a journey "+
      "that way would probably be very long and tiring.\n");
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
    add_exit(EXIT3);
}
