/*
 * Path to SW Speir - beginning
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "../defs.h"

inherit BASE_PATH;

string
setup_long ()
{
  string my_desc = ::setup_long();
  my_desc += "The path ends here to the east, merging with the vast "+
    "plains that surround the village of Port Macdunn.\n";
  add_item("plains",
           "They are wide and calm, and seem to be thriving with "+
           "both animal and plant life.\n");
  
  return my_desc;
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit(PLAINS_EXIT, "east");
  add_exit("path-21-5", "west");
}
