#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "../../defs.h"
#include "../local.h"
#include "door.h"
inherit "/std/door";

public void 
create_door()
{
 
    set_door_id(DOOR_W1_PIER15);
    set_pass_command(({"e","east"}));
    set_door_name(({"sturdy wooden door","door"}));
    set_other_room("/d/Genesis/start/human/sparkle/docks/" + "pier14-15b.c");
 
    set_open(0);
}