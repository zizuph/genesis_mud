inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Rolling grassland");
   set_long("A lush, rolling grassland dominates your field of vision, "+
      "appearing as if you were lost in a sea of grass. Tall grasses rise "+
      "all around you, reaching past waist height. A constant wind from "+
      "the east causes the grass to sway back and forth. The heat from the "+
      "Kaladian sun strikes you relentlessly, a poignant reminder of its "+
      "presence.\n");
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
   add_exit(CPASS(desert/grass/g27),"west");
   add_exit(CPASS(desert/grass/g21),"northwest");
   add_exit(CPASS(desert/grass/g22),"north");
   add_exit(CPASS(desert/grass/g23),"northeast");
   add_exit(CPASS(desert/grass/g29),"east");
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/bed_loner));
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A desert nomad appears from amidst the sea of grass.\n");
   }
}
