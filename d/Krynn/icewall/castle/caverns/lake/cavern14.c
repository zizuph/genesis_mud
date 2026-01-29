/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEINROOM;

init() {
   ADA("jump");
   ::init();
}

create_icewall_room()
{
   set_short("On A Small Ice Block");
   set_long(
      "You are standing upon a small block of ice which is floating "
      + "in the lake. Judging from the look of the water you probably "
      + "don't want to fall in for fear of drowning. Another block of "
      + "ice is just east of you. To the west you can make out a path "
      + "heading uphill. "
      +"\n");
   
   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
   add_item(({"block","ice"}),"You certainly cannot walk to the other block of "
      + "ice. Perhaps there is another way?\n");
   add_item("water","It is very deep and you prefer not to enter it.\n");
   add_cmd_item("water","enter","It is too deep for that.\n");
   
   add_exit(CAVERNS + "cavern13.c", "west");
}

int jump(string str) {
   if (str == "east") {
      write("You carefully jump east, aiming for the block of ice and "
         + "not the deep water.\n");
      say(QCTNAME(TP)+" jumps from the block of ice.\n");
      tell_room(CAVE+"cavern15",QCTNAME(TP)+" jumps from the other block "
         + "of ice and lands right next to you.\n");
      TP->move_living("M",CAVE+"cavern15",1); /*don't follow*/
      return 1;
   }
   NF("Jump Where?\n");
   return 0;
}
