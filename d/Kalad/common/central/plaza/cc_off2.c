/*
ROOM: City Council Intelligence Agency
BY:   Sebster
DATE: Aug 27, 1994
*/

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
object ob1;

void
create_room()
{
   ::create_room();
   hear_bell = 2;
   add_prop(ROOM_I_INSIDE, 1);
   
   set_short("The Council Intelligence Agency");
   set_long(
      "This is the Council Intelligence Agency. You have the feeling that "+
      "you are being watched, and notice the portrait of Joe; he's looking "+
      "at you. There is also a large table in the center of the room where "+
      "fellow spies play poker.\n"
   );
   
   add_prop(ROOM_NO_TIME_DESC, 1);
   
   add_exit(CENTRAL(plaza/cc_hall2), "east", 0, 0, 0);
   
   add_item("table",
      "On the expensive looking table, clad in green velvet, lies a deck "+
      "of cards.\n"
   );
   
   add_item("portrait",
      "The portrait of Joe, the most infamous spy of all, seems to be "+
      "looking at you. What an old trick! Can't they ever come up with "+
      "something new?\n"
   );
   
   add_item(({"deck", "cards"}),
      "You count the cards, and notice there are several aces too many.\n"
   );
   set_alarm(1.0,0.0,"reset_room");
}

reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cc_spy");
      ob1 -> arm_me();
      ob1->move_living("xxx",TO);
   }
}
