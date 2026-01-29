inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Oasis");
   set_long("Tall, leafy palm trees rise above you, swaying slightly "+
      "in the desert wind. The swirling dust of the Great Kalad Waste is "+
      "absent here, instead, lush grasses and fruit-bearing bushes "+
      "surround you. Yet, only a few dozen yards from here, a profusion of "+
      "dust whirls about, the trademark of the wasteland you have "+
      "travelled through. The rich profusion of life here can only "+
      "originate from the presence of life-giving water, which must lie "+
      "to the south where the vegetation is thicker.\n");
   add_item(({"tall palm trees","leafy palm trees","palm trees","tall trees","palm trees","trees","tree"}),
      "They provide shade from the harsh Kaladian sun and help filter "+
      "away the sand from the desert.\n");
   add_item(({"harsh kaladian sun","harsh sun","kaladian sun","sun"}),
      "Its harsh light is muted here, though still strong enough to blind "+
      "those foolish enough to gaze at it.\n");
   add_item(({"lush grasses","grasses","grass"}),"Long and flowing, it "+
      "covers the ground like a sea of green.\n");
   add_item(({"fruit-bearing bushes","bushes","bush"}),"Large, juicy "+
      "fruits are growing upon them. They look quite tasty.\n");
   add_item(({"dust","sand"}),"It lies dozens of yards from here, a "+
      "constant reminder to you of your location within a desert "+
      "wasteland.\n");
   add_item(({"vegetation"}),"There are so many plants here that you "+
      "almost forget you are within a massive desert.\n");
   add_item(({"ground"}),"It isn't visible due to the abundance of "+
      "vegetation.\n");
   add_exit(CPASS(desert/d28),"northeast","@@msg");
   add_exit(CPASS(desert/oasis/o2),"south");
   set_alarm(1.0,0.0,"reset_room");
}
msg()
{
   write("You step out from the oasis, the furnace-like heat of the "+
      "desert greeting you like death itself.\n");
   return 0;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/gazelle_m));
      ob1 -> move_living("M",TO);
      tell_room(TO,"A strong nimble gazelle emerges from the surrounding bushes.\n");
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/gazelle_f));
      ob2 -> move_living("M",TO);
      tell_room(TO,"A nimble gazelle appears from behind some bushes.\n");
      ob1 -> team_join(ob2);
   }
}
