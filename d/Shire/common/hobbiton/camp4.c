inherit "/std/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_room() {
   set_short("orc camp");
   set_long(break_string(
      "You have stumbled upon an orc camp. This is where the "
    + "orc footsoldiers have to lie in the grass. In a corner under a "
    + "tree, stands a small tent for the orcs in charge. "
    + "To the north and the west lies the rest of the camp.\n",70));

   add_item(({"small tent","tent"}), break_string(
      "The tent was put up for the commanding orc. Judging from the size "
    + "of the tent, the leader of this group of orcs must be big.\n",70));

   add_item("grass",
      "The grass is flat from the many feet that have trodden over it.\n");

   add_prop(ROOM_I_INSIDE,0);

   add_exit(HOBBIT_DIR + "camp2","west",0,1); 
   add_exit(HOBBIT_DIR + "camp3","north",0,1);
   add_exit(HOBBIT_DIR + "tent","in","@@may_enter",1);
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

may_enter() {
   object *arr;
   int s;

   if (!sizeof(arr = all_inventory(this_object())) ||
        (s = sizeof(filter(arr, "is_orc", this_object()))) > 0)
   {
      if (s == 1)
      {
         write("The orc stops you from entering the tent.\n");
         say("The orc stops " + QCTNAME(this_player())
           + " from entering the tent.\n"); 
         return 1;
      }
      else
      {
         write("One of the orcs stops you from entering the tent.\n");
         say("One of the orcs stops " + QCTNAME(this_player())
           + " from entering the tent.\n"); 
         return 1;
      }
   }
   return 0;
}

is_orc(obj) { return obj->id("_random_orc_") && living(obj); }

  
