/* Stralle @ Genesis 010409
 *
 * Inquisitor
 *
 * Punishments in the torture chamber and interrogations.
 *
 * Well, the members could make an idea report about it. :)
 */

#pragma strict_types

inherit "/d/Ansalon/guild/new_pot/lib/council/std_council";

mapping
query_inquisitor_commands()
{
    return ([ "punish" : "inquisitor_punish" ]);
}

int
inquisitor_punish(string arg)
{
    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    return 0;
}
