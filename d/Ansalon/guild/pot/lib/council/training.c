/* Stralle @ Genesis 010409
 *
 * Training
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include "../../guild.h"
#include "../../admin/admin.h"

mapping
query_training_commands()
{
    return ([ "restrict" : "restrict_training",
              "unrestrict" : "unrestrict_training" ]);
}

int
restrict_training(string arg)
{
    string whom;

    if ((!is_in_temple()) && (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(), " [training] [for] %w",
        whom))
    {
        notify_fail("Restrict training for whom?\n");
        return 0;
    }

    whom = lower_case(whom);
    
    if (GUILD_ADMIN->add_priest_punishment(whom, P_TRAINING_RESTRICTED) == -1)
    {
        write("There is no such priest.\n");
        return 1;
    }
    
    GUILD_ADMIN->log(this_player(), "council", "Restricts training for " +
        capitalize(whom));

    write("You restrict training for " + capitalize(whom) + ".\n");
    return 1;
}

int
unrestrict_training(string arg)
{
    string whom;

    if ((!is_in_temple()) && (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(), " [training] [for] %w",
        whom))
    {
        notify_fail("Unrestrict training for whom?\n");
        return 0;
    }

    whom = lower_case(whom);
    
    if (GUILD_ADMIN->remove_priest_punishment(whom, P_TRAINING_RESTRICTED) == -1)
    {
        write("There is no such priest.\n");
        return 1;
    }
    
    GUILD_ADMIN->log(this_player(), "council", "Unrestricts training for " +
        capitalize(whom));

    write("You unrestrict training for " + capitalize(whom) + ".\n");
    return 1;
}
