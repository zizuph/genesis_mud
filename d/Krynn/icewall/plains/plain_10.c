/* Created by Stevenson */
/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object igloo;

reset_icewall_room() {
   if (!igloo) {
      igloo = clone_object(ICE_CAST_O+"igloo");
      igloo->move(TO);
   }
}

create_icewall_room() {
   set_short("igloo");
   set_long(
      "You see many igloos here and wonder whose camp it is. One igloo seems "
      + "more prominent than the others. "
      + "There are many tracks in the snow. "
      + "\n");
   
   add_item("igloo","Actually, the igloos appear to be deserted. One, "
      + "however, seems different.\n");
   add_item("tracks","The tracks appear to be web-shaped with large "
      + "claws.\n");
   add_item("snow","It is filled with strange-looking tracks.\n");
   add_cmd_item("igloo","enter","@@igloo");
   
   add_exit(ICE_PLAINS+"plain_8","north");
   
   reset_icewall_room();
}

string igloo() {
   write("You cautiously step into the igloo.\n");
   say(QCTNAME(TP)+" ducks "+TP->query_possessive()+" head and enters the igloo.\n");
   tell_room(ICE_PLAINS+"plain_9",QCTNAME(TP)+" steps in out of the cold.\n");
   TP->move_living("M",ICE_PLAINS+"plain_9",1);
   return "";
}
