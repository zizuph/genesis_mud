inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#include <ss_types.h>
#include <macros.h>
void
create_room() {
   set_short("black hole\n");
   set_long("Here the tunnel forms a `T' splitting off three " +
      "ways through the foot of water filling these passageways. " +
      "You're starting to get annoyed by the occasional " +
      "brushings against your feet by the gods know what horrors, and " +
      "the dank, cold air here seems somehow grossly tainted " +
      "with a festering smell that's starting to get to you as " +
      "well.  This tunnel is in a state of severe dilapidation.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}), "These large, dark blocks of " +
      "stone approximately one by two feet in dimension are covered " +
      "with brackish green and black molds and drip slime from tiny " +
      "cracks throughout the mortar.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_item("ceiling", "The ceiling extends upward at least twenty " +
      "feet where stones jut out from it in an asthetically " +
      "pleasing pattern offering perches perhaps for creatures " +
      "able to cling to walls.\n");
   add_item("water","The water is murky, green, and littered with " +
      "pieces of trash you can only guess as to where they came from " +
      "or what they're made of which float on top of the water along " +
      "with a filmy layer of slime.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/int5","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/room3","north");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun11","east");
   clone_object("/d/Rhovanion/common/dungeon1/living/watersnake.c")
   ->move(TO);
}
void
init() {
   ::init();
   add_action("part_snake","swim");
}
int
part_snake(string str) {
   notify_fail("Swim where?\n");
   if (!str)
      return 0;
   if (str != "underwater")
      return 0;
   if (this_player()->query_skill(SS_SWIM) <= 21)
      {
      write("You splash down into the water only to discover " +
         "your inadequacies at swimming and instead get only a " +
         "mouthful of water.\n");
      say(QCTNAME(this_player()) + " splashes down into the " +
         "water with a feeble dive and comes up with a mouthful " +
         "of sludge.\n");
      return 1;
   }
   write ("You dive underwater...\n");
   this_player()->move_living("diving under the water",
      "/d/Rhovanion/common/dungeon1/rooms/int4a",1);
   return 1;
}
