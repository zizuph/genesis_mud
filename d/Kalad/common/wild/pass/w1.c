/* 
 * /d/Kalad/common/wild/pass/w1.c
 * Purpose    : Valley setting
 * Located    : Hespyre Mountains off of Caravan Route
 * Created By : Antharanos  
 * Modified By: 
 */ 

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
object ob9;
object door;
string long;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Outside the Caravan Gate");
   set_long("You now stand just outside the Caravan Gate of the great city "+
      "of Kabal. The road here is paved in worn grey cobbles and heads "+
      "south towards the Caravan Gate entrance, one of three large gates "+
      "that leads into Kabal. The rest of the roadway, known more commonly as the "+
      "Caravan Route, heads northeast from here, winding its way through "+
      "the foothills immediately surrounding the city. Further in the "+
      "distance you can see the majestic Hespyre mountains, towering above "+
      "the surrounding landscape.\n");
   add_item(({"caravan gate","gate","entrance"}),"A pair of massive "+
      "steel gates that lies between the huge city walls of Kabal, which "+
      "encircle and protect the city from external threats.\n");
   add_item(({"huge city walls","city walls","huge walls","walls","wall"}),
      "A massive wall rising to a height of thirty feet and appears to be "+
      "at least several feet in thickness, truly a great obstacle to any "+
      "invading forces.\n");
   add_item(({"road","roadway","caravan route","route"}),"The cobblestoned "+
      "road leads south into Kabal and northeast through the foothills and "+
      "into the towering heights of the Hespyre mountains.\n");
   add_item(({"foothills","foothill"}),"A small series of gently rolling "+
      "hills covered only with scattered vegetation that eventually rises "+
      "in height to form the Hespyre mountains.\n");
   add_item(({"vegetation"}),"A few hardy grasses can be seen.\n");
   add_item(({"hespyre mountains","mountains","mountain"}),"A "+
      "magnificent range of mountains that runs far to the north and south, "+
      "a giant physical barrier that seperates Kabal from the rest of "+
      "Kalad. The majority of the mountain range lies far to the northeast, "+
      "the direction in which the Caravan Route heads.\n");
   add_item(({"large winch","winch"}),"A large metal rod used to open up "+
      "the Caravan Gate.\n");
   add_exit("/d/Kalad/common/wild/pass/w2", "northeast",0,2);
   door = clone_object("/d/Kalad/common/caravan/door/cgdoor1");
   door -> move(TO);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if (!ob1)
      {
      ob1 = clone_object(CVAN(npc/out_cggk));
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CVAN(npc/kgpcom));
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(CVAN(npc/kguard));
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
   }
   if(!ob9)
      {
      ob9 = clone_object(GG);
      ob9 -> arm_me();
      ob9 -> move_living("M",TO);
      ob1 -> team_join(ob4);
      ob1 -> team_join(ob5);
      ob1 -> team_join(ob6);
      ob1 -> team_join(ob7);
      ob1 -> team_join(ob8);
      ob1 -> team_join(ob9);
      ob2 -> team_join(ob3);
      tell_room(TO,"A gatekeeper, the patrol commander and a guardsman of "+
         "Kabal arrives at the Caravan Gate, accompanied by a troop of six "+
         "elite guardsmen of Kabal.\n");
   }
}
void
init()
{
   ::init();
   AA(crank,crank);
   AA(climb,climb);
   write("A fresh breeze blows past you.\n");
}
int
crank(string str)
{
   if(!str || str != "winch")
      {
      notify_fail("What did you want to crank?\n");
      return 0;
   }
   write("You try in vain to crank the winch but can't quite figure out how to operate the mechanism.\n");
   say(QCTNAME(TP) + " tries in vain to crank the winch but can't quite figure "+
      "out the mechanism.\n");
   return 1;
}

int
climb(string what)
{
   NF("Climb what?\n");
   what = lower_case(what);
   if (!what || (what != "door" && what != "gate" && what != "steel doors" &&
      what != "doors" && what != "gates" && what != "steel door" &&
       what != "caravan gate" && what != "caravan gates"))
      return 0;
   NF("But the doors are open! It would look kind of stupid to climb it now.\n");
   if (door->query_open())
      return 0;
   write("You climb over the gate with some difficulties.\n");
   TP->move_living("climbing over the gate.","/d/Kalad/common/caravan/caravan_gate",1,0);
   return 1;
}
