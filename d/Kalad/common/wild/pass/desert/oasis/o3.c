inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Oasis");
   set_long("You are in an isolated spot within the oasis.\n"+
      "Tall and leafy palm trees tower above you, swaying ever so slightly "+
      "in the wind. The swirling dust of the Great Kalad Waste is absent "+
      "here. All about you, lush grasses along with fruit-bearing bushes "+
      "provide a stark contrast to the desert beyond the trees. You can "+
      "almost smell the presence of the water, which appears to lie in the "+
      "east, where the vegetation is much heavier.\n");
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
   add_item(({"ground"}),"It isn't visible, due to the abundance of "+
      "vegetation.\n");
   add_exit(CPASS(desert/oasis/o6),"east");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/d_lion));
      ob1 -> move_living("M",TO);
      tell_room(TO,"A lion bounds into view and lands before you!\n");
   }
}
