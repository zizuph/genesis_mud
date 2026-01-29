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
      "You are in the eastern part of the barn. This is where the chickens "
    + "are kept. On the floor is wheat and corn, which is the favourite "
    + "kind of food of the little creatures. To the west is the entrance "
    + "of the barn.\n");

   add_exit(STAND_DIR + "barn1","west");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   reset_room();
}

reset_room() 
{
   object *arr;
   int i,s;

   if (!(s = sizeof(arr = all_inventory(this_object()))) ||
      (s = sizeof(filter(arr, "is_chicken", this_object()))) < 4)
   {
      for (i = 0; i< ( 4 - s); i++)
         clone_object(STAND_DIR + "chicken")->move(this_object());
   }
}

is_chicken(obj) { return obj->id("_barn_chicken_"); }
