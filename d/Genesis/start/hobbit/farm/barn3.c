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
      "You have entered the part of the barn where the cows are kept. "
    + "The floor is covered with soft straw, and in the middle of it is "
    + "a gutter which leads outside where the manure flows through.\n");

   add_item("manure", 
      "The manure is brownish and smells a bit. You stick your hand in it "
    + "and taste a bit. Yuck! It tastes like shit! Well, what did you "
    + "expect it to taste anyway?\n");

   add_item("gutter", 
      "You take a look at the gutter and see that it was made to flush "
    + "the cow manure out of the barn.\n");

   add_item(({"soft straw","straw"}), 
      "The soft straw is for the cows to lie on, but it is also the "
    + "food that they spread around when they are eating.\n");

   add_exit(STAND_DIR + "barn1","north");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   reset_room();
}

reset_room() {
   object *arr;
   int i,s;

   if (!(s = sizeof(arr = all_inventory(this_object()))) ||
      (s = sizeof(filter(arr, "is_cow", this_object()))) < 4)
   {
      for (i=0; i<(4-s); i++)
         clone_object(STAND_DIR + "cow")->move(this_object());
   }
}

is_cow(obj) { return obj->id("_barn_cow_"); }
