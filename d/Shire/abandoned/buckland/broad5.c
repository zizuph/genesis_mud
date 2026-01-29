inherit "/d/Shire/eastroad/eroad";
#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* Put something here like Mithlond defs or Bree defs that describe that area. */

#define EXIT1 BUCK_DIR + "broad6","south",0,1
#define EXIT2 BUCK_DIR + "bucklebury/buroad5","northeast",0,1

void
create_room()
{
   
   area = "in southern";
   areaname = "Buckland";
   land = "the Shire";
   areatype = 8;
   areadesc = "field";
   grass = "green";


    extraline = "There are slightly rolling hills to the east and west "+
    "of you.  To the northeast is the entrance to the village of "+
    "Bucklebury, and the road also continues southwards towards a fork "+
    "in the road.";

    add_item(({"hills","field","rolling hills","green hills"}),"The hills "+
      "are covered with green grass and flowers, and there are also "+
      "a few patches where the farmers living here decided that the "+
      "hills weren't too steep to plant crops.\n");
    add_item(({"village","large village"}),"You can see a large village "+
      "to the north of you.  If you've followed the road correctly, it "+
      "should be Bucklebury.\n");
    add_item(({"road"}),"The road is a dirt road, with some small rocks "+
    "found along it, along with some deep wagon ruts.\n");
   
   
   
   add_exit(EXIT1);
   add_exit(EXIT2);
   make_the_room();
}
