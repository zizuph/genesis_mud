inherit "/std/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"

create_room() {
   set_short("orc camp");
   set_long(break_string(
      "You have stumbled upon an orc camp. This is where the "
    + "orc footsoldiers have to lie in the grass. "
    + "West is the entrance of the camp, south is another corner of the "
    + "camp.\n",70));

   add_prop(ROOM_I_INSIDE,0);

   add_exit(HOBBIT_DIR + "camp1","west",0,1);
   add_exit(HOBBIT_DIR + "camp4","south",0,1);
   reset_room();
}

reset_room() {
   object *arr;
   int i,s;

   if (!(s = sizeof(arr = all_inventory(this_object()))) ||
      (s = sizeof(filter(arr, "is_orc", this_object()))) < 2)
   {
      for (i=0; i<(2-s); i++)
         clone_object(NPC_DIR + "random_orc")->move(TO);
   }
}

is_orc(obj) { return obj->id("_random_orc_"); }

