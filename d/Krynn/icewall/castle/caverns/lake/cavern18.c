/*Created by Stevenson*/
/* room containing the ball for the puppy in the study */
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <stdproperties.h>
inherit ICEINROOM;

object ball;

reset_icewall_room() {
   if (!ball) {
      ball=clone_object(ICE_CAST_O+"ball");
      ball->move(TO);
   }
}

create_icewall_room() {
   set_short("Stalactites & Stalagmites");
   set_long(
      "You are in a room of beauty. Mineral-rich water dripping from the "
      + "ceiling has caused many stalagmites and stalactites to form "
      + "capturing the colors of the rainbow. As their colors reflect off "
      + "the face of the water you are nearly blinded with the brilliance. "
      + "Gazing north and east you see dry land. "
      + VBFC("check_float")
      +"\n");
   
   add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
   
   add_item("ceiling","You can see water dripping from it down onto "
      + "stalagmites.\n");
   add_item("rainbow","It is very colorful.\n");
   add_item("stalactites","They descend from the ceiling.\n");
   add_item("stalagmites","They stick out from the ground.\n");
   add_item("water","The reflections of the stalagmites and stalactites "
      + "merge into a colorful rainbow in the water.\n");
   add_item("land","The dry land is north and east of you.\n");
   
   add_exit(CAVE+"cavern17.c","west");
   add_exit(CAVERNS+"cavern19.c", "north");
   add_exit(CAVERNS+"cavern20.c","east");
   
   reset_icewall_room();
}

string check_float() {
   if (ball && E(ball)==TO) 
      return "Next to you is a ball floating in the water. ";
   return "";
}
