/*
 *  Inside the barn.
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>

create_room() 
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Barn");
   set_long(
      "On this side of the barn is the mudpool of the pigs. The pigs "
    + "just love to crawl and roll around in the brown mud. To the east "
    + "is the entrance in the middle of the barn.\n");

   add_exit(STAND_DIR + "barn1","east");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   reset_room();
}

reset_room() {
   object *arr;
   int i,s;

   if (!(s = sizeof(arr = all_inventory(this_object()))) ||
      (s = sizeof(filter(arr, "is_pig", this_object()))) < 4)
   {
      for (i=0; i<(4-s); i++)
         clone_object(STAND_DIR + "pig")->move(this_object());
   }
}

is_pig(obj) { return obj->id("_barn_pig_"); }
