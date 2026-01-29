inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SW "/d/Kalad/common/wild/pass/npc/rt_skelwar"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_I_LIGHT,0);
   INSIDE;
   set_short("Within the ruined tower");
   set_long("Ruined stone tables, broken glass and shattered cabinets lies "+
      "scattered around the room, the broken fragmented remnants of a "+
      "laboratory. The air here smells of decay, probably from the many "+
      "skeletons that lie amidst the ruins of this level of the tower. "+
      "Large piles of dust and sand cover nearly everything, giving you the "+
      "false impression that you are amidst great sand dunes. A partially "+
      "ruined staircase leads both up and down from here.\n");
   add_item(({"ruined stone tables","ruined tables","stone tables","tables","table"}),
      "The great slabs of stone have been knocked off their supports and bear "+
      "marks of having been exposed to intense heat.\n");
   add_item(({"broken glass","glass"}),"It lies in jagged pieces all "+
      "over the room.\n");
   add_item(({"shattered cabinets","cabinets","cabinet"}),
      "The fire-blackened remains of the wooden cabinets are scattered around "+
      "the room, as if from an explosion.\n");
   add_item(({"skeletons","skeleton"}),
      "The long dead remains of human beings. They lie on the ground in "+
      "poses indicative of horrible pain and agony.\n");
   add_item(({"large piles","piles","pile","dust","sand"}),
      "It covers everything in the room, and is even beginning to cling onto you.\n");
   add_item(({"ruined staircase","staircase"}),
      "A set of stairs that has crumbled in some places but is still "+
      "serviceable, though barely.\n");
   add_exit(CPASS(desert/sand/r5),"up",0,-1);
   add_exit(CPASS(desert/sand/r3),"down","@@check",-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(SW);
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(SW);
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(SW);
      ob3 -> arm_me();
      ob3 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
      tell_room(TO,"Several skeletons on the ground rise before your eyes.\n");
   }
}
check()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for (i = 0; i < sizeof(ob); i++)
   {
      if (ob[i]->query_name() == "Warrior")
         {
         pres = 1;
        }
   }
   if (pres == 1)
      {
      write("You try to go down but are stopped by the skeletal warrior!\n");
      say(QCTNAME(TP) + " tries to go down but is stopped by the skeletal warrior!\n");
   }
   return pres;
}
