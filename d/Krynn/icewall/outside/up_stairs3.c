/* Created By Stevenson */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

object door;

void reset_icewall_room() {
   if (!door) {
      door=clone_object(ICE_CAST_O+"housedoor");
      door->move(TO);
   }
}

void create_icewall_room() {
   set_short("Front of house");
   set_long(
      "A fierce wind screams around you. It threatens to knock you off from "
      + "this high spot in Icewall. You can detect a building "
      + "in front of you, through the thick, icy winds. "
      + "You can climb back down the stairs or venture inside. "
      + " \n");
   
   add_item(({"house","building"}),
      "It is rather large and imposing. You can enter it to the north.\n");
   
   add_exit(ICE_OUT+"up_stairs2","down");
   add_exit(ICE_CAST1_R+"main_hall","north");
   
   reset_icewall_room();
}

