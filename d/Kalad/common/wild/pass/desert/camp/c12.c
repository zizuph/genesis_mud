inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("Inside a small tent");
   set_long("This tent's interior is rather plain, showing the "+
      "inhabitants' lack of material wealth. Only two small sleeping mats, "+
      "some lamps and a rug cover the floor. There is also a large iron pot "+
      "in the center of the tent. Along the floor is a mass of thorns and spikes.\n");
   add_item(({"tent"}),"Its what you're standing in, just look around.\n");
   add_item(({"small sleeping mats","small mats","sleeping mats","mats","mat"}),
      "Made out of soft camel hair, it helps keep Bedellin nomads warm in the "+
      "dead of night, as well as help keep them safe from desert creatures.\n");
   add_item(({"lamps","lamp"}),"A small brass lantern that provides some "+
      "light as well as warmth.\n");
   add_item(({"rug"}),"A coarse woolen rug, used to keep the tent free of "+
      "sand and other debris.\n");
   add_item(({"large iron pot","large pot","iron pot","pot"}),"A large "+
      "cauldron used for cooking and heating. It looks slightly cracked.\n");
   add_item(({"crack"}),"A small crack in the pot's side.\n");
   add_item(({"floor"}),"Its just sandy ground.\n");
   add_item(({"mass of thorns and spikes","thorns","spikes","thorn","spike"}),
      "A barrier used by the nomadic Bedellin to keep the desert creatures "+
      "from entering their tents.\n");
   add_exit(CPASS(desert/camp/c13),"east",0,-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/bed_qeld));
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A Bedellin elder enters the tent.\n");
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/bed_wom));
      ob2 -> move_living("M",TO);
      tell_room(TO,"A Bedellin woman enters the tent.\n");
      ob1 -> team_join(ob2);
   }
}
