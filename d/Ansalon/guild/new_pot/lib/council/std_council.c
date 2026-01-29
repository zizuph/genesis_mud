/* Stralle @ Genesis 010705
 *
 * Functions general for the council
 *
 * Revisions:
 *   Lucius, Sep 2016: Renamed "herbmanager" to "chancellor"
 *
 */
#pragma strict_types

#include "../../guild.h"

mapping gCouncilCommandsDelegated = ([
    "leader" : ({ "promote", "demote", "initiate" }),
    "mentor" : ({ "add", "remove", "extend", "list", "promote", "demote" }),
    "inquisitor" : ({ "promote", "demote" }),
    "librarian" : ({ "assign", "unassign", "list" }),
    "chancellor" : ({ "restrict", "list" }) ]);

/* Function name: is_in_temple
 * Description:   Checks if the player is inside the temple
 * Returns:       int - 1/0, true or false
 */
int
is_in_temple()
{
    return (wildmatch("/d/Ansalon/taman_busuk/neraka/temple*",
        file_name(environment(this_player()))));
}

/* Function name: is_our_command
 * Description:   Sees if this command originated from a council
 *                position that we hold.
 * Returns:       int - 1/0, true or false
 */
int
is_our_command()
{
    string *arr = explode(file_name(this_object()), "/");
    int i, size = sizeof(arr);

    arr[size - 1] = explode(arr[size - 1], "#")[0];

    return (((i = member_array(arr[size - 1],
        COUNCIL_TITLES)) >= 0) &&
        GUILD_ADMIN->query_guild_council()[i] ==
        this_player()->query_real_name());
}

/* Function name: is_delegated_command
 * Description:   If we do not hold the council position the command
 *                originated from, this function is called to see if
 *                can perform it.
 * Returns:       int - 1/0, true or false
 */
int
is_delegated_command()
{
    string *arr = explode(file_name(this_object()), "/");

    return (member_array(query_verb(),
        gCouncilCommandsDelegated[explode(arr[sizeof(arr) - 1], "#")[0]]) >= 0);
}
