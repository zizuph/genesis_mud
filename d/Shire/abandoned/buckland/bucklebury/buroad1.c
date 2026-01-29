inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BUCK_DIR + "broad4","north",0,1
#define EXIT2 BB_DIR + "buroad2","south",0,1
#define EXIT3 BB_DIR + "buroad6","east",0,1



void
create_room()
{

   area = "in";
   areaname = "Bucklebury";
   land = "the Shire";
   areatype = 0;
   areadesc = "road";
   grass = "green";


   extraline = "The main road leads either north out of Bucklebury "+
   "or east into the heart of it.  To the southeast, you see a large "+
    "mound that you recognize to be Brandy Hall.";
    add_item(({"Brandy Hall","mound","large mound"}),"This mound "+
      "is by far the largest one you've seen in the area.  It looks "+
      "big enough to house many hobbits, even by hobbit standards.\n");
    add_item(({"road","main road"}),"The road is a dirt one and has "+
      "many ruts and a few holes in it.  It is easy to tell by looking "+
      "at it that it is the main road used in Buckland.\n");


   add_exit(EXIT1);
   add_exit(EXIT2);
   add_exit(EXIT3);


   make_the_room();
}


