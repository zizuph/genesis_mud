inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#define HARD_TO_CLIMB 50
#define DAMAGE 150
string long;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Outcropping");
   set_long("You are on an outcropping of the moutainside.\n"+
      "This narrow ledge is barely large enough to hold you, gazing down "+
      "you can see the tops of the redwood trees lying dozens of feet below "+
      "you. Above is yet more of the mountainside.\n");
   add_item(({"narrow ledge","ledge"}),"A small flat area on the side of "+
      "this mountain.\n");
   add_item(({"tops","redwood trees","redwood tree","trees","tree"}),
      "Even from this great height, they look quite impressive. The forest "+
      "stretches out of sight to the southwest.\n");
   add_item(({"mountainside","side"}),"The sheer side of the mountain "+
      "you are trying to climb, it doesn't look any easier on the way up. "+
      "However, going down looks like it might be far easier.\n");
  add_exit("/d/Kalad/common/wild/pass/w39", "down",0,2);
   add_exit("/d/Kalad/common/wild/pass/underdark/u2", "up", "@@climb",3);
}
void
init()
{
   ::init();
   write("A gust of mountain wind blows against you.\n");
   say("A gust of mountain wind blows against " + QTNAME(TP) + ".\n");
}
climb()
{
   if(TP->query_skill(SS_CLIMB) < random(HARD_TO_CLIMB))
      {
      write("You slip while trying to scale the mountainside and fall down.\n");
      write("You slam into the outcropping!\n");
      TP->heal_hp(-DAMAGE);
      say(QCTNAME(TP) + " slipped while trying to scale the mountainside and slammed into the outcropping.\n");
      return 1;
      if (TP->query_hp() < 1)
         TP->do_die(TO);
   }
   write("You manage to scale the mountainside.\n");
   say(QCTNAME(TP) + " manages to scale the mountainside.\n");
   return 0;
}
