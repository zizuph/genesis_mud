/*
 *  Inside the farm
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room() 
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Farm");
   set_long(
      "This is the living room of the farm. On the wall are shelves "
    + "with little statues of animals on them. On the floor is a "
    + "big, heavy rug. In the middle of the room is a table with "
    + "some chairs around it. There is a lovely smell coming from "
    + "the north and to the west is a bedroom.\n"); 

   add_item(({"shelf","shelves"}), 
      "The shelves are made of oak. On them are several statues of "
    + "animals made of precious china, such as cows, goats and pigs.\n");

   add_item("table", 
      "In the middle of the table is a candle. The farmers do not stay "
    + "up very late, because they have to get up early in the morning. "
    + "But when they have visitors they make an exception and sit "
    + "around the table with them, to tell each other stories.\n");

   add_item(({"chair","chairs"}), 
      "The chairs are made of oak and look strong enough to hold you. "
    + "They have been placed around the table in a circle.\n");

   add_exit(STAND_DIR + "farm1","east");
   add_exit(STAND_DIR + "farm3","west");
   add_exit(STAND_DIR + "farm4","north");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an indoor room */
}