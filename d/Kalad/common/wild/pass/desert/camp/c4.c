inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Desert path");
   set_long("You are travelling along a narrow twisting path in the Great "+
      "Kalad Waste. All around you, sand swirls and twists, impairing "+
      "your vision and impeding your travel. The relentless heat of the "+
      "Kaladian sun beats down on you from above, sapping the strength "+
      "from your body.\n"+
      "A camp lies just to the southwest.\n"+
      "The path wanders to the northeast and southwest.\n");
   add_item(({"desert path","path","narrow twisting path","narrow path","twisting path"}),
      "A cleared trail within the waste, where slightly less sand is "+
      "billowing about.\n");
   add_item(({"swirling sand","twisting sand","sand"}),"It is constantly blowing "+
      "about you, limiting your sight to just a few yards.\n");
   add_item(({"kaladian sun","sun"}),"A harsh, brilliant orb of light "+
      "that heats this land to terrible temperatures.\n");
   add_item(({"camp"}),"It looks like a Bedellin nomad camp, with "+
      "many smaller tents surrounding a much larger, central tent.\n");
   add_item(({"smaller tents","tents","tent","larger tent","central tent"}),
      "The swirling sand of the waste procludes you from gaining any "+
      "meaningful details from here.\n");
   add_exit(CPASS(desert/camp/c3),"northeast",0,3);
   add_exit(CPASS(desert/camp/c5),"southwest","@@msg",2);
}
msg()
{
   write("You leave the trail behind and enter the camp.\n");
   return 0;
}
