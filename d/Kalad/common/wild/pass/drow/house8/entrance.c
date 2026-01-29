inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define GUARD "/d/Kalad/common/wild/pass/drow/npc/h8_war"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The entrance to the House Noquar compound");
   set_long("You are at the entrance to the grand compound of House "+
      "Noquar, the Eighth-ranked house of the city of Undraeth. Although "+
      "not as grand as the higher-ranked houses, it is nevertheless "+
      "impressive in its own right. The lurid glow of dozens of faerie fire "+
      "decorations enfolds the entirety of the compound, causing it to "+
      "veritably blaze with multi-colored light. An arched entranceway lies "+
      "just to the east, where it is strangely blanketed with darkness. To "+
      "the northeast is a seperate compound, smaller and less worked than "+
      "the one to the east.\n");
   add_item(({"compound"}),
      "Which compound?\n");
   add_item(({"entrance"}),
      "A clearing located midway between the streets of Undraeth in the west, "+
      "and the main compound in the east.\n");
   add_item(({"grand compound","house noquar","eigth-ranked house","house noquar compound","main compound"}),
      "A collection of massive stalagmites that have been magically "+
      "bound to one another to form a structure similar to surface world "+
      "manors and private estates.\n");
   add_item(({"lurid glow","glow","faerie fire decorations","decorations","decoration","faerie fire","fire"}),
      "Varying colors of the spectrum have all been used to create a sight that "+
      "veritably exudes gaudiness and chaos.\n");
   add_item(({"arched entranceway","entranceway"}),
      "The only dark area of the main compound, it appears to lead into it.\n");
   add_item(({"seperate compound"}),
      "A small structure, compared to the main compound, it appears as "+
      "nothing more than a low pile of half-ruined stalagmites.\n");
   add_item(({"streets","street"}),
      "It is too difficult to make out any details from here.\n");
   add_exit(CPASS(drow/d47),"west","@@msg");
   add_exit(CPASS(drow/house8/s_chamber),"northeast","@@msg1",-1,-1);
   add_exit(CPASS(drow/house8/main_hall),"east","@@check",-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
msg()
{
   write("You head away from the main compound and towards the streets.\n");
   say(QCTNAME(TP) + " heads away from the main compound and towards the streets.\n");
   return 0;
}
msg1()
{
   write("You head for the compound in the northeast.\n");
   say(QCTNAME(TP) + " heads for the seperate compound.\n");
   return 0;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h8_e_war));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(GUARD);
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(GUARD);
      ob3 -> arm_me();
      ob3 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
      tell_room(TO,"Several drow emerge from the compound.\n");
   }
}
check()
{
   if((present(ob1,TO) || present(ob2,TO) || present(ob3,TO)) &&
         TP->query_subloc_obj("_h8_insignia") == 0)
   {
      write("You are stopped by a drow!\n");
      say(QCTNAME(TP) + " tries to go east but is stopped by a drow!\n");
      return 1;
   }
   else
      {
      write("You pass into the compound of House Noquar.\n");
      say(QCTNAME(TP) + " passes through the east archway.\n");
      return 0;
   }
}
