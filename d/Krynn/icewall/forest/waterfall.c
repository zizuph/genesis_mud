/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Icy Waterfall");
   set_long(
      "A mighty waterfall stands before you. Its roar is deafening as it "
      + "bursts from the mountain and falls into the pool before you. "
      + "You can almost see through the waterfall but not quite. "
      + "There is also an opening in the face of the mountain through which "
      + "you may pass. "
      + "\n");
   
   add_item("mountain","The mountains surround this area. There is an opening "
      + "in the mountain just in front of you.\n");
   add_item(({"waterfall","water"}),"There might be a room behind it...\n");
   add_item("pool","It is filled with very cold water.\n");
   add_item(({"pass","opening"}),"The opening is actually the entrance "
      + "to a narrow pass.\n");
   add_cmd_item(({"pass","opening"}),"enter","@@pass");
   
   add_cmd_item("waterfall","enter","@@go_waterfall");
   
}

string go_waterfall() {
   write("You jump into the waterfall.\n");
   say(QCTNAME(TP)+" disappears behind the waterfall.\n");
   tell_room(ICE_OUT+"back_waterfall",QCTNAME(TP)
      + " arrives through the waterfall.\n");
   TP->move_living("M",ICE_OUT+"back_waterfall",1,0);
   return "";
}

string pass() {
   set_dircmd("pass");
   write("You carefully squeeze into the narrow pass.\n");
   say(QCTNAME(TP)+" wiggles into the opening.\n");
   tell_room(ICE_FOREST+"forest_15",QCTNAME(TP) + " arrives, "
      + "squeezing out of the tight pass.\n");
   TP->move_living("M",ICE_FOREST+"forest_15");
   return "";
}
