#include "stdroom.h"

create_room()
{
  set_short("On a path in the northern Misty Mountains");
  set_long("@@get_long");

  add_item(({"cave", "opening"}), break_string("Here in the rocky side "
    + "of the mountain is the opening to a small cavern.  A damp gust of "
    + "wind from the cave brings a smell of damp earth and stale air to "
    + "your sensitive nose.  From what you can see, the cave looks small "
    + "and relatively safe.\n", 70));

  add_prop(ROOM_I_LIGHT, 1);

  add_exit(RPATH + "entry", "east");

}

string get_long()
{
  string RetS;
  string TimeS;

  TimeS = find_object("/d/Gondor/elessar/lib/clock")->query_time_of_day();

  RetS = "On a path in the northern Misty Mountains.  ";

  switch (TimeS)
  {
  case "early morning":
    RetS += "The sky is lightening.  It should be dawn soon.  ";
    break;

  case "morning":
    RetS += "The sun is peaking above the mountain tops.  ";
    break;

  case "noon":
    RetS += "The sun is high overhead.  ";
    break;

  case "afternoon":
    RetS += "The sky begins to darken as the sun dips behind the mountain "
      + "tops.  ";
    break;

  case "evening":
    RetS += "It is growing very dark.  It will be night soon.  ";
    break;

  case "night":
    RetS += "It is night time.  You must strain to see.  ";
    break;

  default:
    break;
  }

  RetS += "You can see a valley below you.  The path continues northeast "
    + "and southwest.  There is the opening of a dark and forbidding cave "
    + "just east of where you stand.\n";

  return break_string(RetS, 70);
}
