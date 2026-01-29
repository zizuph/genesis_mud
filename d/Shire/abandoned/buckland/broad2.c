inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 BUCK_DIR + "broad1","north",0,1
#define EXIT2 BUCK_DIR + "broad3","south",0,1
#define EXIT3 BUCK_DIR + "broad8","southeast",0,1

void
create_room()
{
   
   area = "in northern";
   areaname = "Buckland";
   land = "the Shire";
   areatype = 8;
   areadesc = "field";
   grass = "green";


    extraline = "There are fields to the east and west of you with some "+
    "crops growing in them.  Here there is a fork in the road.  The "+
    "road heading south seems to be much more used than the one heading "+
    "to the southeast.";
    add_item(({"fields","field","crop"}),"These crops growing in the "+
    "fields are among the best you've ever seen.  It's easy to tell that "+
    "someone has spent a lot of time looking after them.\n");
    add_item(({"road"}),"The road is a dirt road, with some small rocks "+
    "found along it, along with some deep wagon ruts.\n");
   
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
    add_exit(EXIT3);
   make_the_room();
}
