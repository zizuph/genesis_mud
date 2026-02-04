inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

object weapon;

create_room() {
   set_short("Forge");
   set_long(break_string(
      "The heat in this forge is almost unbearable. You wonder "
    + "how the blacksmith can work in these circumstances. Here "
    + "you can have your weapons improved, or you can buy a weapon "
    + "here. "
    + "A little sign is hanging on the wall.\n",70));

   add_item(({"list","pricelist","sign","little sign"}),
      "Weapons:\n"
    + "--------\n"
    + "Knife ......  12 copper coins\n"
    + "Axe   ...... 139 copper coins\n"
    + "Sword ...... 527 copper coins\n"
    + "\n"
    + "Weapon improvement:\n"
    + "-------------------\n"
    + "Wax weapon     ...... 70  copper coins\n"
    + "Sharpen weapon ...... 99  copper coins\n"
    + "Harden weapon  ...... 430 copper coins\n");

   add_exit(STAND_DIR + "h_lane2", "west");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
}

init() {
   ::init();
   add_action("do_buy","buy",0);
   add_action("do_wax","wax",0);
   add_action("do_sharpen","sharpen",0);
   add_action("do_harden","harden",0);
}

do_buy(str) {
   if(!str)
      return 0;
   write("The blacksmith says: Sorry, all is sold out!\n");
   return 1;
}

do_wax(str) {
   if(!str || !(weapon = present(str,this_player())))
      return 0;
   write("The blacksmith says: I am sorry, I am out of wax!\n");
   return 1;
}

do_sharpen(str) {
   if(!str || !(weapon = present(str,this_player())))
      return 0;
   write("The blacksmith says: I am sorry, I cannot do that now!\n");
   return 1;
}

do_harden(str) {
   if(!str || !(weapon = present(str,this_player())))
      return 0;
   write("The blacksmith says: I am sorry, I do not have the proper tools!\n");
   return 1;
}
