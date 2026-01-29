inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("The chamber of the Matron Mother of House Noquar.\n");
   set_long("A multi-faceted room lies before you, resembling nothing so "+
      "much as the interior of a multi-faceted eye. The walls, and ceiling, "+
      "which converge to form a dome-like structure have been enchanted "+
      "with blood-red faerie fire, casting the chamber into eerie shades "+
      "of red. Only two features disturb the continuity of the strange "+
      "multi-faceted walls. To the west and north lie pools of darkness, "+
      "darkness so intense that not a glimmer of light from the faerie fire "+
      "even begins to penetrate it. Lying in various areas about the chamber "+
      "are a large spider sculpture, a platinum brazier and a small shrine.\n"+
      "In the east stands a black archway.\n");
   add_item(({"chamber","multi-faceted room"}),
      "An unusually designed room of the House Noquar compound, its like "+
      "nothing you've ever seen before, so unique is its architectural "+
      "design.\n");
   add_item(({"walls","wall","ceiling","multi-faceted walls","multi-faceted wall"}),
      "The walls and ceiling of this chamber form a dome, composed of many "+
      "facets, somewhat like the interior of a compound eye. The effect is "+
      "one that proves quite disturbing, for everywhere one looks, one's "+
      "face is reflected in a distorted parody of itself.\n");
   add_item(({"blood-red faerie fire","faerie fire"}),
      "It completely covers the walls and ceiling, lending its eerie light to "+
      "this already unusual chamber.\n");
   add_item(({"pools of darkness","pools","pool","darkness"}),
      "They look to be exits from this room.\n");
   add_item(({"large spider sculpture","large sculpture","spider sculpture","sculpture"}),
      "Strangely enough, it is not a sculpture, but a bed.\n");
   add_item(({"platinum brazier","brazier"}),
      "Faint wisps of incense can be seen rising from it.\n");
   add_item(({"wisps","wisp","incense"}),
      "Thin vapors of grey smoke.\n");
   add_item(({"small shrine","shrine"}),
      "A small shrine devoted to Lolth, the Spider-Queen. Upon its grey surface "+
      "is a sinisterly dark stain.\n");
   add_item(({"dark stain","stain"}),
      "It appears to be blood, from what being you cannot tell.\n");
   add_item(({"black archway","archway"}),
      "It appears to lead from this chamber and into another one, though it is "+
      "difficult to tell considering it is completely lightless.\n");
   add_exit(CPASS(drow/house8/main_hall),"west",0,-1,-1);
   add_exit(CPASS(drow/house8/tr_chamber),"north",0,-1,-1);
   add_exit(CPASS(drow/house8/joinroom),"east","@@check",-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h8_matron));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(CPASS(drow/npc/h8_patron));
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      tell_room(TO,"Two figures emerge from the pools of darkness.\n");
   }
}
check()
{
   object *ob;
   int i;
   ob = deep_inventory(TP);
   for(i = 0; i < sizeof(ob); i++)
   if(ob[i]->id("_sniff_the_sniffer"))
      {
      write("You step into the black archway...\n");
      say(QCTNAME(TP) + " steps into the black archway...\n");
      return 0;
   }
   write("You step into the black archway...and cannot pass!\n");
   say(QCTNAME(TP) + " steps into the black archway...and cannot pass!\n");
   return 1;
}
