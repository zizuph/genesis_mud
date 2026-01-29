inherit "/d/Shire/eastroad/villagemaker";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 SB_DIR + "sroad1","north",0,1
#define EXIT2 SB_DIR + "sroad3","south",0,1
#define EXIT3 SB_DIR + "/burrows/burrow1_1","east",0,1



void
create_room()
{
   areaname = "Standelf";
   land = "Buckland";
   areatype = 2;
   areadesc = "road";
 

    extraline = "You can see a lot of tiny smials around lining the "+
    "road, and there is one directly to your east.";
    add_item(({"road"}),"The road is dirt and a bit of gravel, and looks "+
      "very travelled.\n");
    add_item(({"windows","window"}),"The windows are so shiny and sparkling "+
      "that it is almost impossible to see through them.\n");

   add_exit(EXIT1);
   add_exit(EXIT2);
    add_exit(EXIT3);
   make_the_room();
}





