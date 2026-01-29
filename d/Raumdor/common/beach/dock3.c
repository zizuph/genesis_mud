/* Ported to the new ship system by Tapakah, 05/2009 */
#include "defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit DOCK_ROOM;
inherit LIBPIER;

void
create_room()
{
    ::create_room();

    set_long(
      "You are on a stretch of dreary docks that extend from the shore to " +
      "the east and end just to the west. Beyond the rocky coast, a large " +
      "forest consumes the land. A sign has been affixed to one of the " +
      "pilings.\n");

    add_exit(BEACH_DIR + "dock2", "east");
    add_exit(BEACH_DIR + "dock4", "west");

    add_pier_entry(MASTER_OB(TO), "Raumdor", "Pier to Sparkle");

    initialize_pier();
}
