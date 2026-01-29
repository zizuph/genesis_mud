inherit "/std/room";

#include "troll_reset.h"

object clock;
string body();

void create_room() {

    string str;

    str = "@@my_long";
   clock = find_object("/d/Gondor/elessar/lib/clock");
   set_short("A Bridge on the Great Eastroad");
   set_long("@@break_string(str, 70)");

   add_item(({ "bass", "fish" }), break_string("You can't see the bass anymore, since "
	    + "it has already fallen back into the water.  But you can "
            + "see several other fish swimming in the clear water under "
            + "the bridge.\n", 70));

   add_item(({ "river" }), break_string("You can see fish swimming a couple of meters "
            + "below the surface of the slowly moving water, but you can't "
            + "spot the bottom.  It must be very deep.\n", 70));

   add_item(({ "island", "sandbar" }), break_string(
              "About all you can see is that the island seems covered with "
            + "trees, except for the very edge, which appears to be a sandy "
            + "beach.\n", 70));

   add_exit(STAND_DIR + "gh6", "east", 0);
   add_exit(STAND_DIR + "gh8", "west", 0);

   reset_room();
}
string my_long()
{
    return (
        "You are on the east end of a long bridge over an enormous river "
      + "that crosses the Great Eastroad.  You guess that this river must be "
      + "at least half a kilometer wide.  It appears to be flowing very "
      + "slowly to the south.  Far to the south, the bright @@body@@light"
      + "reflects off the river into your eyes, but you can vaguely "
      + "make out a small island in the middle of the river.  Just "
      + "north of the bridge, you see a large bass jump from the water.\n");
}


string body() {
  int hour;

  hour = clock->query_hour();
  if (hour < 6 || hour >= 20) 
    return "moon";
  else
    return "sun";
}
