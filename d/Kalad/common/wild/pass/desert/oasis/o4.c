inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Oasis");
   set_long("You are in a dark, isolated spot within the oasis.\n"+
      "Tall leafy palm trees ring this clearing, blocking out all but a "+
      "few of the sun's rays. The ground is blanketed with lush grasses, "+
      "while the edge of the clearing is lined with many fruit-bearing "+
      "bushes. At the center of this clearing, where a lone shaft of "+
      "sunlight filters through the canopy, lies an old stone well.\n");
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
   add_item(({"clearing"}),"A roughly circular spot where only the "+
      "grass grows.\n");
   add_item(({"canopy"}),"The large leaves of the palm trees form a "+
      "protective shield above you, blocking out the harsh rays of the "+
      "Kaladian sun and plunging this place into a state of semi-darkness "+
      "and cool temperatures.\n");
   add_item(({"old stone well","old well","stone well","well"}),
      "So ancient is it, that it looks as if it may collapse in upon itself "+
      "at any moment. Peering down its depths you can see nothing but "+
      "darkness, and even sound seems muted, for not a whisper or echo "+
      "can be heard from it.\n");
   add_item(({"darkness"}),"Its black...\n");
   add_exit(CPASS(desert/oasis/o6),"north");
}
void
init()
{
   ::init();
   AA(enter,enter);
}
int
enter(string str)
{
   if(!str || str != "well")
      {
      NF("What do you wish to enter?\n");
      return 0;
   }
   write("You slowly but carefully begin climbing down the well.\n");
   say(QCTNAME(TP) + " slowly but surely begins climbing down the well.\n");
   set_alarm(3.0,0.0,"climb_down");
   return 1;
}
void
climb_down()
{
   TP->move_living("down into the well","/d/Kalad/common/wild/pass/desert/oasis/u1");
   return;
}
