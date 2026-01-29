inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   object ob1;
   set_short("An intersection.\n");
   set_long("You now are in an appriximately twenty foot diameter round " +
      "intersection with a vaulted ceiling extending deep into the dark " +
      "void above you.  The floor here is geometrically arranged with " +
      "large, curved stone blocks, but arranged in a circle around an " +
      "oddly shaped center stone.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("center stone", "This stone is smooth, more polished then the " +
      "rest a bit, and expertly set into the floor perfectly level obviously by " +
      "a truly skillfull master craftsman.\n");
   add_item("ceiling","Shining your light up, you see the ceiling " +
      "extends upward at least twenty feet where stones just out from " +
      "it in an asthetically pleasing pattern offering perches perhaps " +
      "for creatures able to cling to walls.\n");
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to be " +
      "nearly identical so you figure they must have been worked by " +
      "a master stoneworker.\n");
   add_item("stone", "The stone here is of a dark, dark almost black " +
      "color that is very dull in luster and reflects little light.\n");
   ob1 = clone_object("/d/Rhovanion/common/dungeon1/living/bats.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun5","southeast");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun6","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun7","north");
}
