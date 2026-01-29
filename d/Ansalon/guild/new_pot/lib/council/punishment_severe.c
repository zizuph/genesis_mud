/* Stralle @ Genesis 010409
 *
 * Punishment severe
 */

#pragma strict_types

inherit "/d/Ansalon/guild/new_pot/lib/council/std_council";

mapping
query_punishment_severe_commands()
{
    return ([ "punish" : "do_punish" ]);
}

int
do_punish(string arg)
{
    if ((!is_in_temple()) && (!is_our_command() && !is_delegated_command()))
        return 0;
}
