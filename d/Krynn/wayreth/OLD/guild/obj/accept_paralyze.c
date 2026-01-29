/*
 * This paralyze is used when a player is getting accepted.
 */
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit "/std/paralyze";

public void
create_paralyze()
{
    set_fail_message("You are so baffeled about what is going on, " +
		     "so you are not able to do that.\n");
    add_name(ACCEPT_PARALYZE_NAME);
}
