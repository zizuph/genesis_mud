#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include "../../defs.h"
#include "../local.h"
#include "door.h"
inherit "/std/door";

public void 
create_door()
{
 
    set_door_id(DOOR_W1_ALLEY);
    set_pass_command(({"w","west"}));
    set_door_name(({"small wooden door","door"}));
    set_other_room("/d/Genesis/start/human/sparkle/docks/" + "alley1a.c");

    set_open(0); 
}

/*
 * Function name: pass_door
 * Description  : This function is called when a player uses any of the "pass
 *                commands" for this door.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
pass_door(string str)
{
    if (this_player()->query_stat(SS_DIS) < ALLEY_DIS_REQUIRED)
    {
        write("You are not brave enough to enter the alley.\n");
        return 1;
    }

    return ::pass_door(str);
}
