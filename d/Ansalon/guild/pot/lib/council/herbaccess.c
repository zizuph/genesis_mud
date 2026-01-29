/* Stralle @ Genesis 010409
 *
 * Herbaccess
 *
 * Restricts the access to the herbshop for certain members that
 * they cannot buy herbs. Also a command for allowing non-members
 * to gain access to the shop to buy and/or sell.
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include <composite.h>
#include <files.h>
#include "../../guild.h"

mapping
query_herbaccess_commands()
{
    return ([ "restrict" : "restrict_herbaccess",
              "list" : "list_herbaccess" ]);
}

int
restrict_herbaccess(string arg)
{
    string *arr = ({ }), access, who;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(),
        "[herbaccess] [by] [toggling] %s 'for' %s", access, who))
    {
        notify_fail("Restrict herbaccess by toggling buy, sell and/or " +
            "list privilegies for whom?\n");
        return 0;
    }

    who = lower_case(who);

    if (!SECURITY->exist_player(who))
    {
        notify_fail("You have never heard of anyone known as " +
            capitalize(who) + ".\n");
        return 0;
    }

    if (wildmatch("*buy*", access))
        arr += ({ "buying" });
    if (wildmatch("*sell*", access))
        arr += ({ "selling" });
    if (wildmatch("*list*", access))
        arr += ({ "listing" });
    if (wildmatch("*identify*", access))
        arr += ({ "identifying" });

    arr = GUILD_ADMIN->set_herbaccess(who, arr);
    GUILD_ADMIN->log(this_player(), "council", "Sets herbaccess for " +
        capitalize(who) + " to " + (pointerp(arr) && sizeof(arr) ?
        COMPOSITE_WORDS(arr) : "none"));
        
    write("You set the restrictions of " + capitalize(who) +
        " to that of " + (pointerp(arr) && sizeof(arr) ?
        COMPOSITE_WORDS(arr) : "no restrictions at all") + ".\n");
    
    return 1;
}

int
list_herbaccess(string arg)
{
    mixed *arr;
    int x, size;
    string str = "";

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || arg != "herbaccess")
    {
        notify_fail("List what? Herbaccess?\n");
        return 0;
    }
    
    arr = GUILD_ADMIN->query_herbaccess_list();

    if (!sizeof(arr))
    {
        write("No one has had restrictions given at the herbshop.\n");
        return 1;
    }

    for (x = 0, size = sizeof(arr) ; x < size ; x += 2)
    {
        str += sprintf("%-13s : %-s\n", capitalize(arr[x]),
            COMPOSITE_WORDS(arr[x + 1]));
    }
    
    this_player()->more(str);
    return 1;
}
