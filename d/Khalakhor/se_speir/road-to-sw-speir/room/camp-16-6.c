/*
 * Camp room on the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "../defs.h"

inherit BASE_CAMP;
string banner_file = OBJS_DIR + "banner";
object banner;

string
setup_long ()
{
  string my_desc = ::setup_long();
  my_desc += "You are inside the camp. The tent here is larger than most "+
    "of the other ones, and there is a campfire with something roasting "+
    "on it.\n";
  add_item(({"fire", "campfire", "roast"}),
           "A body of a large ungulate is being roasted on the fire.\n");
  add_cmd_item(({"fire", "campfire", "roast"}), "stoke",
               "You feel awkward messing with the campfire, "+
               "as you are not of the camp.\n");

  return my_desc;
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("camp-16-5", "north");
  add_exit("camp-17-7", "southeast");
  add_exit("camp-15-6", "west");
  add_exit("camp-17-6", "east");
}
