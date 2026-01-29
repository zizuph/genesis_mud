/*
 * Bywater Road 
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("The Bywater road");
   set_long("You are on a well travelled road in the centre of Hobbiton. "
    + "Many people have passed here over the years. "
    + "On both sides of the road are some trees planted, and "
    + "you can see some children playing around them. "
    + "To the west is an intersection of this road and another one. "
    + "You can smell an unknown scent from the alchemist's house to "
    + "the north, maybe he has discovered something interesting. "
    + "A new shop has opened to the south, and you smell leather oil coming from it. "
    + "There is a little sign pointing east here.\n");

   add_item("sign", 
      "The little sign is attached to a tree trunk and points to the east. "
    + "Some words have been scribbled on it.\n");

   add_exit(STAND_DIR+"alchemists","north");
   add_exit(STAND_DIR+"bw_road6","east");
   add_exit(STAND_DIR+"cr_road","west");
   add_exit("/d/Shire/common/hobbiton/cobbler","south",0,1);

   add_prop(ROOM_I_INSIDE,0);  /* This is an open air room */
}

init() {
   ::init();
   add_action("do_read","read",0);
}

do_read(str) {
   if (str == "" || !str) return 0;
   str = lower_case(str);
   if (str == "sign" || str == "words") {
      write("The sign says: Hobbiton Post-office\n");
      say(QCTNAME(this_player()) + " reads the little sign.\n");
      return 1;
   }
   return 0;
}