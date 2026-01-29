inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room()
{
   object ob1;
   set_short("An intersection.\n");
   set_long("Having trapsed through the long, dank corridors you come " +
      "across this approximately twenty foot diameter round intersection " +
      "with a vaulted ceiling extending deep into the dark depths above " +
      "you.  The floor here is geometrically arranged with large, curved " +
      "stone blocks like in the walls, but arranged in a circle around an " +
      "oddly shaped center stone.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("block", "These are large, dark blocks of stone approximately one by two feet in dimension.  They all appear to be nearly identical so you figure they must have been worked on by a master stoneworker.\n");
   add_item("blocks", "These are large, dark blocks of stone approximately one by two feet in dimension.  They all appear to be nearly identical so you figure they must have been worked on by a master stoneworker.\n");
   add_item("center stone", "This stone is smooth, more polished then the rest a bit, and expertly set into the floor perfectly level obviously by a truly skillfull master craftsman.\n");
   add_item("ceiling", "The ceiling extends upward at least twenty feet where stones jut out from it in an asthetically pleasing pattern offering perches perhaps for creatures able to cling to walls.\n");
   ob1 = clone_object("/d/Rhovanion/common/dungeon1/living/bats.c");
   ob1->move(this_object());
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun8","northeast");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun2","south");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun3","west");
}
