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
  add_exit("path-21-5", "east");
  add_exit("path-19-5", "west");
}
