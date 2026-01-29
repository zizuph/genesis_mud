/*
 *  The entrance of the farm
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
      "You are standing in front of the entrance to the farmhouse. "
    + "On the floor is a doormat with the word 'Welcome' embroidered "
    + "on it. A lovely smell comes from the inside. East is the middle "
    + "of the farmyard.\n"); 

   add_item(({"doormat","mat"}), 
      "The doormat is worn and old, but it still shows the good intentions "
    + "of the hobbits who live here. Because you don't want to be impolite, "
    + "you wipe your feet on it.\n");

   add_exit(STAND_DIR + "yard1","east");
   add_exit(STAND_DIR + "farm2","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}