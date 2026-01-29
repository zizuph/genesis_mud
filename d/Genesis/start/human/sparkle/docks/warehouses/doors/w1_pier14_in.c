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
 
    set_door_id(DOOR_W1_PIER14);
    set_pass_command(({"s","south"}));
    set_door_name(({"sturdy wooden door","door"}));
    set_other_room("/d/Genesis/start/human/sparkle/docks/" + "ware1_1b.c");
 
    set_open(0);
}