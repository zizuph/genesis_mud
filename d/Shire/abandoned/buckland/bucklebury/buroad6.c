inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

#define EXIT1 BB_DIR + "buroad1","west",0,1
#define EXIT2 BB_DIR + "buroad7","east",0,1



void
create_room()
{
   area = "in northern";
   areaname = "Bucklebury";
   land = "the Shire";
   areatype = 0;
   areadesc = "dirt road";
   grass = "green";

    extraline = "This road leads over a gentle slope, just north of Brandy "+
    "Hall.  Luckily the slope is not very steep so walking is not too "+
    "difficult, which means you can enjoy the scenery as you wander "+
    "along.";


    add_item(({"road","dirt road"}),"This is a dirt road that looks "+
      "like it is used quite frequently.\n");
    add_item(({"slope","gentle slope"}),"The hill is not very steep, "+
      "being just tall enough to house the hobbits who live underneath "+
      "in Brandy Hall.\n");
    add_item(({"scenery"}),"The scenery here is very nice to look at.  "+
      "You are surrounded by fields of tall grass, flowers and herbs, and "+
      "can also see some very nice hobbit holes and houses.\n");

   add_exit(EXIT1);
   add_exit(EXIT2);

   make_the_room();
}


