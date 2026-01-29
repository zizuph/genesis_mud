/* vleave.c created by Louie@Genesis
 * This file contains the code for the "vleave" command
 * This file is part of the vampire guild soul
 */

/* Description
 * -----------
 * This command allows a vampire to leave the guild.
 */

#include "../guild.h"
#include <macros.h>
#include <std.h>

int vleave(string str)
{
  
    if (!strlen(str))
    {
        notify_fail("Leave the vampire guild?\n");
        return 0;
    }

    if (str != "the vampire guild" &&
        str != "the Vampire guild")
    {
        notify_fail("Leave the vampire guild?\n");
        return 0;
    }

    if (!this_player()->query_prop("_live_i_vamp_leave_guild")) {
        this_player()->catch_tell("If you truly wish to leave the vampire guild, "+
            "type the command again.\n");
        this_player()->add_prop("_live_i_vamp_leave_guild", 1);
        return 1;
    }

    setuid();
    seteuid(getuid());
    this_player()->kick_out_vamp();

    return 1;
}
