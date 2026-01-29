inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define CAN_START_NOQUAR "_can_start_noquar"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("A chapel to Lolth");
   set_long("A chapel devoted to Lolth.\n"+
      "This circular chamber is rimmed by dozens of adamantine pillars, "+
      "completely encircling its circumference, save for the northern section, "+
      "where a dark archway lies. The center of this chamber is occupied "+
      "by a circle of obsidian braziers, which in turn encircle one grand "+
      "brazier that is presently glowing with a foreboding red light. "+
      "A patch of darkness lies in the east, while a black archway leads to "+
      "the west.\n");
   add_item(({"chapel","circular chamber","chamber"}),
      "A place of dark homage devoted to the Spider-Queen of the drow, Lolth.\n");
   add_item(({"adamantine pillars","adamantine pillar","pillars","pillar"}),
      "The structures encircle the perimeter of this chamber, acting as "+
      "though they were guardians of this place of worship.\n");
   add_item(({"dark archway","archway"}),
      "A lightless doorway that lies to the north, and appears to lead out "+
      "of this chamber.\n");
   add_item(({"center"}),
      "It is occupied by many braziers.\n");
   add_item(({"circle of obsidian braziers","circle","obsidian braziers"}),
      "They form a wide ring at the center of this room and are slowly "+
      "pouring forth an overly sweet aroma into the air.\n");
   add_item(({"one grand brazier","grand brazier"}),
      "A large brazier, well over five and a half feet in height, that is "+
      "presently casting a dark red light across the room.\n");
   add_item(({"braziers","brazier"}),
      "Which brazier?\n");
   add_item(({"dark red light","dark light","red light","foreboding red light","foreboding light","light"}),
      "It fills the entirety of this room.\n");
   add_item(({"patch","darkness"}),
      "The absence of light...\n");
   add_item(({"black archway","archway"}),
      "It appears to lead west, into another chamber.\n");
   add_exit(CPASS(drow/house8/main_hall),"north",0,-1,-1);
   add_exit(CPASS(drow/house8/sac_chamber),"east","@@msg",-1,-1);
   add_exit(CPASS(drow/house8/start),"west","@@check",-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h8_priest));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A figure appears as if from nowhere.\n");
   }
}
msg()
{
   write("You step into the patch of darkness.\n");
   say(QCTNAME(TP) + " steps into the patch of darkness.\n");
   return 0;
}
check()
{
   object *ob;
   int i;
   ob = deep_inventory(TP);
   for(i = 0; i < sizeof(ob); i++)
   if(ob[i]->id("_h8_insignia"))
      {
      write("You step into the black archway...\n");
      say(QCTNAME(TP) + " steps into the black archway...\n");
      TP->add_prop(CAN_START_NOQUAR,1);
      return 0;
   }
   write("You step into the black archway...and cannot pass!\n");
   say(QCTNAME(TP) + " steps into the black archway...and cannot pass!\n");
   return 1;
}
