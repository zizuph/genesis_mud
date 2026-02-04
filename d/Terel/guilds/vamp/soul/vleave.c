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

    if (!TP->query_prop("_live_i_vamp_leave_guild")) {
        TP->catch_tell("If you truly wish to leave the vampire guild, "+
            "type the command again.\n");
        TP->add_prop("_live_i_vamp_leave_guild", 1);
        return 1;
    }

    setuid();
    seteuid(getuid());
    TP->remove_vampire();

    return 1;
}

int vrelease(string str)
{
  
    notify_fail("Release who from their bonds?\n");
    if (!strlen(str))
    {
        return 0;
    }

    object bg;

    if (!parse_command(str,environment(TP),
	"%o 'from' 'his' / 'her' 'bonds'",bg))
    {
        return 0;
    }
    
    if (!IS_BG(bg))
    {
        TP->catch_msg(QCTNAME(bg) + " is not a bloodguard.\n");
        return 1;
    }

    if (!bg->query_prop("_live_i_bg_leave_guild")) {
        TP->catch_msg("If you truly wish to release "+ QTNAME(bg) +
            ", type the command again.\n");
        bg->add_prop("_live_i_bg_leave_guild", 1);
        return 1;
    }

    setuid();
    seteuid(getuid());
    bg->remove_bloodguard(0);
    TP->catch_msg("You release "+QTNAME(bg)+" from "+bg->query_possessive()+
       " bloodguard bonds.\n");

    return 1;
}
