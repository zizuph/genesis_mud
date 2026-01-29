/*
 *  The bedroom of the farm
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
      "This is the bedroom of the farm. On the wall hang several pictures "
    + "of interesting people who have visited the farm. The room has no "
    + "windows, which could be expected from a hobbit building. "
    + "To the east is the livingroom, from which a lovely smell "
    + "emerges.\n"); 

   add_item("pictures", 
      "There are many pictures hanging on the walls. Among them you see "
    + "a picture of a sturdy looking hobbit, with a big pipe. Under it "
    + "you read: 'Bilbo Baggins'.\n");

   add_exit(STAND_DIR + "farm2","east");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an indoor room */
}