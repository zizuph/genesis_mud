inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   int i;
   object ob1;
   object ob2;
   set_short("a faoul place\n");
   set_long("This is a turn in this passage of brack, stone " +
      "blocks which is currently under about a foot of water and " +
      "filled with all manner of vermin.  It reaks of " +
      "foul decay and infestation here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("stone", "The stone here is of a dark, dark almost " +
      "black color that is very dull in luster and reflects " +
      "little light.\n");
   add_item("water","The water is murky, green, and littered with " +
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   for (i = 0; i < 3; i++)
   clone_object("/d/Rhovanion/common/dungeon1/living/rat.c")
   ->move(TO);
   for (i = 0; i < 5; i++)
   clone_object("/d/Rhovanion/common/dungeon1/living/rat3.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int6","south");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun24","east");
}
