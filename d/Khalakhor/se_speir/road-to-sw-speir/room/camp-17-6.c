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
    "of the other ones, and there is a couple of makeshift benches here.\n";
  add_item(({"bench", "benches"}), "Crudely but effectively constructed, "+
           "these benches seem to be used for the meetings of the warriors "+
           " of the camp.\n");
  add_cmd_item(({"bench", "benches"}), "sit", "You feel awkward using those "+
               "benches, as you are not of the camp.\n");

  return my_desc;
}

void
reset_room ()
{
  ::reset_room();
  if (! banner || ! present(banner))
    if (file_size(banner_file + ".c") != -1) {
      banner = clone_object(banner_file);
      banner->move(TO);
      banner->configure_banner();
      remove_item("pole");
    }
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("camp-17-5", "north");
  add_exit("camp-17-7", "south");
  add_exit("camp-16-6", "west");
  add_exit("camp-18-6", "east");
}
