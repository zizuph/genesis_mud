/*
 * Eastern pier of northern village
 * TAPAKAH 04/2005
 */

#pragma strict_types;
#pragma save_binary;

inherit "/d/Khalakhor/std/room";

#include <stdproperties.h>
#include "/d/Khalakhor/sys/defs.h";
#include "/d/Khalakhor/sys/paths.h";
#include "/d/Khalakhor/sys/paths.h";
#include "/d/Khalakhor/sys/properties.h";
#include "/d/Khalakhor/sys/terrains.h";

void
create_khalakhor_room()
{
  ::create_khalakhor_room();

  set_short("Pier in northern Khalakhor speir.\n");
  set_long("");
}
