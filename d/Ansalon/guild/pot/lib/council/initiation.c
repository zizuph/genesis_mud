/* Stralle @ Genesis 010409
 *
 * Initiation
 *
 * Let new a member into the guild as Initiate.
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include "../../guild.h"

mapping
query_initiation_commands()
{
    return ([ "initiate" : "do_initiate" ]);
}

int
do_initiate(string arg)
{
    object pl;
    string reason;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

#ifdef CLOSED_FOR_NEW_MEMBERS
    write("Unfortunately the guild is closed for new members. No " +
        "initation will commence.\n");
    return 1;
#endif
    if (!present("terwed", environment(this_player())))
    {
        notify_fail("You would require Terwed's assistance.\n");
        return 0;
    }

    if (environment(this_player())->query_initiating_in_progress())
    {
        notify_fail("There is already an initation in progress.\n");
        return 0;
    }

    if (!arg || !(pl = present(arg, environment(this_player()))))
    {
        notify_fail("Initiate whom?\n");
        return 0;
    }
    
    if (!this_player()->query_met(pl->query_real_name()))
    {
        notify_fail("Whyever would you want to initiate someone " +
            "you do not know?\n");
        return 0;
    }
    
    if (!interactive(pl))
    {
        notify_fail(pl->query_name() + " cannot be initiated.\n");
        return 0;
    }
    
    if (stringp(reason = (GUILD_ADMIN)->query_may_join(pl)))
    {
        notify_fail(pl->query_name() + " cannot be initated because " +
            pl->query_pronoun() + " is " + reason + ".\n");
        return 0;
    }
    
    environment(this_player())->prepare_initiation(pl, this_player());

    GUILD_ADMIN->log(this_player(), "council", "Begins initiating " +
        pl->query_name());
    
    return 1;
}
