/*
 *  The yard of the farm
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Yard");
   set_long(
      "You are standing behind the main building of the farm, "
    + "near a shed that is too small for you to "
    + "enter. There is a long chain fastened to the shed. The "
    + "smell of a dog comes from within the shed. You can go "
    + "east, back to the yard.\n");

   add_item("shed",
      "The shed is used as a shelter for the guard dog of the farm. "
    + "It has been the home of the dog for many years.\n");

   add_item("chain",
      "The chain is bolted to the shed with big bolts and nuts on one end, "
    + "it is connected to a dog-collar on the other end. "
    + "The chain is about 15 feet long, giving the guard dog enough reach "
    + "to get you.\n");

   add_item(({"building","main building"}),
      "The building is a typical hobbit building. You are looking at a "
    + "blind wall, since hobbits do not like windows.\n");

   add_exit(STAND_DIR + "yard3","east");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */

   if(!present("dog"))
      clone_object(STAND_DIR + "dog")->move(this_object());
}

reset_room() {
   if(!present("dog"))
      clone_object(STAND_DIR + "dog")->move(this_object());
}