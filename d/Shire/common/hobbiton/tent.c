inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"

create_room() {
   set_short("commandtent");
   set_long(break_string(
      "You are inside a field tent. This is where the commander of the "
    + "group of orcs hangs out when he is waiting for a scout to return. "
    + "The commander's tent is filled with empty bottles, so you deduce "
    + "that the commander is quite a party-animal.\n",70));

   add_item(({"bottles","empty bottles"}), break_string(
      "The empty bottles smell disgusting. Whatever the commander drinks, "
    + "it smells awful.\n",70));

   add_prop(ROOM_I_INSIDE,1);

   add_exit(STAND_DIR + "camp4","out",0,1);

   reset_room();
}

reset_room() {
   if (!present("_leader_orc_"))
      clone_object(STAND_MONSTER + "leader_orc")->move(this_object());
   if (!present("_orc_prisoner_"))
      clone_object(STAND_MONSTER + "prisoner")->move(this_object());
}
