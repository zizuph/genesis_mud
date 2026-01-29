/*
 * Hill lane 
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt"); 
   set_short("On Hill lane south of the crossroad");
   set_long("You are standing on a narrow part of Hill lane in the centre "
    + "of Hobbiton. Along the road on both sides are some trees "
    + "planted. It looks like this is a busy part of the "
    + "village. You can see several hobbits walking around here. "
    + "To the east is a low stone building, you see some smoke "
    + "coming out of the chimney. On the west side of the road is a "
    + "building with a large sign hanging on a pole. "
    + "South you see more people and north is a crossroad.\n");

   add_item(({"sign","large sign"}), "@@sign_long");
   add_item("pole","The pole is secured to the front of the building.\n");

   add_exit(STAND_DIR + "cr_road","north");
   add_exit(STAND_DIR + "h_lane3","south");
   add_exit(STAND_DIR + "forge","east");
   add_exit(STAND_DIR + "shop","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
}

init() {
   ::init();
   add_action("do_read","read",0);
}

do_read(str) {
   if(!str || str == "")
      return 0;
   if (str == "sign" || str == "large sign");
   {
      write(sign_long());
      return 1;
   }
   return 0;
}

sign_long() {
   return "On the large sign you read 'Drugstore'.\n";
}