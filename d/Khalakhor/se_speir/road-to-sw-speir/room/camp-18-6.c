/*
 * Camp room on the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "../defs.h"

inherit BASE_CAMP;

string
setup_long ()
{
  string my_desc = ::setup_long();
  my_desc += "This part of the camp is tucked in the shore between the "+
    "rocks and makes a good observation point for all things coming from "+
    "the east. You notice some kind of path past the rocks to the north.\n";
  add_item("path", "A path goes north of here, but it's not really "+
           "accessible from where you are.\n");
  return my_desc;
}
void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("camp-17-5", "northwest");
  add_exit("camp-17-6", "west");
}
