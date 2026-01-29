/* File farmer-end.c */
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define GG "/d/Kalad/common/caravan/npc/gateguard"
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;
object ob7;
object ob8;

void create_room()
{
	::create_room();
	set_short("On the intersection of End street and Farmer's Way");
    set_long("You are now at the intersection of End and Farmer's Way. "+
    "End street leads north and south from here, while Farmer's Way "+
    "goes off into the center of Kabal to the east. A large gate "+
    "known as Farmer's Gate is to your west, and it leads outside "+
    "of Kabal into the farm lands. The eternal, blazing Kaladian "+
    "sun beams down on you making you sweat a little.\n"+
    "There is a small gatehouse here.\n");
    hear_bell = 2;                   /*  2 = outdoor, 1 = indoor */
   add_item(({"large winch","winch"}),"A large metal rod used to open up the "+
      "Farmer's Gate.\n");
    add_exit(NOBLE(end/s1),"north",0,0,-1);
    add_exit(MARKET(end/s1),"south","@@block",0,0);
    add_exit(NOBLE(farmer/s10),"east",0,0,0);
    add_exit(NOBLE(gatehouse),"in",0,-1,-1); 
    clone_object(NOBLE(obj/fgdoor))->move(TO);
    add_item("gatehouse","A small gatehouse for guards to check "+
    "travellers as they pass in and out of Farmer's Gate.\n");
    set_alarm(2.0,0.0,"reset_room");
}

int block()
{
	write("The way is temporarily blocked.\n");
	return 1;
}

void
reset_room()
{
   if (!ob1)
      {
      ob1 = clone_object(CVAN(npc/in_cggk));
      ob1 -> move_living("M",TO);
   }
   if (!ob2)
      {
      ob2 = clone_object(CVAN(npc/cmilitia_cg));
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(GG);
      ob3 -> arm_me();
      ob3 -> move_living("M",TO);
   }
   if(!ob4)
      {
      ob4 = clone_object(GG);
      ob4 -> arm_me();
      ob4 -> move_living("M",TO);
   }
   if(!ob5)
      {
      ob5 = clone_object(GG);
      ob5 -> arm_me();
      ob5 -> move_living("M",TO);
   }
   if(!ob6)
      {
      ob6 = clone_object(GG);
      ob6 -> arm_me();
      ob6 -> move_living("M",TO);
   }
   if(!ob7)
      {
      ob7 = clone_object(GG);
      ob7 -> arm_me();
      ob7 -> move_living("M",TO);
   }
   if(!ob8)
      {
      ob8 = clone_object(GG);
      ob8 -> arm_me();
      ob8 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
      ob1 -> team_join(ob4);
      ob1 -> team_join(ob5);
      ob1 -> team_join(ob6);
      ob1 -> team_join(ob7);
      ob1 -> team_join(ob8);
      tell_room(TO,"A gatekeeper and a militiaman arrive at the Farmer's Gate, "+
         "accompanied by a troop of six elite guardsmen of Kabal.\n");
   }
}
