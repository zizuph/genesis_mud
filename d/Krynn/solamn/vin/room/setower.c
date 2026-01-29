/* Modified by Teth Dec 7 1996 for new VK */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>

inherit TOWER;

public void
create_tower()
{
    object door;

    set_short("Inside the southeast tower");
    set_long("You are standing inside the southeast tower. A door leads out "+
      "to the streets, and a spiral stairway also leads up to the "+
      "battlements above.\n");

    AE(VROOM + "setowerup", "up", "@@up");

    door = clone_object(VOBJ + "sedoorb");
    door->move(TO);
    door->set_key(KEEPKEY);
    reset_vin_room();
}
