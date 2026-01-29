inherit "/std/room";

#include "troll_reset.h"

object clock;
string body();

create_room()
{
   set_short("The Great Eastroad");
   set_long("@@my_long");

   add_item(({ "duck" }), break_string("You see a mother duck swimming in "
            + "the water with her babies trailing behind.  AWWW, aren't "
            + "they cute!\n", 70));

   add_item(({ "river" }), break_string("You can see fish swimming a couple "
            + "of meters below the surface of the slowly moving water, but "
            + "you can't spot the bottom.  It must be very deep.\n", 70));

   add_item(({ "island", "sandbar" }), break_string(
              "About all you can see is that the island seems covered with "
            + "trees, except for the very edge, which appears to be a sandy "
            + "beach.\n", 70));

   add_exit(STAND_DIR + "gh7", "east");
   add_exit(STAND_DIR + "gh9", "west");

   reset_room();
}


string my_long()
{
    string str;

    str = "You are on the west end of a long bridge over an enormous river "
        + "that crosses the Great Eastroad.  Far to the west you see Grey "
        + "Havens.  You guess that this river must be at least half a "
        + "kilometer wide.  It appears to be flowing very slowly to the "
        + "south.  Far to the south, the bright @@body@@light "
        + "reflects off the river into your eyes, but you can vaguely "
        + "make out a small island in the middle of the river.  To the "
        + "north you see a pure white duck swimming in the water.\n";


    return (break_string(str, 70));
}


string body()
{
  int hour;

  hour = clock->query_hour();
  if (hour < 6 || hour >= 20) 
    return "moon";
  else
    return "sun";
}
