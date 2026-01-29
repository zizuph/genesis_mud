inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "buroad4","northeast",0,1
#define EXIT2 BUCK_DIR + "broad5","southwest",0,1
#define EXIT3 BB_DIR + "buroad15","east",0,1



void
create_room()
{

   area = "in";
   areaname = "Bucklebury";
   land = "the Shire";
   areatype = 0;
   areadesc = "road";
   grass = "green";


    extraline = "This road leads southwest out of Bucklebury, or you "+
    "go back into it by going either east or northeast.  To the northeast "+
    "you see a large mound that is Brandy Hall, and to the east you can "+
    "other smaller burrows.";

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


