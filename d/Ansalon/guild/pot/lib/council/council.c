/* Stralle @ Genesis 010702
 *
 * Council
 *
 * Adds/Remove people from the Council
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include "../../guild.h"

#define POT_LEADER_WHEN_CONFIRMED    "_pot_leader_when_confirmed"

mapping
query_council_commands()
{
    return ([ "add" : "add_council_member",
              "remove" : "remove_council_member",
              "list" : "list_council_members" ]);
}

int
add_council_member(string arg)
{
    string who, position;
    object pl;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(),
        " %s 'as' %s", who, position))
    {
        notify_fail("Add whom as council member under what position?\n");
        return 0;
    }

    who = lower_case(who);
    
    if (position == "leader" && GUILD_ADMIN->query_council_seat("leader") ==
        this_player()->query_real_name())
    {
        if (this_player()->query_prop(POT_LEADER_WHEN_CONFIRMED) < time())
        {
            write("If you are certain you wish to appoint " +
                capitalize(who) + " as leader while at the same time step " +
                "down as leader, do what you just did again within a " +
                "short period of time.\n");
            this_player()->add_prop(POT_LEADER_WHEN_CONFIRMED, time() + 20);
            return 1;
        }

        GUILD_ADMIN->remove_council_member(this_player()->query_real_name(),
            "leader");
        GUILD_ADMIN->log(this_player(), "council",
            capitalize(this_player()->query_real_name()) + " stepped " +
            "down as leader.");
        write("You step down as leader.\n");
    }

    switch (GUILD_ADMIN->add_council_member(who, position))
    {
        case -1:
            notify_fail(capitalize(who) + " is not a member.\n");
            return 0;
        case 0:
            notify_fail(capitalize(who) + " is already on the council.\n");
            return 0;
        case -2:
            notify_fail(capitalize(who) + " is not of the sufficiant " +
                "standing quite yet.\n");
            return 0;
        case -3:
            notify_fail("There is no such position as " + position + ".\n");
            return 0;
        case -4:
            notify_fail("That position is already taken.\n");
            return 0;
        case 1:
            GUILD_ADMIN->log(this_player(), "council",
                capitalize(who) + " was put on the council as " +
                position + " by " + capitalize(this_player()->query_real_name()));
            write("You add " + capitalize(who) + " to the council as " +
                position + ".\n");
            return 1;
    }
}

int
remove_council_member(string arg)
{
    string whom, seat;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;
        
    if (!arg || !parse_command(arg, this_player(),
        " %s 'from' %s", whom, seat))
    {
        notify_fail("Remove whom from what councilseat?\n");
        return 0;
    }

    whom = lower_case(whom);

    if (seat == "leader")
    {
        notify_fail("Add another as leader if you wish to step down.\n");
        return 0;
    }
    
    switch (GUILD_ADMIN->remove_council_member(whom, seat))
    {
        case -1:
            notify_fail(capitalize(whom) + " is no council member.\n");
            return 0;
        case -2:
            notify_fail(capitalize(seat) + " is no seat of the council.\n");
            return 0;
        case -3:
            notify_fail(capitalize(seat) + " cannot be removed.\n");
            return 0;
        case 1:
            GUILD_ADMIN->log(this_player(), "council", capitalize(whom) +
                " was removed from the council by " +
                capitalize(this_player()->query_real_name()));
            write("You removed " + capitalize(whom) + " from the " +
                "council.\n");
            return 1;
    }
}

int
list_council_members(string arg)
{
    string *arr = map(GUILD_ADMIN->query_guild_council(), capitalize),
        *pos = COUNCIL_TITLES, str;
    int x;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || arg != "council members")
    {
        notify_fail("List what? Council members?\n");
        return 0;
    }
    
    for (x = 0, str = "" ; x < 5 ; x++)
    {
        str += sprintf("%-11s : %-13s\n", capitalize(pos[x]),
            (stringp(arr[x]) ? arr[x] : "None"));
    }
    
    write(str);
    return 1;
}
