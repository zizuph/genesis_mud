inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the Bedellin camp");
   set_long("You are within the camp of the Bedellin nomads, the "+
      "ever-present sand slightly less obvious here then "+
      "elsewhere in the waste. "+
      "Their sand-colored tents surround you, and from within come the "+
      "sounds of life, so rare here in the desert. "+
      "An entrance leads into the gigantic tent that lies directly to the "+
      "west. Many Bedellin warriors are guarding the entrance. "+
      "The clear desert sky is dominated by the harsh Kaladian sun, its "+
      "relentless rays baking the land beneath it.\n");
   add_item(({"bedellin camp","camp"}),"It surrounds you from all sides.\n");
   add_item(({"ever-present swirling sand","ever-present sand","swirling sand","sand"}),
      "The light brown sand lies scattered around the camp.\n");
   add_item(({"sand-colored tents","tents","tent"}),"The dwellings used "+
      "most commonly by the nomadic Bedellin, perfect for a people "+
      "constantly on the move.\n");
   add_item(({"clear desert sky","clear sky","desert sky","sky"}),
      "The astoundingly blue sky is clear of clouds, more evidence of the "+
      "dry nature of this place.\n");
   add_item(({"kaladian sun","sun"}),"A harsh yellow orb that bakes "+
      "this land to a scorching temperature.\n");
   add_item(({"land"}),"The desert landscape of the Great Kalad Waste.\n");
   add_item(({"entrance"}),"An opening into the gigantic tent.\n");
   add_item(({"gigantic tent"}),"The largest tent in the Bedellin camp, its "+
      "centralized location indicates its importance, probably the abode of the "+
      "tribe's sheik.\n");
   add_item(({"many bedellin warriors","many bedellin","many warriors","bedellin warriors","warriors","warrior"}),
      "Dressed in bleach white abas and armed with an assortment of weapons, "+
      "ranging from scimitars to spears, the Bedellin look quite capable "+
      "of keeping out any unwanted intruders.\n");
   add_exit(CPASS(desert/camp/c19),"west","@@move",-1);
   add_exit(CPASS(desert/camp/c17),"east",0,2);
   add_exit(CPASS(desert/camp/c27),"south",0,2);
}
move()
{
   if(TP->query_gender() != 0)
      {
      write("You try to enter the Sheik's tent, but are suddenly thrown out "+
         "by the mob of Bedellin warriors.\n");
      write("One Bedellin warrior shouts: Stay out of here, woman!\n");
      say(QCTNAME(TP) + " tries to enter the Sheik's tent, but is suddenly thrown out "+
         "by the mob of Bedellin warriors.\n");
      say("One Bedellin warrior shouts: Stay out of here, woman!\n");
      return 1;
   }
   write("The Bedellin warriors look at you suspiciously and then "+
      "cautiously let you inside, after disarming you of any and all "+
      "weapons.\n");
   TP->command("drop weapons");
   return 0;
}
