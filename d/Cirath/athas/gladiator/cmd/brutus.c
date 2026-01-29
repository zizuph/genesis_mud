#include "defs.h"
#include <composite.h>

/*
 * This function controls listing and removing of those that have
 * attacked the GM npc 'brutus'.  This is needed as there are automatic
 * punishments involved in attacking him.
 */
public int
_cmd_brutus(string str)
{
    string name, *arr;

    if (!strlen(str))
        return notify_fail("Syntax: brutus <list> [name] | brutus <rem> <name>\n");

    sscanf(str, "%s %s", str, name);
    switch(str)
    {
    case "list":
        if (strlen(name))
        {
            if (!sizeof(arr = MANAGER->query_brutus_attacker(name)))
            {
                str = "No one has attacked Brutus by that name.\n";
                break;
            }

            str = capitalize(name) + ": "+ COMPOSITE_WORDS(arr) + "\n";
        }
        else
        {
            int ix = -1, sz;

            arr = m_indexes(MANAGER->query_brutus_attacker(0));
            sz = sizeof(arr = sort_array(arr));

            if (sz == 0)
            {
                str = "No one has attacked Brutus recently.\n";
                break;
            }

            str = 0;
            while(++ix < sz)
                _cmd_brutus("list "+ arr[ix]);
        }
        break;

    case "rem":
        if (!strlen(name))
        {
            str = "Syntax: brutus <list> [name] | brutus <rem> <name>\n";
            break;
        }

        if (MANAGER->remove_brutus_attacker(name))
        {
            str = capitalize(name) + " removed from the list.\n";
            WRITE_LOG(LOG_BRUTUS, TP, ": " + str);
        }
        else
        {
            str = "Unable to remove '"+ capitalize(name) +"' from "+
            "the list.\n";
        }
        break;

    default:
        str = "Syntax: brutus <list> [name] | brutus <rem> <name>\n";
        break;
    }

    if (strlen(str))
        write(str);

    return 1;
}
