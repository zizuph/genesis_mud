#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/solamn/vin/knight/guild.h"
#include <std.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <config.h>
#include <filter_funs.h>

inherit IN_BASE;

void
reset_vin_room()
{
}

public void
create_vin_room()
{
    set_short("Idle room, you shouldn't see this");
    set_long("Room to keep horses that are sent home.\n");

    add_prop("_room_i_allow_steed", 1);
    add_prop("_room_i_allow_horse", 1);
}
