inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/buckland/buckdefs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 BUCK_DIR + "broad13","northwest",0,1
#define EXIT2 SB_DIR + "sroad1","southeast",0,1

void
create_room()
{
   
   area = "just northeast of";
   areaname = "Standelf";
   land = "the Shire";
   areatype = 8;
   areadesc = "grassy field";
   grass = "green";
   
   extraline = "The fields that surround you are lush and green "+
     "with crops growing in them.  They look remarkably well-tended.  "+
    "Although the fields seem to surround you on all sides, you can vaguely "+
    "make out a small village somewhere to the south of you.";
    add_item(({"fields","field","crop"}),"These crops growing in the "+
    "fields are among the best you've ever seen.  It's easy to tell that "+
    "someone has spent a lot of time looking after them.\n");
    add_item(({"road"}),"The road is a dirt road, with some small rocks "+
    "found along it, along with some deep wagon ruts.\n");
   
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   make_the_room();
}
