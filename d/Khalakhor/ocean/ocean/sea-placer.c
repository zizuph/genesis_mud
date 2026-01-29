/*
 * Khalakhor ocean placer
 * Uses Krynn placer
 * Tapakah, 11/2021
 */

#pragma no_clone

inherit "/d/Krynn/std/placer";

#include "defs.h"

void
create_placer()
{
    set_area_name("Khalakhor-Ocean");
    set_base_path(KHALAKHOR_SEA);
    set_unit_path(LIVING);
    set_area_path(ROOM);
}
