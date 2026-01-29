inherit "/std/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"

create_room() {
   set_short("bushy field");
   set_long(
      "You find yourself on the other side of the bushes. "
    + "On the floor you see traces of activity in the soil. "
    + "Perhaps you can make something out of them. There are exits in many "
    + "directions, including the one through the bushes to the west.\n");

   add_item(({"bush","bushes"}), break_string(
      "The dense bushes block the view of whatever is behind them. They "
    + "look like the bushes that commonly grow in the Shire.\n",70));

   add_item(({"soil","traces"}), "@@traces_long");


   add_prop(ROOM_I_INSIDE,0);

   add_exit(HOBBIT_DIR + "field3","west",0,1);
   add_exit(HOBBIT_DIR + "camp2","south",0,1);
   add_exit(HOBBIT_DIR + "camp3","east",0,1);
   reset_room();
}

reset_room() {
   if (!present("orc"))
      clone_object(HOBBIT_DIR + "npc/sleeping_orc")->move(TO);
}

traces_long() {
   string str;
   int sk;

   sk = this_player()->query_skill(SS_TRACKING);


   str = "The dry soil shows many traces of footsteps.";

   if (sk > 15)
   {
       str += " The footsteps are Orc footsteps.";
       if (sk > 25)
          str += " In fact, you can see clearly that it must have been "
               + "some orcs from Isengard, judging from the way they "
               + "have stomped on the ground.";
       str += " Big footsteps lead east, and smaller ones lead south.";
       if (sk > 25)
          str += " The big footsteps are probably made by dangerous White "
               + "Hand orcs, and the smaller one by regular orcs.";
    }
    return break_string(str + "\n", 70);
}
