inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 BUCK_DIR + "broad8","west",0,1
#define EXIT2 BUCK_DIR + "broad10","southeast",0,1

void
create_room()
{
   
   area = "in northern";
   areaname = "Buckland";
   land = "the Shire";
   areatype = 8;
   areadesc = "field";
   grass = "green";


    extraline = "There are rolling green hills surrounding "+
    "you, and the road continues to the west and to the southeast.";
    add_item(({"field","hills","rolling hills","green hills"}),"The hills "+
      "are covered with green grass and flowers, and there are also "+
      "a few patches where the farmers living here decided that the "+
      "hills weren't too steep to plant crops.\n");
    add_item(({"road"}),"The road is a dirt road, with some small rocks "+
      "found along it, along with some deep wagon ruts.  This road is "+
      "more narrow than the one to the northwest.\n");
   
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   make_the_room();
}
