inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define GUARD "/d/Kalad/common/wild/pass/drow/npc/h5_e_war"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The main hall of House Kilsek");
   set_long("This grand, circular hall is the main area of the House "+
      "Kilsek compound, for all other vital areas of the compound connect "+
      "to this great chamber. Intricate decorations of faerie fire decorate "+
      "the entire chamber, covering the floor, walls and ceiling. At the "+
      "center of the room is a column of blood red light, one that "+
      "disappears into the ceiling above. Decorated archways lie to the west, "+
      "north, east and south.\n");
   add_item(({"main hall","hall","grand hall","circular hall","main area","area","compound","great chamber","chamber"}),
      "It is the centrally located section of this drow compound, have a look "+
      "around.\n");
   add_item(({"intricate decorations","decorations","decoration","faerie fire","fire"}),
      "Glowing magical descriptions of drow and spiders showing fealty to "+
      "Lolth the Spider Queen.\n");
   add_item(({"floor","walls","wall","ceiling"}),
      "It is made of a strange black stone that is covered with faerie fire "+
      "decorations.\n");
   add_item(({"column","blood red light","red light","light"}),
      "A radiant beam of red light that seems to connect the floor and ceiling.\n");
   add_item(({"decorated archways","archways","decorated archway","archway"}),
      "Sculptured black stone archways that lead to other sections of the "+
      "compound.\n");
   add_exit(CPASS(drow/house5/entrance),"west",0,-1,-1);
   add_exit(CPASS(drow/house5/p_quarters),"north",0,-1,-1);
   add_exit(CPASS(drow/house5/temple),"east",0,-1,-1);
   add_exit(CPASS(drow/house5/w_quarters),"south",0,-1,-1);
   add_exit(CPASS(drow/house5/mm_chamber),"up","@@guard_block",-1,-1);
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
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
      tell_room(TO,"Several drow emerge from concealment.\n");
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
      write("A drow prevents you from stepping into the blood red light!\n");
      say(QCTNAME(TP) + " tries to go up but is prevented by a drow!\n");
   }
   if(pres != 1)
      {
      write("You step into the blood red light and are transported up.\n");
      say(QCTNAME(TP) + " steps into the blood red light and is transported up.\n");
   }
   return pres;
}
