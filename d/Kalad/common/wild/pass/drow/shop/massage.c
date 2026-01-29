/* A massage house! */
/* by Antharanos */
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define HAVE_BEEN_MASSAGED "_have_been_massaged"
#define BEING_MASSAGED "_being_massaged"
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A massage parlour");
   set_long("A dim room, lit only by eerily glowing violet faerie fire. "+
      "A strange spider web covers the archway in the west, while numerous "+
      "obsidian tables lie all about the room. A patch of darkness lies in "+
      "the east, conspiciously so. Incense seems to hang thickly "+
      "within the air, its source unbeknownst to you.\n");
   add_item(({"massage parlour","parlour","room","dim room"}),
      "An eerie, dimly lit room.\n");
   add_item(({"eerily glowing violet faerie fire","glowing violet faerie fire","glowing faerie fire","violet faerie fire","faerie fire","fire"}),
      "In varying shades of violet, it laces the length and breadth of the "+
      "room, providing a dim and eerie glow.\n");
   add_item(({"strange spider web","strange web","spider web","web"}),
      "A delicate covering, somewhat like a curtain.\n");
   add_item(({"obsidian tables","tables","table"}),
      "Long, flat surfaces where customers are massaged.\n");
   add_item(({"patch of darkness","darkness"}),
      "The only unlit spot within the entire room.\n");
   add_exit(CPASS(drow/shop/massage_entr),"west","@@check",-1,-1);
   set_noshow_obvious(1);
}
check()
{
   if(TP->query_prop(BEING_MASSAGED))
      {
      write("You can't leave, you're still being massaged!\n");
      return 1;
   }
   write("You head back towards the entrance room.\n");
   say(QCTNAME(TP) + " heads back towards the entrance room.\n");
   return 0;
}
void
init()
{
   ::init();
   AA(massage_me,massage);
}
int
massage_me(string str)
{
   if(!str || str != "me")
      {
      NF("You can only _be_ massaged, you can't massage anyone else!\n");
      return 0;
   }
   if(TP->query_prop(HAVE_BEEN_MASSAGED))
      {
      write("You've already had a massage!\n");
      return 1;
   }
   write("You quietly ask for a massage.\n");
   say(QCTNAME(TP) + " quietly asks for a massage.\n");
   TP->add_prop(HAVE_BEEN_MASSAGED,1);
   set_alarm(3.0,0.0,"do_massage");
   return 1;
}
void
do_massage()
{
   write("A strong, sensuous drow female enters the room.\n");
   say("A strong, sensuous drow female enters the room.\n");
   set_alarm(3.0,0.0,"massaging");
   return;
}
void
massaging()
{
   write("She massages you thoroughly, easing your sore muscles.\n");
   say("The drow female massages " + QTNAME(TP) + " thoroughly.\n");
   TP->add_prop(BEING_MASSAGED,1);
   set_alarm(3.0,0.0,"more_massage");
   return;
}
void
more_massage()
{
   write("She continues her massage and you feel as though all your worries "+
      "are slipping away.\n");
   say("The drow female continues her massage and it appears as "+
      "if " + QTNAME(TP) + "'s worries have been forgotten.\n");
   set_alarm(6.0,0.0,"end_massage");
   return;
}
void
end_massage()
{
   write("The drow female finishes her massage.\n");
   write("She pats you on the rump then is gone.\n");
   write("You feel much better!\n");
   say("The drow female finishes her massage.\n");
   say("The drow female pats " + QTNAME(TP) + " on the rump, then is gone.\n");
   TP->remove_prop(BEING_MASSAGED);
   return;
}
