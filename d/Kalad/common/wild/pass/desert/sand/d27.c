inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define DIFFICULTY 40
#define DAMAGE 250
string long;
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the endless sand dunes");
   set_long("All around you, in great sloping mounds are "+
      "the huge glittering ridges of the sand dunes. "+
      "The loose sand that fills your parched throat makes travel through "+
      "this harsh clime extremely difficult, for "+
      "it seems as if you sink lower and lower with each step, and even "+
      "the smallest of sand dunes is a hindrance to travel. "+
      "The nearest dunes lie immediately to the west and southeast, while "+
      "ways through the dunes lead to the north and southwest. "+
      "The scorching rays of the Kaladian sun hammer down on the dunes "+
      "all about you, so intense is the heat that ripples of air are "+
      "clearly visible.\n");
   add_item(({"great sloping mounds","great mounds","sloping mounds","mounds","mound","huge glittering ridges","huge ridges","glittering ridges","ridges","sand dunes","sand dune","dunes","dune"}),
      "Formed from the continual action of the harsh desert winds, the great "+
      "collections of sands are ever-shifting in the landscape, threatening "+
      "anything of permanence with ignoble burial. The sand dune to the "+
      "east doesn't seem as steep as the rest and might be climbable.\n");
   add_item(({"loose sand","sand"}),"The tiny, fine granules slip through "+
      "your grasp.\n");
   add_item(({"kaladian sun","sun"}),"The harshly brilliant orb hangs "+
      "in the sky, scorching the land beneath it with its rays of light.\n");
   add_item(({"ways","way"}),"Passages through the dunes that allow "+
      "travel among them.\n");
   add_cmd_item(({"up","dune"}),"climb","@@climb");
   add_cmd_item("dune","climb","@@climb");
   add_exit(CPASS(desert/sand/d22),"north",0,3);
   add_exit(CPASS(desert/sand/d30),"southwest",0,3);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(npc/sandling));
      ob1 -> move_living("M",TO);
      tell_room(TO,"The sand before you shifts slightly, a figure suddenly "+
         "forming before your eyes.\n");
   }
}
climb()
{
   if(TP->query_skill(SS_CLIMB) < random(DIFFICULTY))
      {
      write("You try to climb up the dune but fail miserably.\n");
      write("You slip and slide down the dune, hurting yourself in the "+
         "process.\n");
      say(QCTNAME(TP) + " tried to climb up a dune but slipped and got hurt.\n");
      TP->heal_hp(-DAMAGE);
      if(TP->query_hp() <= 0)
         TP->do_die(TO);
      return 1;
   }
   write("You climb up the dune.\n");
   set_dircmd("dune");
   TP->move_living("up the side of the dune","/d/Kalad/common/wild/pass/desert/sand/on_dune");
   return "You've managed to reach the top of the dune.\n";
}
