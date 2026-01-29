/*
 * Hill lane, outside the bank
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

object trashcan;

/* Prototypes */
void reset_room();

void
create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("On the Hill lane outside the Guild");
   set_long("This is a very busy place in this village. "
    + "Here are several hobbits running in and out of a low, dark grey "
    + "building to the east. On a board beside the door you read "
    + "'Hobbiton Adventurers Guild'. "
    + "To the west is huge white building. "
    + "Above the entrance is a big sign with writing in gold on it. "
    + "There is a small plaque next to the door. "
    + "To the south Hill lane ends in a field.\n");

   add_item(({"sign","big sign"}),
      "The sign says: Bank of Hobbiton.\n");

   add_item(({"small plaque", "plaque"}),
      "It says: No entrance for goblins and gnomes.\n");

   add_exit(STAND_DIR + "h_lane2","north");
   add_exit(STAND_DIR + "guild","east");
   add_exit(STAND_DIR + "bank","west");
   add_exit("/d/Shire/common/hobbiton/er172","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */

   reset_room();
}

void
reset_room() {
   if (!present("gnome_trash")) {
      trashcan = clone_object(STAND_DIR + "trashcan");
      trashcan->move(this_object());
   }
}