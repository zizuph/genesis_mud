inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("Inside a small tent");
   set_long("The interior of this tent is quite plain, indicating the "+
      "occupants' lack of material wealth. Only three small sleeping mats, "+
      "a pair of lamps and a rug cover the floor. There is also a large "+
      "iron pot in the center of the tent. The sides of the tent "+
      "are decorated with hooks, which hang from the tent poles. The outskirts "+
      "of the tent floor are covered with thorny spikes.\n");
   add_item(({"tent"}),"It is what you are inside of.\n");
   add_item(({"sleeping mats","mats","mat"}),"Made of woven camel fibers and "+
      "complete with blankets and cushions, the setup looks quite comfortable.\n");
   add_item(({"blankets","blanket"}),"A warm wool blanket, perfect for "+
      "the cold desert night.\n");
   add_item(({"cushions","cushion"}),"Rather fluffly pillows filled with "+
      "soft camel hairs.\n");
   add_item(({"lamps","lamp"}),"Simple iron lamps used to illuminate "+
      "illuminate the tent's interior.\n");
   add_item(({"rug"}),"A carpet woven from some rough, stringy material.\n");
   add_item(({"tent floor","floor"}),"It is nothing but hot, dry sand.\n");
   add_item(({"large iron pot","iron pot","pot"}),"A three foot diameter "+
      "pot placed in the tent's center and used for cooking food.\n");
   add_item(({"sides"}),"The tent's interior is unaddorned except for several "+
      "hooks placed on the tent poles.\n");
   add_item(({"hooks","hook"}),"A place from which weapons are hung.\n");
   add_item(({"tent poles","poles","pole"}),"The sturdy wooden poles "+
      "hole up the tent.\n");
   add_item(({"thorny spikes","spikes","spike"}),"Sharpened bones along "+
      "with sharp thorns that are used to keep scorpions and other desert "+
      "creatures from entering the tent.\n");
   add_exit(CPASS(desert/camp/c14),"west",0,-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/bed_healer));
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
      tell_room(TO,"The Bedellin healer strides into the tent.\n");
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(npc/bed_wom));
      ob2 -> my_stuff();
      ob2 -> move_living("M",TO);
      tell_room(TO,"A Bedellin woman enters the tent.\n");
   }
   if(!ob3)
      {
      ob3 = clone_object(CPASS(npc/bed_child));
      ob3 -> move_living("M",TO);
      tell_room(TO,"A Bedellin child skips into the tent.\n");
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
   }
}
