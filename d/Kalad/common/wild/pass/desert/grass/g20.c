inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define HAVE_USED_POOL "_have_used_pool"
object ob1;
object ob2;
object ob3;
object ob4;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Rolling grassland");
   set_long("A lush, rolling grassland dominates your field of vision, "+
      "appearing as if you were lost in a sea of grass. Tall grasses rise "+
      "all around you, reaching past waist height. A constant wind from "+
      "the east causes the grass to sway back and forth. A splashing "+
      "fountain of water is here, around which a large pool has formed. "+
      "Shading palm trees have grown along the pool's edge, providing "+
      "welcome shade from the heat.\n");
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
   add_item(({"sky"}),"Colored the deepest blue, it is completely free of "+
      "clouds.\n");
   add_item(({"splashing fountain","fountain"}),"A small column of "+
      "water at the center of the spring.\n");
   add_item(({"water"}),"Crystal clear and just the slightest bit warm, "+
      "its value is beyond measure in this land.\n");
   add_item(({"shading palm trees","shading trees","palm trees","trees","tree"}),
      "Tall and possesing a great many leaves, they help to shade this "+
      "oasis of life.\n");
   add_exit(CPASS(desert/grass/g19),"west");
   add_exit(CPASS(desert/grass/g12),"northwest");
   add_exit(CPASS(desert/grass/g13),"north");
   add_exit(CPASS(desert/grass/g14),"northeast");
   add_exit(CPASS(desert/grass/g21),"east");
   add_exit(CPASS(desert/grass/g27),"southeast");
   add_exit(CPASS(desert/grass/g26),"south");
   add_exit(CPASS(desert/grass/g25),"southwest");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/d_vulture));
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/d_lion));
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(CPASS(npc/d_hare));
      ob3 -> move_living("M",TO);
   }
   if(!ob4)
      {
      ob4 = clone_object(CPASS(npc/d_wolf));
      ob4 -> move_living("M",TO);
      tell_room(TO,"A few animals arrive at the pool.\n");
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
