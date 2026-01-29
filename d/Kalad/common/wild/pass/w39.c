inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#define HARD_TO_CLIMB 30
#define DAMAGE 200
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("End of the Valley");
   set_long("You have reached the end of the valley, ahead of you is "+
      "nothing but the sheer side of the mountains. The valley walls here, "+
      "which were wider in the south are less spaced and have a higher "+
      "degree of ascent. The redwood trees, which tower above you, lie "+
      "mostly at the floor of the valley. There seems to be a narrow path "+
      "winding its way up the mountainside.\n");
   add_item(({"sheer side","side","mountainside"}),"The side of the "+
      "mountain opposite to you is even more steeply angled than the other "+
      "sides, however it still looks climbable.\n");
   add_item(({"valley walls","walls","wall"}),"The sides of the valley "+
      "are rather steep here, and would still be climbable if not for their "+
      "extreme ruggedness.\n");
   add_item(({"redwood trees","trees","tree"}),"The forest surrounds "+
      "you on all sides, shadowy undergrowth bristling with animal sounds.\n");
   add_exit("/d/Kalad/common/wild/pass/w38", "southwest",0,2);
   add_exit("/d/Kalad/common/wild/pass/underdark/u1", "up", "@@climb",3);
}
climb()
{
   if(TP->query_skill(SS_CLIMB) < random(HARD_TO_CLIMB))
      {
      write("You slip while climbing up the path and fall down.\n");
      write("You slam through the branches of a tree and then slam into the ground!\n");
      TP->heal_hp(-DAMAGE);
      say(QCTNAME(TP) + " slipped from the path, crashed through the branches of a tree and then slammed into the ground.\n");
      if(TP->query_hp() < 1)
         TP->do_die(TO);
      return 1;
   }
   write("You manage to climb up the path.\n");
   say(QCTNAME(TP) + " managed to climb up the path.\n");
   return 0;
}
