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
  string desc = ::setup_long();

  desc += "From the western side the path seems to bend to the south, as "+
    "both the mountains and the rocky shore are getting closer, and "+
    "the path more narrow. You notice that the mountains here are also "+
    "barely a wall, just a few yards high.\n";
  add_item("wall", "You figure out that the time and the weather may "+
           "make it climbable soon, but not yet.\n");
  return desc;
}

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("path-14-5", "east");
  add_fail("southwest", "A part of the mountain wall collapsed and is "+
           "blocking the passage.\n");
  //  add_exit(COMMON_EXIT, "southwest");
}
