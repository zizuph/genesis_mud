/*Created by Macker 07/14/94*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;


int num_fish = 3;
object fisher1, fisher2, fisher3;

void
reset_icewall_room()
{
   if(!fisher1)
      {
      (fisher1 = clone_object(PLAINS_L + "fisher2"))->move(TO);
      tell_room(TO, "An ice folk fisherman arrives.\n");
   }
   if(!fisher2)
      {
      (fisher2 = clone_object(PLAINS_L + "fisher2"))->move(TO);
      tell_room(TO, "An ice folk fisherman arrives.\n");
   }
   if(!fisher3)
      {
      (fisher3 = clone_object(PLAINS_L + "fisher2"))->move(TO);
      tell_room(TO, "An ice folk fisherman arrives.\n");
   }
   return;
}

init()
{
   ADD("fishfunc","catch");
   ::init();
}

create_icewall_room() {
   set_short("Frozen Pond");
   set_long(
      "This is a frozen pond where the ice folk often " +
      "come to fish. Their village is to the southwest. It " +
      "is very cold here. Actually it is very cold everywhere around here.\n");
   
   add_item( ({"ground", "snow", "ice", "path", "road"}),
      "It is white and cold. What did you expect?\n");
   
   add_item( ({"pond", "frozen pond", "frozen over pond", "fishing area"}),
      "The frozen pond in front of you is often used by the " +
      "ice folk for fishing. There are some small holes in the ice. " +
      "\n");
   
   add_item("holes", "The fishermen drop their fishing lines " +
      "through these holes into the freezing water.\n");
   
   add_item("village", "The village is to your soutwest. Why don't you go check it out?\n");
   
   
   add_exit(FISHING + "fishing_1.c", "southwest");
   reset_icewall_room();
}


int fishfunc(string str) {
   NF("Catch what?\n");
   if (!P("icepole",TP)) return 0;
   if (str != "fish" && str != "fish with pole") return 0;
   if (!num_fish) {
      NF("I guess they just aren't biting today.\n");
      return 0;
   }
   write("You cast the line far out into the pond and "
      + "before it even touches the water, a large fish jumps "
      + "out of the water and gets hooked.\n\nYou place the "
      + "fish into your inventory.\n");
   clone_object(PLAINS_O + "fish")->move(TP);
   num_fish--;
   say( QCTNAME(TP) + " jerks " + POSSESSIVE(TP) +
      " fishing pole towards the pond "
      + "and immediately catches a fish.\n");
   return 1;
}

