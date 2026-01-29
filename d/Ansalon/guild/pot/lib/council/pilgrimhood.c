/* Stralle @ Genesis 010409
 *
 * Pilgrimhood
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include <files.h>
#include <language.h>
#include <composite.h>
#include "../../guild.h"

mapping
query_pilgrimhood_commands()
{
    return ([ "add" : "add_pilgrim",
              "remove" : "remove_pilgrim",
              "extend" : "extend_pilgrimage",
              "list" : "list_pilgrims" ]);
}

int
add_pilgrim(string arg)
{
    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || sscanf(arg, "%s as pilgrim", arg) != 1)
    {
        notify_fail("Add whom as pilgrim?\n");
        return 0;
    }

    arg = lower_case(arg);
    
    if (!SECURITY->exist_player(arg))
    {
        notify_fail("You have never heard of anyone named \"" +
            capitalize(arg) + "\".\n");
        return 0;
    }
    
    GUILD_ADMIN->add_pilgrim(arg);
    GUILD_ADMIN->log(this_player(), "council", "Added " + capitalize(arg) +
        " as pilgrim");

    write("You make " + capitalize(arg) + " known as Pilgrim.\n");
    return 1;
}

int
remove_pilgrim(string arg)
{
    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || sscanf(arg, "%s from pilgrimage", arg) != 1)
    {
        notify_fail("Remove whom from pilgrimage?\n");
        return 0;
    }
    
    arg = lower_case(arg);

    /* If successful, will remove the player */
    if (!GUILD_ADMIN->remove_pilgrim(arg))
    {
        notify_fail("There is no such pilgrim.\n");
        return 0;
    }

    GUILD_ADMIN->log(this_player(), "council", "Removed " + capitalize(arg) +
        " as pilgrim");
    
    write("You remove " + capitalize(arg) + " from pilgrimage.\n");
    return 1;
}

int
extend_pilgrimage(string arg)
{
    int days;
    string who;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || !parse_command(arg, this_player(),
        " [pilgrimage] [another] %d [days] [for] %s", days, who))
    {
        notify_fail("Extend the pilgrimage another how many days for what " +
            "pilgrim?\n");
        return 0;
    }
    
    if (days <= 0)
    {
        notify_fail("Extending implies a positive number of days.\n");
        return 0;
    }

    who = lower_case(who);
    
    /* If successful, will extend the pilgrimage */
    if (!GUILD_ADMIN->extend_pilgrimage(who, time() + days * 86400))
    {
        notify_fail("There is no such pilgrim.\n");
        return 0;
    }

    GUILD_ADMIN->log(this_player(), "council", "Extended pilgrimage for " +
        capitalize(who) + " by " + days + " days");
    
    write("You extend the pilgrimage for " + capitalize(who) + " for " +
        "another " + LANG_WNUM(days) + " days.\n");
    return 1;
}

int
list_pilgrims(string arg)
{
    string *arr;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (arg != "pilgrims")
    {
        notify_fail("List what? Pilgrims?\n");
        return 0;
    }
    
    arr = map(GUILD_ADMIN->query_pilgrims(), capitalize);
    write("The following people are also known as pilgrims; " +
        COMPOSITE_WORDS(arr) + ".\n");
    return 1;
}
