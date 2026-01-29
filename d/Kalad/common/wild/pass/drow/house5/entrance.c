inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define GUARD "/d/Kalad/common/wild/pass/drow/npc/h5_war"
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The entrance to House Kilsek");
   set_long("The large stalagmite compound known collectively as House Kilsek "+
      "rises threateningly over you in the east, its numerous gracefully rising "+
      "stalagmite towers appearing like nothing more than blackened fingers "+
      "clawing their way out of a shallow grave. Compared to the rest of the "+
      "city, this place is practically ablaze with lights, as numerous decorations "+
      "of faerie fire cause the compound to glow in a rainbow of reds, purples, "+
      "greens and blues. A dark archway lies to the east, apparently leading "+
      "into the compound. In the south lies a smaller, much less imposing "+
      "structure.\n");
   add_item(({"large stalagmite compound","house kilsek","house","large compound","stalagmite compound","compound"}),
      "A fiercely glowing mass of stalagmites that serves as both home and "+
      "fortress for the drow of House Kilsek.\n");
   add_item(({"stalagmite towers","towers","stalagmite tower","tower"}),
      "Several black stone towers that rise above the compound.\n");
   add_item(({"decorations","decoration","faerie fire","fire"}),
      "Magically glowing decorations that depict numerous scenes, most of which "+
      "depict spiders in one form or another.\n");
   add_item(({"dark archway","archway"}),
      "A recess filled with darkness, despite the numerous lights from the "+
      "faerie fire surrounding it.\n");
   add_item(({"structure"}),
      "Nothing more than a low, though relatively large mound to the south.\n");
   add_exit(CPASS(drow/d10),"west");
   add_exit(CPASS(drow/house5/main_hall),"east","@@guard_block",-1,-1);
   add_exit(CPASS(drow/house5/s_quarters),"south","@@guard_prevent",-1,1);
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
   }
   if(!ob5)
      {
      ob5 = clone_object(GUARD);
      ob5 -> arm_me();
      ob5 -> move_living("M",TO);
   }
   if(!ob6)
      {
      ob6 = clone_object(GUARD);
      ob6 -> arm_me();
      ob6 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
      ob1 -> team_join(ob4);
      ob1 -> team_join(ob5);
      ob1 -> team_join(ob6);
      tell_room(TO,"Several drow arrive before the compound.\n");
      return 1;
   }
}
guard_block()
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
      write("A drow prevents you from going east!\n");
      say(QCTNAME(TP) + " tries to go east but is prevented by a drow!\n");
   }
   if(pres != 1)
      {
      write("You pass into the House Kilsek compound unchallenged.\n");
      say(QCTNAME(TP) + " passes into the House Kilsek compound unchallenged.\n");
   }
   return pres;
}
