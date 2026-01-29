/*
 * Path to SW Speir - beginning
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "../defs.h"

inherit BASE_PATH;

void
create_khalakhor_room ()
{
  ::create_khalakhor_room();
  add_exit("path-15-5", "east");
  add_exit("path-13-5", "west");
}
