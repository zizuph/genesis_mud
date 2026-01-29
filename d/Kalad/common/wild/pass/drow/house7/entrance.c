inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define GUARD "/d/Kalad/common/wild/pass/drow/npc/h7_war"
object ob1;
object ob2;
object ob3;
object ob4;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The entrance to the House Claddath compound");
   set_long("Before you is the compound of House Claddath, the seventh-ranked "+
      "house of Undraeth. The compound, which lies to the south, is a "+
      "massive congregation of stalagmites that have been magically "+
      "reshaped into an imposing fortress. Two especially tall stalagmites "+
      "tower above all the others, with the highest tower located near the "+
      "southern end of the compound, and with the shorter tower closer to your "+
      "position. Various intricate decorations, all wrought in magical faerie fire "+
      "line the compound in eerie reds, purples and greens.\n");
   add_item(({"entrance"}),
      "A large open area before the compound of House Claddath.\n");
   add_item(({"compound","house claddath","house","fortress","imposing fortress","mighty fortress"}),
      "A massive grouping of stalagmites combined and reshaped through magic "+
      "to form a fortress of incredible durability.\n");
   add_item(({"stalagmites","stalagmite"}),
      "They have been fused and reshaped into a mighty fortress of stone.\n");
   add_item(({"highest tower"}),
      "A tower near the far southern end of the compound that rises above "+
      "all the others.\n");
   add_item(({"shorter tower"}),
      "A tower second only in height to the highest tower in the south.\n");
   add_item(({"tower"}),
      "Which one?\n");
   add_item(({"intricate decorations","decorations","decoration","magical faerie fire","faerie fire","magical fire","fire"}),
      "Outstanding images of the Spider Queen, Lolth and all her various "+
      "followers, from the drow themselves to her grotesque yochlol.\n");
   add_exit(CPASS(drow/d15),"north");
   add_exit(CPASS(drow/house7/main_hall),"south","@@check",-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(GUARD);
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
   }
   if(!ob4)
      {
      ob4 = clone_object(GUARD);
      ob4 -> arm_me();
      ob4 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
      ob1 -> team_join(ob4);
      tell_room(TO,"A group of drow arrive at their post.\n");
   }
}
check()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Drow")
         {
         pres = 1;
       }
   }
   if(pres == 1)
      {
      write("You try to go south but are stopped by a drow!\n");
      say(QCTNAME(TP) + " tried to go south but was stopped by a drow!\n");
   }
   return pres;
}
