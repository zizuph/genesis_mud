inherit "/std/room.c";
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
void
create_room()
{
   set_short("shaft");
   set_long("You have entered a vertical shaft descending down into darkness and\n" +
      "leading up to the tunnel above.  The stones here are dark and\n" +
      "nearly as large as the stones in the passageways above.\n" +
      "Strange noises can be heard from below.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}), "These are large, dark blocks of stone approximately one by two feet in dimension.  They all appear to be nearly identical so you figure they must have been worked on by a master stoneworker.\n" +
      "You are thinking you might be able to use these blocks of stone as handholds when you notice something strange about the cracks between the blocks.\n");
   add_item(({"crack","cracks"}), "There is nothing unusual about these cracks except there are what appear to be webs (or the remnants thereof) stuck in some of the cracks.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun4","up");
}
void
init()
{
   ::init();
   add_action("try_climb","climb");
}
int
try_climb(string str)
{
   notify_fail("Climb where?\n");
   if (!str)
      return 0;
   if (str != "down")
      return 0;
   if (this_player()->query_skill(SS_CLIMB) <= 20)
      {
      write("You try to climb down, but, due to your inexperience, fall...\n");
      say(QCTNAME(this_player()) + " begins climbing down, but can't keep a grip and falls into the dark depths below...\n");
      this_player()->heal_hp(-25);
      this_player()->move_living(" falling down the shaft...     Thud!",
         "/d/Rhovanion/common/dungeon1/rooms/spilair3.c", 1);
      return 1;
   }
   this_player()->move_living("climbing down the shaft",
      "/d/Rhovanion/common/dungeon1/rooms/spilair2.c", 1);
   return 1;
}
