/*
ROOM: Council of Lords Spy Organization
BY:   Sebster
DATE: Aug 28, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"

void
create_room()
{
   ::create_room();
   hear_bell = 2;
   
   add_prop(ROOM_I_INSIDE, 1);  
   
   set_short("The Lords Spy Organisation");
   set_long(
      "This is the Lords Spy Organization. This organization is to make "+
      "sure that the lords know what is going on in the city. "+
      "You have the feeling that "+
      "you are being watched, and notice the portrait of Joe; he's looking "+
      "at you. The master "+
      "spy, Sir Espion, usually sits in this room, deciding who they are "+
      "to spy on next.\n"
   );
   add_item("portrait",
      "The portrait of Joe, the most infamous spy of all, seems to be "+
      "looking at you. What an old trick! Can't they ever come up with "+
      "something new?\n"
   );
   
   add_prop(ROOM_NO_TIME_DESC, 1);
   
   add_exit(CENTRAL(plaza/cl_hall2), "west", 0, -1, -1);
}

init()
{
   ::init();
   add_action("push","push");
   add_action("enter","enter");
   add_action("search","search");
}

search(string str)
{
   notify_fail("Search what?\n");
   if (!str) return 0;
   if (str=="portrait")
      {
      set_alarm(5.0,0.0,"search_result",TP);
      write("You start to search the portrait.\n");
      say(QCTNAME(TP)+" starts to search the portrait.\n");
      return 1;
   }
   return 0;
}

search_result(object who)
{
   if(who)
      {
      who->catch_msg("You realize that the portrait is a hatch!\n");
      return;
   }
}

push(string str)
{
   notify_fail("What?\n");
   if (!str || str!="portrait") return 0;
   write("You push the portrait of Joe.\n");
   say(QCTNAME(TP)+" pushes the portrait of Joe.\n");
   set_alarm(2.0,0.0,"do_push");
   return 1;
}

do_push()
{
   write("The portrait opens inwards, and then closes again. Its a hatch!\n");
   say("The portrait opens inwards, and then closes again. Its a hatch!\n");
}

enter(string str)
{
   notify_fail("Enter what?\n");
   if (!str || str!="portrait") return 0;
   write("You enter the portrait.\n");
   say(QCTNAME(TP)+" enters the portrait.\n");
   TP->move_living("entering the darkness.","/d/Kalad/common/central/plaza/cl_hidden1");
   return 1;
}
