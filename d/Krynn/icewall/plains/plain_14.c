/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

void create_icewall_room() {
   set_short("Tunnel Entrance");
   set_long(
      "You are on the frozen plains of Icewall. There is "
      + "a peculiar sense of quiet in the area. You wonder "
      + "what life could possibly survive in this harsh "
      + "climate. Just to the south of you is a small "
      + "opening the face of the mountains. "
      + "\n");
   
   add_item(({"opening","cave","mountain"}),
      "It appears to be the opening to some tunnel through "
      + "the mountains.\n");
   add_item("tunnel","Maybe you should enter it?\n");
   add_cmd_item("tunnel","enter","@@go_cave");
   
   add_exit(ICE_PLAINS+"plain_12","west");
   
}

string go_cave() {
   write("You carefully enter the cave.\n");
   say(QCTNAME(TP)+" disappears into the dark opening.\n");
   TP->move_living("M",ICE_PLAINS + "tunnel");
   return "";
}

