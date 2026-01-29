inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos, modified from Ashbless's bath house */
   create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("A small pool at the oasis");
   set_long("Cooling palm trees and the melodic sounds of birds resound "+
      "from the surroundings. Almost unnoticed at the very heart of this "+
      "oasis is a large clear pond. Many animals are in and around it, "+
      "bathing and drinking.\n");
   add_item(({"cooling palm trees","cooling trees","palm trees","trees","tree"}),
      "Tall, graceful trees that help to block out the fierece rays of the "+
      "Kaladian sun.\n");
   add_item(({"kaladian sun","sun"}),"You are nearly blinded by its "+
      "awesome brilliance!\n");
   add_item(({"large clear pond","large pond","clear pond","pond"}),"A large "+
      "body of water that sparkles and glistens in the sunlight.\n");
   add_item(({"water"}),"It is as clear as pure glass.\n");
   add_item(({"ground"}),"It isn't visible due to the thick underbrush.\n");
   add_item(({"underbrush","brush"}),"A profileration of plants grows "+
      "on the ground, obscuring it from your view.\n");
   add_cmd_item("water","drink",VBFC_ME("do_drink"));
   add_item(({"animals","animal"}),"@@animals");
   add_prop(OBJ_I_CONTAIN_WATER,1);
   add_prop(ROOM_I_TYPE,ROOM_BEACH);
   add_exit(CPASS(desert/oasis/o3),"west");
   add_exit(CPASS(desert/oasis/o2),"north");
   add_exit(CPASS(desert/oasis/o5),"east");
   add_exit(CPASS(desert/oasis/o4),"south");
   set_alarm(3.0,0.0,"msg1");
}

do_drink()
{
   int soaked;
   soaked = TP->query_soaked();
   TP->set_soaked(soaked + 100);
   return "You refresh yourself from the clear water.\n";
}

msg1()
{
   tell_room(TO,"One of the animals steps into the water.\n");
   set_alarm(3.0,0.0,"msg2");
   return 1;
}
msg2()
{
   tell_room(TO,"The animal bathes in the water.\n");
   set_alarm(3.0,0.0,"msg3");
   return 1;
}
msg3()
{
   tell_room(TO,"The animal climbs out of the water and shivers.\n");
   return 1;
}

s_block()
{
   if(TP->query_prop(IN_WATER))
      {
      write("You have to exit the water first.\n");
      return 1;
   }
   else
      return 0;
}

init()
{
   ::init();
   AA(bathe,bathe);
   AA(bathe,scrub);
   AA(bathe,clean);
   AA(bathe,wash);
   AA(swim,swim);
   AA(sing,sing);
   AA(go_water,enter);
   AA(go_water,go);
   AA(out_water,exit);
   AA(out_water,climb);
}

go_water(str)
{
   NF(C(query_verb()) + " what?\n");
   if (str != "water" && str != "basin" && str != "bath")
      return 0;
   
   if( TP->query_prop(IN_WATER) )
      write("You're already in the water.\n");
   else
      {
      TP->add_prop(IN_WATER,1);
      write(
         "You step into the pond and the warm water "+
         "reaches your waist.\n");
      say(QCTNAME(TP) + " steps into the water.\n");
   }
   
   return 1;
}

out_water(str)
{
   if (query_verb() == "climb")
      {
      NF("Climb what?\n");
      if(str!="out of water"&&str!="out of pond"&&str!="out of large pond")
         return 0;
   }
   else
      {
      NF("Exit what?\n");
      if(str != "water" && str != "pond" && str != "large pond")
         return 0;
   }
   
   if (TP->query_prop(IN_WATER) != 1)
      write("You aren't in the water.\n");
   else
      {
      TP->remove_prop(IN_WATER);
      write("You climb out of the warm water and shiver as a slight "+
         "breeze touches your skin.\n");
      say(QCTNAME(TP) + " climbs out of the water and shivers.\n");
   }
   
   return 1;
}

swim(str)
{
   if (str)
      return 0;
   
   if (!TP->query_prop(IN_WATER))
      {
      write("You can't swim unless you're in the water.\n");
      return 1;
   }
   
   write("You splash around in the water as if you were a child again.\n"+
      "Gosh, don't you feel silly?\n");
   say(QCTNAME(TP) + " splashes around in the water as if " + TP->query_pronoun() + " were a child again. Boy does " + TP->query_pronoun() + " look silly.\n");
   return 1;
}

sing(str)
{
   if (!str)
      str = "RUBBER DUCKY, YOU'RE THE ONE..."+
   "YOU MAKE BATHING, SO MUCH FUN...";
   
   write("You start singing: '" + str + "...'" +
      "but soon notice that your singing has caused the animals around "+
      "the pond to hide in fear from you. You stop singing.\n");
   say(QCTNAME(TP) + " starts singing: '" + str + "...'" +
      "but soon notices that " + TP->query_possessive() + " singing "+
      "has caused the animals around the pond to hide in fear "+
      "from the terrible sound. " + QCTNAME(TP) + " stops singing.\n");
   
   return 1;
}

bathe(str)
{
   object *ob;
   int i;
   
   if(str)
      if( str != "me" && str != "self" && str != "myself")
      return 0;
   
   if(!TP->query_prop(IN_WATER))
      {
      write("You can't bathe until you enter the water.\n");
      return 1;
   }
   
   if (TP->query_prop(LIVE_I_DIRTY) == 0)
      write("You bathe yourself in the relaxing warm water, though "+
      "you were already clean.\n");
   else
      write("You scrub yourself thoroughly and layers of filth come off "+
      "in the water and sink to the bottom.\n"+
      "You're now squeaky clean!\n");
   
   say(QCTNAME(TP) +
      " bathes in the water. You realize it was about time.\n");
   
   TP->add_prop(LIVE_I_DIRTY,0);
   
   ob = deep_inventory(TP);
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->id("dirty"))
      ob[i]->remove_object();
   
   return 1;
}

animals()
{
   string str;
   
   str = (
      "A variety of wildlife is gathered around the life-giving water "+
      "of the pond. Among them are gazelle, antelope and even some "+
      "large lizards. However, as soon as they notice your close "+
      "attention, they dart away into the underbrush.\n");
   
   say(QCTNAME(TP) + " starts to intensely scrutinize several of the "+
      "animals around the pond. The animals soon notice however, and "+
      "abruptly disappear into the brush.\n");
   
   return str;
}
