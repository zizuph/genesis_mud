/*
 *  The yard of the farm
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room() 
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("Yard");
   set_long("You are in the northern part of the farmyard. "
    + "The soil here has been trampled by hoofs. There is a washing "
    + "line hanging from one pole to another. The yard continues "
    + "both north and south.\n");

   add_item("soil", 
      "Many animals must have walked here, since the loose soil "
    + "shows marks of all kinds of hoof and footprints. They seem "
    + "to lead south.\n");

   add_item(({"washing line","line","pole","poles"}), 
      "There are two poles standing here, securely fastened to the "
    + "ground. Between them hangs an orange rope, which is used to "
    + "hang clothes on to dry.\n");

   add_exit(STAND_DIR + "yard3","north");
   add_exit(STAND_DIR + "yard1","south");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}