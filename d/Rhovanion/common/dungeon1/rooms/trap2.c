inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#include <ss_types.h>
void
create_room() {
   int i;
   set_short("sorry, no short\n");
   set_long("You fall...\n" +
      "You are at the bottom of a twenty foot deep " +
      "hastily constructed shaft of broken, stone blocks.  The " +
      "walls are made of large chunks of stone blocks that must " +
      "have been too damaged to use in the passageways above. " +
      "Judging by the looks of what's down here, I'd start " +
      "looking for a way out...  and fast!\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}), "The large, broken, stone " +
      "blocks comprising the walls and floor of this wretched " +
      "pit are covered in goopish, black-green slime and mortared " +
      "together by only the black, muddy soil found in these " +
      "places.\n");
   add_item("slime","This slimy mess covers the stone walls here " +
      "and appears to be some sort of mold or moss plant.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_item("soil","Feeling a bit of the soil between your " +
      "fingers, you find it might help you climb out of here " +
      "due to its odd gripping property if you climbed it " +
      "instead of the stone.\n");
   add_item(({"wall","walls"}),"The walls are made of " +
      "broken stone blocks mortared with soil.\n");
   clone_object("/d/Rhovanion/common/dungeon1/living/ratskel2.c")
   ->move(TO);
   for (i = 0; i < 4; i++)
   clone_object("/d/Rhovanion/common/dungeon1/living/ratskel.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/living/ratskel2.c")
   ->move(TO);
}
void
init() {
   ::init();
   add_action("try_climb","climb");
}
int
try_climb(string str) {
   notify_fail("Climb where?\n");
   if (!str)
      return 0;
   if (str != "soil")
      return 0;
   if (this_player()->query_skill(SS_CLIMB) <= 20)
      {
      write("You try to climb out using the soil for a grip, but, " +
         "due to your foolish inexperience, fall back down to your " +
         "doom.\n");
      say(QCTNAME(this_player()) + " frantically claws at the " +
         "walls in vain trying to climb out only to slide back " +
         "down...\n");
      return 1;
   }
   this_player()->move_living("climbing out the shaft",
      "/d/Rhovanion/common/dungeon1/rooms/room4.c", 1);
   return 1;
}
