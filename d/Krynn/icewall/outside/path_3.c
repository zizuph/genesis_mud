#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

create_icewall_room() {
   set_short("Upward sloping path");
   set_long(
      "You are on a twisty path which leads to the plains. "
      + "Because of the wind, your visibility is almost gone. "
      + "To the north you can dimly make out some mountains. "
      + "\n");
   
   add_item("mountains","The Mountains of Icewall make this quite a safe little Valley.\n");
   add_item("snow","It makes Icewall white.\n");
   add_item("plains","They are north of here somewhere.\n");
   add_item("path","It widens to the southwest and narrows uphill.\n");
   add_exit(ICE_OUT+"path_2","southwest");
   add_exit(ICE_OUT+"path_4","north","@@screach");
}

screach() {
   write("You hear a blood-curdling screech in the distance.\n\n");
   return 0;
}
