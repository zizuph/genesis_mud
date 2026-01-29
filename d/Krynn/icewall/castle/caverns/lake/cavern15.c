/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEINROOM;

object penguin;

init() {
   ADA("jump");
   ::init();
}

reset_icewall_room() {
   if (!penguin) {
      penguin = clone_object(ICE_CAST_M+"peng2");
      penguin->move(TO);
   }
}

create_icewall_room()
{
   set_short("On A Small Ice Block");
   set_long(
      "You are standing upon a small block of ice which is floating "
      + "in the lake. Judging from the look of the water you probably "
      + "don't want to fall in for fear of drowning. Another block of "
      + "ice is just west of you. " + VBFC("check_peng") + " "
      +"\n");
   
   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
   
   add_item(({"block","ice"}),"You certainly cannot walk to the other block of "
      + "ice. Perhaps there is another way?\n");
   add_item("water","It is very deep and you prefer not to enter it.\n");
   add_cmd_item("water","enter","It is too deep for that.\n");
   
   add_exit(CAVE + "cavern3.c", "southwest");
   
   reset_icewall_room();
}

int jump(string str) {
   if (str == "west") {
      write("You carefully jump west, aiming for the block of ice and "
         + "not the deep water.\n");
      say(QCTNAME(TP)+" jumps from the block of ice.\n");
      tell_room(CAVE+"cavern14",QCTNAME(TP)+" jumps from the other block "
         + "of ice and lands right next to you.\n");
      TP->move_living("M",CAVE+"cavern14",1); /*don't follow*/
      return 1;
   }
   NF("Jump Where?\n");
   return 0;
}

string check_peng() {
   if (penguin && E(penguin)==TO)
      return "Sitting next to you is a lonely penguin.";
   return "";
}
