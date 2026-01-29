/* Stralle @ Genesis 010409
 *
 * Travel restrictions
 */

#pragma strict_types

inherit "/d/Ansalon/guild/new_pot/lib/council/std_council";

#include "../../guild.h"
#include "../../admin/admin.h"

mapping
query_travel_commands()
{
    return ([ "issue" : "restrict_travel",
              "unissue" : "unrestrict_travel" ]);
}

int
restrict_travel(string arg)
{
    string whom;

    if ((!is_in_temple()) && (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(),
        " [travel] [restrictions] [for] %w", whom))
    {
        notify_fail("Issue travel restrictions for whom?\n");
        return 0;
    }

    whom = lower_case(whom);
    
    if (GUILD_ADMIN->add_priest_punishment(whom, P_TRAVEL_RESTRICTED) == -1)
    {
        write("There is no such priest.\n");
        return 1;
    }
    
    GUILD_ADMIN->log(this_player(), "council", "Issues travel restrictions " +
        "for " + capitalize(whom));

    write("You issue travel restrictions for " + capitalize(whom) + ".\n");
    return 1;
}

int
unrestrict_travel(string arg)
{
    string whom;

    if ((!is_in_temple()) && (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(),
        " [travel] [restrictions] [for] %w", whom))
    {
        notify_fail("Unissue travel restrictions for whom?\n");
        return 0;
    }

    whom = lower_case(whom);
    
    if (GUILD_ADMIN->remove_priest_punishment(whom, P_TRAVEL_RESTRICTED) == -1)
    {
        write("There is no such priest.\n");
        return 1;
    }
    
    GUILD_ADMIN->log(this_player(), "council", "Unissues travel " +
        "restrictions for " + capitalize(whom));

    write("You unissue travel restrictions for " + capitalize(whom) + ".\n");
    return 1;
}
