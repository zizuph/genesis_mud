inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Mute made this, too.\n");
   set_long("This long, immaculate passageway makes a sharp " +
      "turn here.  It is nearly featureless, adorned only with " +
      "a sconch on the northwest edge of the turn.  It contains " +
      "three torches, all lit.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item("sconch","This is a dark, filthy, copper " +
      "sconch set onto the northwest edge of the turn.  It " +
      "contains three brightly lit torches.\n");
   add_item(({"torch","torches"}), "These are simple, " +
      "wooden torches with some especially combustive substance " +
      "topping them.  They are burning rather brightly.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/guard4","west","@@part_check");
   add_exit("/d/Rhovanion/mute/dungeon1/guard2","north");
   room_add_object("/d/Rhovanion/mute/dungeon1/wguard2.c",1,
      "An odd figure steps out from around the corner to oppose you.");
}
int part_check() {
   if(TP->query_npc()) { return 0; }
   if (present("guard",TO))
      {
      write("The guard won't let you pass.\n");
      say(QCTNAME(TP)+" tries to pass the guard west, but " +
         "jumps back cringing in fear as the guard bares his steel " +
         "bladed claws.\n");
      return 1;
   }
   return 0;
}
