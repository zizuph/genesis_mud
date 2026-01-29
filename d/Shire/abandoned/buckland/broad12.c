inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 BUCK_DIR + "broad6","northwest",0,1
#define EXIT2 BUCK_DIR + "broad13","southeast",0,1

void
create_room()
{
   
   area = "in southern";
   areaname = "Buckland";
   land = "the Shire";
   areatype = 8;
   areadesc = "grassy field";
   grass = "green";
   
   extraline = "The fields that surround you are lush and green "+
     "with crops growing in them.  They look remarkably well-tended.  "+
    "You feel very alone here, as there are only the fields for as far "+
      "as the eye can see.";
    add_item(({"fields","field","crop"}),"These crops growing in the "+
    "fields are among the best you've ever seen.  It's easy to tell that "+
    "someone has spent a lot of time looking after them.\n");
    add_item(({"road"}),"The road is a dirt road, with some small rocks "+
    "found along it, along with some deep wagon ruts.\n");
   
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   make_the_room();
}
