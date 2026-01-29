inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Rolling grassland");
   set_long("Amazingly enough, you find yourself within a lush, rolling "+
      "grassland here in the very heart of the Great Kalad Waste. Tall "+
      "grasses surround you, reaching past your waist, as they sway "+
      "slightly from the constant westerly wind. Up in the sky, the heat "+
      "of the Kaladian sun continually reminds you of its presence.\n");
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
   add_exit(CPASS(desert/grass/g29),"west");
   add_exit(CPASS(desert/grass/g23),"northwest");
   add_exit(CPASS(desert/grass/g24),"north");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/d_falcon));
      ob1 -> move_living("M",TO);
      tell_room(TO,"The harsh cry of a desert falcon attracts your attention "+
         "to it.\n");
   }
}
