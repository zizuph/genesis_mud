/* Stralle @ Genesis 010409
 *
 * Librarian
 *
 * Assign library assistants and remove them.
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include "../../guild.h"
#include <composite.h>

mapping
query_librarian_commands()
{
    return ([ "assign" : "add_assistant",
              "unassign" : "remove_assistant",
              "list" : "list_assistants" ]);
}

int
add_assistant(string arg)
{
    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg)
    {
        notify_fail("Assign whom as library assistant?\n");
        return 0;
    }

    arg = lower_case(arg);
    
    if (member_array(arg, GUILD_ADMIN->query_guild_list()) < 0)
    {
        notify_fail(capitalize(arg) + " is no member of the guild.\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid());

    switch (find_object(GUILD_LIB)->council_assign(arg))
    {
        case 0:
            notify_fail(capitalize(arg) + " is already a library " +
                "assistant.\n");
            return 0;
        case 1:
            write("You appoint " + capitalize(arg) + " as library " +
                "assistant.\n");
            GUILD_ADMIN->log(this_player(), "council", "Appoints " +
                capitalize(arg) + " as library assistant");

            return 1;
    }
}

int
remove_assistant(string arg)
{
    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg)
    {
        notify_fail("Unassign whom as library assistant?\n");
        return 0;
    }

    arg = lower_case(arg);
    
    setuid();
    seteuid(getuid());

    switch (find_object(GUILD_LIB)->council_unassign(arg))
    {
        case 0:
            notify_fail(capitalize(arg) + " is no library assistant.\n");
            return 0;
        case 1:
            write("You unassign " + capitalize(arg) + " as library " +
                "assistant.\n");
            GUILD_ADMIN->log(this_player(), "council", "Unappoints " +
                capitalize(arg) + " as library assistant");

            return 1;
    }
}

int
list_assistants(string arg)
{
    string *arr;

    if ((!is_in_temple()) || (!is_our_command() && !is_delegated_command()))
        return 0;

    if (!arg || arg != "library assistants")
    {
        notify_fail("List what? Library assistants?\n");
        return 0;
    }

    setuid();
    seteuid(getuid());
    
    arr = map(find_object(GUILD_LIB)->query_librarian(), capitalize);

    write("The librarians are: " + COMPOSITE_WORDS(arr) + ".\n");
    return 1;
}
