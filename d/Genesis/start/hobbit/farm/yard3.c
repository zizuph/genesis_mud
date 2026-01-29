/*
 *  The yard of the farm
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

public void
create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Yard");
   set_long("You are in the utmost northern part of the farmyard. "
    + "In contrast to the rest of the yard, there are virtually "
    + "no hoofprints on the soil. There is a tree here, with a "
    + "sign on it. West of here is a small shed, south the "
    + "yard continues.\n");

   add_item("soil", 
      "Not many animals have walked here, since the soil shows only "
    + "a few hoofprints.\n");

   add_item(({"willow","tree"}), 
      "The willow looks old with its hanging branches. Birds like "
    + "the tree, because they can comfortably build their nests "
    + "in the broad treetop.\n");

   add_item("sign", "@@sign_long");

   add_exit(STAND_DIR + "yard4","west");
   add_exit(STAND_DIR + "yard2","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}

init() {
   ::init();
   add_action("do_read", "read", 0);
}

do_read(str) {
   if (str == "sign")
   {
      write(sign_long());
      return 1;
   }
}

sign_long() {
   return 
      "The sign reads: 'BEWARE! Vicious dog!'. Below the words is a "
    + "drawn picture of a really mean and ugly looking dog.\n";
}