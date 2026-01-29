/* File :/d/Shire/common/trollsh/riv6no.c */

#include "defs.h"
inherit STAND_EROAD;


object troll;

create_er_shaws()
{
   set_short("Great Eastroad, Rocks");
   set_long(
      "You are walking in between some trees, standing next to "
      +"some huge rocks. From here it is easier to see what shape "
      +"they have. There are trees all around this opening, and you "
      +"can see a hill to your north. Maybe you can climb it from "
      +"here too. "
   );
   
   add_item(({"hill"}),
      "The hill looks too steep to climb from here, maybe you can \n"+
      "try to climb up some other place.\n"
   );
   
   add_item(({"rocks","boulders","boulder"}),
      "They are really big, and it's difficult to "
      +"see what these once were. \n" );
   
   /*
   {
      if (TP->query_skill(SS_AWARENESS) > 30)
         
      return"The rocks have the shape of trolls, they are huge, almost "
      +"20 feet high where they stand.  You can also see that the trolls "
      +"were very primitive, wearing no armour, only a torn up blood skin "
      +"around their bodies. \n";
      else
         return  "The boulders have a strange shape... they remind you of something "
      +"nasty and evil. You feel all scared when you look at them, and your "
      +"bones start to shiver. \n";
   }
   */
   
   SOUTH("rivend6");
   
   reset();
}



reset_er_shaws()
{
   if (!troll)
      {
      troll = clone_object(STAND_MONSTER + "rocktroll");
      troll -> move(this_object());
   }
   
}
