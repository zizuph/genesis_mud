inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#define HAVE_DRUNK_POISON "_have_drunk_poison"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Rolling grassland");
   set_long("Spreading out before you is a lush, rolling grassland "+
      "right here within the heart of the Great Kalad Waste. Tall grasses "+
      "fill your field of view, giving the impression of a sea of grass. "+
      "A wind blows constantly from the east, causing the grass to whip back and "+
      "forth. A clear pool of water is here, its edges thick with the "+
      "growth of palm trees.\n");
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
   add_item(({"clear pool","pool"}),"A pool of water around fifteen "+
      "feet across at its widest point and nearly four feet in depth.\n");
   add_item(({"water"}),"Its as clear as glass.\n");
   add_item(({"palm trees","palm tree","trees","tree"}),"They grow "+
      "thickly along the edge of the pool, their large leaves providing "+
      "shade from the endless heat of the Kaladian sun.\n");
   add_exit(CPASS(desert/grass/g22),"west");
   add_exit(CPASS(desert/grass/g15),"northwest");
   add_exit(CPASS(desert/grass/g16),"north");
   add_exit(CPASS(desert/grass/g17),"northeast");
   add_exit(CPASS(desert/grass/g24),"east");
   add_exit(CPASS(desert/grass/g30),"southeast");
   add_exit(CPASS(desert/grass/g29),"south");
   add_exit(CPASS(desert/grass/g28),"southwest");
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
   write("You take a sip of the water.\n");
   say(QCTNAME(TP) + " takes a sip of the water.\n");
   set_alarm(3.0,0.0,"poison");
   return 1;
}
void
poison()
{
   object poison;
   poison = clone_object("/std/poison_effect");
   if(poison)
      {
      poison->move(TP);
      poison->set_time(500);
      poison->set_interval(50);
      poison->set_strength(500);
      poison->set_damage(({POISON_HP, 500, POISON_STAT, SS_CON}));
      poison->start_poison();
      TP->add_prop(HAVE_DRUNK_POISON,1);
   }
   return 0;
}
