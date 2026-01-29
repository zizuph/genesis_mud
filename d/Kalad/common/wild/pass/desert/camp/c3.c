inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Desert path");
   set_long("You are travelling along a narrow twisting path in the Great "+
      "Kalad Waste. Swirling sand surrounds you, impairing your vision "+
      "and clogging your nostrils. The unrelenting heat seems to sap the "+
      "strength from your very being.\n"+
      "The path wanders to the north and southwest.\n");
   add_item(({"desert path","path","narrow twisting path","narrow path","twisting path"}),
      "A cleared trail within the waste, where slightly less sand is "+
      "billowing about.\n");
   add_item(({"swirling sand","sand"}),"It is constantly swirling "+
      "about you, limiting your sight to just a few yards.\n");
   add_exit(CPASS(desert/camp/c2),"north",0,3);
   add_exit(CPASS(desert/camp/c4),"southwest",0,3);
}
