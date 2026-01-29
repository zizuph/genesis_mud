/* Created by Stevenson */
/* Created by Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEINROOM;

object pole;

void reset_icewall_room() {
   if (!pole) {
      pole = clone_object(ICE_CAST_O+"pole");
      pole->move(TO);
   }
}

void create_icewall_room() {
   set_short("Inside an igloo");
   set_long(
      "You are inside a remarkably large igloo. A large mat made of "
      + "bear fur covers the floor, and an old campfire is in the "
      + "exact center of the room. Strangely, nobody is here. "
      + "\n");
   
   add_item(({"rug","mat","fur"}),"The fur is actually from a polar bear.\n");
   add_item("campfire","The fire has been out for some time.\n");
   
   add_exit(ICE_PLAINS+"plain_10","out");

   reset_icewall_room();
}
