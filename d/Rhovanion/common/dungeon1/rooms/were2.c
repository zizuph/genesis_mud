inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("rats!\n");
   set_long("This small chamber has nearly collapsed!  The ceiling " +
      "dips down in the middle nearly four feet, the slime covered " +
      "walls bend and strain, and cracks run through the old, stone " +
      "blocks of the walls and ceiling.  There's about two feet of " +
      "brackish, slimy water filling this place and the floor beneath " +
      "it feels mushy and disgusting.  Debris of all manner lies strewn " +
      "about everywhere, floating on the water, sticking out... " +
      "everywhere.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("water","The water is murky, green, and littered with " +
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   clone_object("/d/Rhovanion/common/dungeon1/gear/barrel.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/werehelm.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/board.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/goo.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/were1","south");
}
