inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
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
   add_exit(CPASS(desert/camp/c39),"west",0,2);
   add_exit(CPASS(desert/camp/c29),"north",0,2);
   set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/bed_ewar");
      ob1 -> my_stuff();
      ob1 -> move_living("xxx",TO);
   }
}
