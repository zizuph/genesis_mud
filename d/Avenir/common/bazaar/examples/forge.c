inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

#define MY_SHOVEL  (STAND_OBJ + "shovel")
#define MY_KNIFE   (STAND_WEAPON + "sell_knife")
#define MY_AXE     (STAND_WEAPON + "sell_axe")
#define MY_SWORD   (STAND_WEAPON + "sell_sword")

object weapon;
static object bill;

create_room() {
   set_short("Forge");
   set_long(break_string(
      "The heat in this forge is almost unbearable. You wonder "
    + "how the blacksmith can work in these circumstances. The blacksmith "
/*  + "is capable of straightening bent weapons and " */
    + "sells some tools and weapons here. "
    + "A little sign is hanging on the wall.\n",70));

   add_item(({"sign","little sign"}),"@@sign_long");

   add_exit(STAND_DIR + "lpath1", "north");

   add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
   reset_room();
}

reset_room() {
   if (!find_living("_blacksmith_"))
      clone_object(STAND_MONSTER + "blacksmith")->move(this_object());

/* addition made by merrygrin */

   if (!bill) {
      bill = clone_object(STAND_MONSTER + "son_of_smith");
      bill->move(this_object());
    }

    if (!present("iron"))
	clone_object(STAND_OBJ + "cast_iron")->move(this_object());
}

init() {
   ::init();
   add_action("do_read","read",0);
}

sign_long() {
   int p1, p2, p3, p4;

   seteuid(getuid());
   p1 = MY_SHOVEL->query_prop(OBJ_I_VALUE) * 2;
   p2 = MY_KNIFE->query_prop(OBJ_I_VALUE) * 2;
   p3 = MY_AXE->query_prop(OBJ_I_VALUE) * 2;
   p4 = MY_SWORD->query_prop(OBJ_I_VALUE) * 2;

   return 
      "Tools:\n"
    + "--------\n"
    + "Shovel . . . .  " + p1 + " copper coins\n"
    + "\n"
    + "Weapons:\n"
    + "--------\n"
    + "Long knife . . . . . .  " + p2 + " copper coins\n"
    + "Sturdy axe . . . . . .  " + p3 + " copper coins\n"
    + "Mediocre sword . . . .  " + p4 + " copper coins\n"
/*
    + "Weapon improvement:\n"
    + "-------------------\n"
    + "Harden <weapon>  . . . . . xx  copper coins\n"
    + "Sharpen <weapon> . . . . . xx  copper coins\n"
    + "Straighten <weapon>  . . . xx  copper coins\n"
*/
    + "\n";
}

do_read(str) {
   if (str == "sign" || str == "little sign")
   {
       write("You read:\n" + sign_long());
       return 1;
   }
   return 0;
}
