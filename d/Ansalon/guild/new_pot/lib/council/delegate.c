/* Stralle @ Genesis 010409
 *
 * Delegate
 *
 * Temporarily gives another member of the council most commands
 * that council member has for a temporary period of time. Should
 * contain weeks, other council member's name and the commands.
 * Also this should be in some kind of log.
 */

#pragma strict_types

inherit "/d/Ansalon/guild/new_pot/lib/council/std_council";

#include "../../guild.h"
#include <language.h>

mapping
query_delegate_commands()
{
    return ([ "delegate" : "do_delegate",
              "undelegate" : "do_undelegate" ]);
}

int
do_delegate(string arg)
{
    string whom, what;
    int weeks, i;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(),
        "%s [responsobilities] [to] %w 'for' %d 'weeks'", what, whom, weeks))
    {
        notify_fail("Delegate what responsobilities to whom for how many " +
            "weeks?\n");
        return 0;
    }

    whom = lower_case(whom);
    
    if (member_array(whom, GUILD_ADMIN->query_guild_council()) < 0)
    {
        notify_fail("Preferably he who will take over your " +
            "responsobilities would be on the council.\n");
        return 0;
    }

    if (weeks < 0 || weeks > 8)
    {
        notify_fail("Such responsobilities should not be given out " +
            "for longer than eight weeks.\n");
        return 0;
    }
    
    if (((i = member_array(what, COUNCIL_TITLES)) < 0) ||
        GUILD_ADMIN->query_guild_council()[i] !=
        this_player()->query_real_name())
    {
        notify_fail("You have no such responsobilities to delegate.\n");
        return 0;
    }


    if (GUILD_ADMIN->query_delegated(whom, what))
    {
        write(capitalize(whom) + " already has been given those " +
            "responsobilities for another " +
            LANG_WNUM((time() - GUILD_ADMIN->query_delegated(whom, what)) /
            86400 * 7) + " weeks.\n");
        return 1;
    }

    GUILD_ADMIN->set_delegated(this_player()->query_real_name(),
        whom, what, time() + weeks * 7 * 86400);
    GUILD_ADMIN->log(this_player(), "council", "Delegated " + what +
        " responsobilities to " + capitalize(whom) + " for " +
        LANG_WNUM(weeks) + " weeks");

    write("You delegate your " + what + " responsobilities to " +
        capitalize(whom) + " for " + LANG_WNUM(weeks) + " weeks.\n");
    return 1;
}

int
do_undelegate(string arg)
{
    string whom, what;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(),
        "%w [responsobilities] [for] %w", what, whom))
    {
        notify_fail("Undelegate what responsobilities for whom?\n");
        return 0;
    }

    whom = lower_case(whom);
    
    switch (GUILD_ADMIN->remove_delegated(whom, what))
    {
        case -1:
            notify_fail(capitalize(whom) + " has not been given " +
                "any responsobilities.\n");
            return 0;
        case -2:
            notify_fail(capitalize(whom) + " has not been given " +
                "those responsobilities.\n");
            return 0;
        case 1:
            write("You undelegate the responsobilities given to " +
                capitalize(whom) + " as " + what + ".\n");

            GUILD_ADMIN->log(this_player(), "council", "Undelegates " +
                "responsobilities as " + what + " from " + capitalize(whom));
            return 1;
    }
}            
