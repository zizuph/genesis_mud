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
      "The Caravan Route lies just to the northeast.\n"+
      "The path wanders to the northeast and south.\n");
   add_item(({"desert path","path","narrow twisting path","narrow path","twisting path"}),
      "A cleared trail within the waste, where slightly less sand is "+
      "billowing about.\n");
   add_item(({"swirling sand","sand"}),"It is constantly swirling "+
      "about you, limiting your sight to just a few yards.\n");
   add_item(({"caravan route","route"}),"A cobblestoned roadway that "+
      "bears the effects of heavy usage and the harsh environment in its "+
      "cracked and faded surface.\n");
   add_exit(CPASS(desert/d22),"northeast","@@msg",3);
   add_exit(CPASS(desert/camp/c2),"south",0,3);
}
msg()
{
   write("With a sense of relief, you step back onto the Caravan Route, "+
      "leaving behind the sand-blown trail.\n");
   return 0;
}
