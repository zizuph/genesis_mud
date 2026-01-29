/*Created by Stevenson*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object squirrel;

reset_icewall_room() {
   if (!squirrel) {
      squirrel=clone_object(ICE_CAST_M+"squirrel");
      squirrel->move(TO);
   }
}

create_icewall_room() {
   set_short("Base of Icewall Mountains");
   set_long(
      "You are at the base of the eastern edge of the Icewall "
      + "Mountains. As you glance at the mountains you notice a "
      + "small opening to the north. On the ground you see the "
      + "stream bubbling alongside some flowers. You wonder how "
      + "they could live here. "
      + "\n");
   
   add_item("flowers","They are a strange breed of Distinctyus Icelovits. "
      + "Although common to colder climates, they flourish quite well in sub-zero "
      + "temperatures.  They would probably melt if you touched them. "
      + "\n");
   add_cmd_item(({"flower","flowers"}),({"get","touch","pick"}),
      "They would melt if you did that.\n");
   add_item("ground","It isn't so icy here.  Perhaps the stream is the reason.\n");
   add_item("mountains","They are huge and intimidating.\n");
   
   add_item("stream","It gurgles merrily, giving nourishment to the "
      + "flowers.\n");
   
   add_item("opening","It appears to be the entrance to a cave.\n");
   add_cmd_item("cave","enter","@@go_cave");
   
   add_exit(ICE_FOREST+"forest_9","west");
   add_exit(ICE_FOREST+"forest_12","southeast");
   
   reset_icewall_room();
}

string go_cave() {
   write("You carefully enter the cave.\n");
   say(QCTNAME(TP)+" disappears into the strange opening.\n");
   TP->move_living("M",ICE_FOREST+"tunnel");
   return "";
   
}
