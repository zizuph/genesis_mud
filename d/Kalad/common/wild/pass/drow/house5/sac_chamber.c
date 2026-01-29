inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SAC "/d/Kalad/common/wild/pass/drow/npc/h5_sacrifice"
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
   set_short("A sacrificial chamber");
   set_long("This dark, somewhat damp chamber is quite a contrast to the "+
      "extremely fine condition of the rest of the House Kilsek compound. "+
      "Unlike the rest of the aforementioned compound, this place has been "+
      "roughly hewn from dark stone and does little to preserve the quality "+
      "of the air. Further, moisture seems to pervade the place like it would "+
      "some subterranean lake, leading to an atmosphere of uncomfortable "+
      "wetness.\n"+
      "The only noteworthy object is the single blood red column of light that "+
      "dominates the center of this room.\n");
   add_item(({"sacrificial chamber","chamber","dark chamber","damp chamber"}),
      "A dreary and depressing place, it is where you are now.\n");
   add_item(({"dark stone","stone"}),
      "The unusually black rock found throughout the Dark Dominion.\n");
   add_item(({"walls","wall","floor","ceiling"}),
      "It is composed of dark stone, cold and unyielding to the touch.\n");
   add_item(({"blood red column of light","blood red light","red light","light","column"}),
      "A beam of crimson energy that rises from the floor to and through the "+
      "ceiling up above.\n");
   add_exit(CPASS(drow/house5/temple),"up","@@check",-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
check()
{
   if(TP->query_average_stat() < 20)
      {
      write("You try to enter the column of light but fail!\n");
      say(QCTNAME(TP) + " tries to enter the column of light but fails!\n");
      return 1;
   }
   write("You feel yourself grow lighter as you are transported up by the column of light.\n");
   say(QCTNAME(TP) + " seems to grow lighter as " + TP->query_pronoun() + " is "+
      "transported up by the column of light.\n");
   return 0;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(SAC);
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(SAC);
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(SAC);
      ob3 -> move_living("M",TO);
   }
   if(!ob4)
      {
      ob4 = clone_object(SAC);
      ob4 -> move_living("M",TO);
   }
   if(!ob5)
      {
      ob5 = clone_object(SAC);
      ob5 -> move_living("M",TO);
   }
   if(!ob6)
      {
      ob6 = clone_object(SAC);
      ob6 -> move_living("M",TO);
      tell_room(TO,"A chorus of moans attracts your attention to a group of gnomes.\n");
   }
}
