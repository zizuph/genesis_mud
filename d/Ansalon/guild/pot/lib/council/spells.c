/* Stralle @ Genesis 010409
 *
 * Spell restrictions
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include "../../guild.h"
#include "../../admin/admin.h"

mapping
query_spells_commands()
{
    return ([ "revoke" : "restrict_spells",
              "invoke" : "unrestrict_spells" ]);
}

int
restrict_spells(string arg)
{
    string whom;

    if ((!is_in_temple()) && (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(), " [spells] [for] %w",
        whom))
    {
        notify_fail("Revoke spells for whom?\n");
        return 0;
    }

    whom = lower_case(whom);
    
    if (GUILD_ADMIN->add_priest_punishment(whom, P_SPELLS_RESTRICTED) == -1)
    {
        write("There is no such priest.\n");
        return 1;
    }
    
    GUILD_ADMIN->log(this_player(), "council", "Revokes spells for " +
        capitalize(whom));

    write("You revoke spells for " + capitalize(whom) + ".\n");
    return 1;
}

int
unrestrict_spells(string arg)
{
    string whom;

    if ((!is_in_temple()) && (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(), " [spells] [for] %w",
        whom))
    {
        notify_fail("Invoke spells for whom?\n");
        return 0;
    }

    whom = lower_case(whom);
    
    if (GUILD_ADMIN->remove_priest_punishment(whom, P_SPELLS_RESTRICTED) == -1)
    {
        write("There is no such priest.\n");
        return 1;
    }
    
    GUILD_ADMIN->log(this_player(), "council", "Invokes spells for " +
        capitalize(whom));

    write("You invoke spells for " + capitalize(whom) + ".\n");
    return 1;
}
