/* Stralle @ Genesis 010409
 *
 * Punishment light
 *
 * Issue letter to the captains of the boats out from Sanction,
 * restricting travel for a priest for a specific time.
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

mapping
query_punishment_light_commands()
{
    return ([ "issue" : "do_issue" ]);
}

int
do_issue(string arg)
{
    if ((!is_in_temple()) && (!is_our_command() && !is_delegated_command()))
        return 0;
}
