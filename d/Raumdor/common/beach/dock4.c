/* Ported to the new ship system by Tapakah, 05/2009 */
#include "defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit DOCK_ROOM;
inherit LIBPIER;

#define SIGN "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
object sign;

void
create_room()
{
    ::create_room();
    set_long(
      "You are on a stretch of dreary docks that extend from the shore to " +
      "the east and ends here. Beyond the rocky coast, a large forest " +
      "consumes the land. A sign has been affixed to one of the pilings.\n");
    add_exit(BEACH_DIR + "dock3", "east");

    sign = clone_object(SIGN);
    sign->move(TO);
    reset_room();

    add_pier_entry(MASTER_OB(TO), "Raumdor", "Pan-Donut Circle");
    initialize_pier();
}

object
query_sign()
{
    return sign;
}
