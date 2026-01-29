/*
 * Originally by Zima, 1998?
 *
 * Tidied the code
 * Patched count of available vines
 * Tapakah, 07/2021
 */

#include "/d/Khalakhor/sys/defs.h"
#include "plains.h"

inherit PLAINS + "hsuckle_room";

void
create_khalakhor_room ()
{
  create_plain();
  create_honeysuckle_room();

  add_exit(PLAINS + "plains_28_8", "north");
  add_exit(PLAINS + "plains_29_8", "northeast");
  add_exit(PLAINS + "plains_29_9", "east");
}
