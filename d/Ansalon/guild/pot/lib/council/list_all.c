/* Stralle @ Genesis 050116
 *
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/lib/council/std_council";

#include <composite.h>
#include <files.h>
#include "../../guild.h"

mapping
query_listall_commands()
{
    return ([ "list" : "list_all" ]);
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

int
list_all(string arg)
{
    return list_herbaccess(arg) || list_council_members(arg) ||
           list_assistants(arg) || list_pilgrims(arg);
}
