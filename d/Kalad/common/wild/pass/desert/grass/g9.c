inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define HAVE_USED_POOL "_have_used_pool"
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;
object ob7;
object ob8;
object ob9;
object ob10;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("An oasis in the rolling grassland");
   set_long("A suprisingly lush, rolling grassland spreads out before "+
      "you. The tall grasses bend slightly in the warm desert wind, which "+
      "is continually blowing from the east. A crystal clear fountain of "+
      "water is here, around which a shallow pool has formed. Tall, leafy "+
      "palm trees crowd around the pool, shading you from the heat of "+
      "the Kaladian sun.\n");
   add_item(({"lush grassland","rolling grassland","grassland"}),
      "A slightly elevated region here within the Great Kalad Waste, that "+
      "unlike the rest of the region is filled with a relative abundance "+
      "of plant and animal life.\n");
   add_item(({"tall grasses","grasses","tall grass","grass"}),
      "The golden yellow grass grows to a height of nearly four feet, waving "+
      "and undulating as the wind whips among them, creating the appearance "+
      "of a sea of grass.\n");
   add_item(({"kaladian sun","sun"}),"It hangs in the sky, one of the "+
      "constant reminders to you of the oppressive heat of this land.\n");
   add_item(({"sky"}),"Colored the deepest blue, it is completely free "+
      "of clouds.\n");
   add_item(({"crystal clear fountain","clear fountain","fountain"}),
      "Pure, cleansing water sprays forth from it, giving nourishment to this "+
      "water-starved land.\n");
   add_item(({"pure water","cleansing water","water"}),"It is clear and just "+
      "the slightest bit warm.\n");
   add_item(({"shallow pool","pool"}),"A body of water that has formed "+
      "due to the natural spring at its heart. The pool is roughly five "+
      "feet in depth and around two dozen feet across at the widest point. "+
      "Numerous palm trees surround it.\n");
   add_item(({"tall palm trees","leafy palm trees","tall trees","leafy trees","palm trees","trees","tree"}),
      "Their giant leaves have formed an encovering canopy over the pool, "+
      "providing a haven from the heat of the Kaladian sun.\n");
   add_exit(CPASS(desert/grass/g8),"west");
   add_exit(CPASS(desert/grass/g4),"northwest");
   add_exit(CPASS(desert/grass/g5),"north");
   add_exit(CPASS(desert/grass/g10),"east");
   add_exit(CPASS(desert/grass/g16),"southeast");
   add_exit(CPASS(desert/grass/g15),"south");
   add_exit(CPASS(desert/grass/g14),"southwest");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/g_snake));
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/gazelle_m));
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(CPASS(npc/gazelle_f));
      ob3 -> move_living("M",TO);
   }
   if(!ob4)
      {
      ob4 = clone_object(CPASS(npc/gazelle_f));
      ob4 -> move_living("M",TO);
   }
   if(!ob5)
      {
      ob5 = clone_object(CPASS(npc/wild_dog));
      ob5 -> move_living("M",TO);
   }
   if(!ob6)
      {
      ob6 = clone_object(CPASS(npc/d_falcon));
      ob6 -> move_living("M",TO);
   }
   if(!ob7)
      {
      ob7 = clone_object(CPASS(npc/d_vulture));
      ob7 -> move_living("M",TO);
   }
   if(!ob8)
      {
      ob8 = clone_object(CPASS(npc/d_lion));
      ob8 -> move_living("M",TO);
   }
   if(!ob9)
      {
      ob9 = clone_object(CPASS(npc/d_hare));
      ob9 -> move_living("M",TO);
   }
   if(!ob10)
      {
      ob10 = clone_object(CPASS(npc/d_wolf));
      ob10 -> move_living("M",TO);
      ob2 -> team_join(ob3);
      ob2 -> team_join(ob4);
      tell_room(TO,"Several animals arrive at the pool of water.\n");
   }
}
void
init()
{
   ::init();
   AA(drink,drink);
}
int
drink(string str)
{
   if(!str || str != "water")
      {
      NF("You can't drink '" + str + "'.\n");
      return 0;
   }
   if(TP->query_prop(HAVE_USED_POOL))
      {
      write("You take a drink of the water from the pool.\n");
      say(QCTNAME(TP) + " takes a drink of the water from the pool.\n");
      return 1;
   }
   else
      write("You take a drink of the water from the pool.\n");
   say(QCTNAME(TP) + " takes a drink of the water from the pool.\n");
   set_alarm(3.0,0.0,"effect");
   return 1;
}
void
effect()
{
   TP->heal_hp(500);
   TP->add_prop(HAVE_USED_POOL,1);
   write("You feel refreshed.\n");
   say(QCTNAME(TP) + " looks refreshed.\n");
   return;
}
