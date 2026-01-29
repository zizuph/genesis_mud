inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 BUCK_DIR + "broad7","southwest",0,1
#define EXIT2 BUCK_DIR + "broad5","north",0,1
#define EXIT3 BUCK_DIR + "broad12","southeast",0,1

void
create_room()
{
   
   area = "in southern";
   areaname = "Buckland";
   land = "the Shire";
   areatype = 8;
   areadesc = "field";
   grass = "green";


    extraline = "You are standing at a fork in the road.  You can keep "+
    "following it to the southeast, which will take you to Standelf, or "+
    "to the southwest which will take you to the ferry.";

    add_item(({"road"}),"The road is a dirt road, with some small rocks "+
    "found along it, along with some deep wagon ruts.\n");
   
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
    add_exit(EXIT3);
   make_the_room();
}
