inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BUCK_DIR + "broad14","northwest",0,1
#define EXIT2 SB_DIR + "sroad2","south",0,1



void
create_room()
{

   area = "in";
   areaname = "northern Standelf";
   land = "the Shire";
   areatype = 0;
   areadesc = "road";
   grass = "green";


    extraline = "The road leads northwest out of Buckland, or south "+
    "into the small village of Standelf. There doesn't seem to be "+
    "anything too remarkable about the village from here, but a "+
    "travel through it might be worthwhile.";
    add_item(({"road","main road"}),"The road is a dirt one and has "+
      "many ruts and a few holes in it.  It is easy to tell by looking "+
      "at it that it is the main road used in Buckland.\n");


   add_exit(EXIT1);
   add_exit(EXIT2);


   make_the_room();
}


