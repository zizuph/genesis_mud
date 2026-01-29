/* modified by Teth Dec 7 1996 for new VK */

#include "../../local.h"
#include <ss_types.h>
#include <macros.h>

inherit TOWER;

public void
create_tower()
{
    object door;

    set_short("Inside the southwest tower");
    set_long("You are standing inside the southwest tower. There is a "+
             "door leading out, as well as a ladder leading up to the "+
             "battlement above.\n");

    AE(VROOM + "swtowerup", "up", "@@up");

    door = clone_object(VOBJ + "swdoorb");
    door->move(TO);
    door->set_key(KEEPKEY);
    reset_vin_room();
}
