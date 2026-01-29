/* modifed by Teth for new VK Dec 96 */

#include <ss_types.h>
#include <macros.h>
#include "../../local.h"

inherit TOWER;

public void
create_tower()
{
    object door;

    set_short("Inside the northeast tower");
    set_long("You are standing inside the northeast tower. A doorway leads out to "+
      "the streets of Vingaard, and a ladder leads upwards to the battlements "+
      "above.\n");

    AE(VROOM + "netowerup", "up", "@@up");

    door = clone_object(VOBJ + "nedoorb");
    door->move(TO);
    door->set_key(KEEPKEY);
    reset_vin_room();
}
