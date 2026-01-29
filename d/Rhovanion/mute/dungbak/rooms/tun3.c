inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room()
{
   int i;
   object ob1;
   object ob2;
   set_short("Another one of those tunnels.\n");
   set_long("You are in another long, dark tunnel similar to the first you encountered, with large, stone blocks comprising the walls and ceiling and a flat slab of stone for the floor.  It's a little dirtier in here... there's some rat feces by the sides of the passageway.  There is a scent of dry, dank rot here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("stone", "The stone here is of a dark, dark almost black color that is very dull in luster and reflects little light.\n");
   add_item("block", "These are large, dark blocks of stone approximately one by two feet in dimension.  They all appear to be nearly identical so you figure they must have been worked on by a master stoneworker.\n");
   add_item("blocks", "These are large, dark blocks of stone approximately one by two feet in dimension.  They all appear to be nearly identical so you figure they must have been worked on by a master stoneworker.\n");
   ob1 = clone_object("d/Rhovanion/mute/dungeon1/corpse.c");
   ob1->move(this_object());
   for (i = 0; i < 10; i++)
   ob2 = clone_object("d/Rhovanion/mute/dungeon1/rat.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/int1", "east");
   add_exit("/d/Rhovanion/mute/dungeon1/tun4","west");
}
