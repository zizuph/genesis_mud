#include "defs.h"
#include <composite.h>

private void
_cmd_punish__query(string name, mixed tmp)
{
    if(name == "all")
    {
        if(!sizeof(tmp))
        {
            write("Nobody seems to be under that punishment.\n");
            return;
        }

        write(
            "The following are affected by that punishment:\n" +
            sprintf("%-#78s\n", implode(map(tmp, capitalize), "\n"))
        );
    } else if(tmp > 0) {
        write(capitalize(name) + " is under that punishment.\n");
    }  else {
        write(capitalize(name) + " is not under that punishment.\n");
    }
}

private void
_cmd_punish__add(string name, mixed tmp, int punishment_int, string punishment_name, object tp)
{
    if(tmp > 0)
    {
        write(capitalize(name) + " is already under that punishment.\n");
    } else if(ADD_PUNISHMENT(name, punishment_int)) {
        string msg = "Punishment '" + punishment_name + "' added to: " + capitalize(name) + ".\n";
        write(msg);
        WRITE_LOG(LOG_PUNISH, tp, ": "+ msg);
    } else {
        write("Unable to add that punishment to " + capitalize(name) + ".\n");
    }
}

private void
_cmd_punish__remove(string name, mixed tmp, int punishment_int, string punishment_name, object tp)
{
    if(tmp <= 0)
    {
        write(capitalize(name) + " is not under that punishment.\n");
    } else if(REM_PUNISHMENT(name, punishment_int)) {
        string msg = "Punishment '" + punishment_name +"' removed from: " + capitalize(name) + ".\n";
        write(msg);
        WRITE_LOG(LOG_PUNISH, tp, ": "+ msg);
    } else {
        write("Unable to remove that punishment from " + capitalize(name) + ".\n");
    }
}

/*
 * This function handles punishemnts.  Listing, adding, removing, etcetera.
 * Only the High Overseer may invoke some of these.
 * Only the High Overseer may punish Lesser Overseers.
 */
public int
_cmd_punish(string str)
{
    object tp = this_player();
    string *arr;

    if(!strlen(str) || sizeof(arr = explode(lower_case(str), " ")) != 3)
    {
        return notify_fail("Usage: punish <add|rem|query> <name> <type>\n");
    }

    string command = arr[0];
    string name = arr[1];
    string punishment_name = arr[2];
    int punishment_int = MAP_PUN[punishment_name];

    if(punishment_int == 0)
    {
        return notify_fail(
            "That is not a valid punishment.  Choose from:\n  "+
            COMPOSITE_WORDS(m_indexes(MAP_PUN)) + "\n"
        );
    }

    if(name == "all" && command != "query")
    {
        return notify_fail("You may only 'query' all, not 'add' nor 'rem'.\n");
    }

    int pos = POSITION(tp);

    if(command != "query" && punishment_int == PUN_EXPEL && pos != POS_HIGH)
    {
        return notify_fail("Only the High Overseer may 'expel'.\n");
    }

    switch(MANAGER->query_overseer_position(name))
    {
        case POS_NONE:
        break;

        case POS_WIZ:
        case POS_HIGH:
            return notify_fail("Surely you jest, you may not punish that individual.\n");
        break;

        default:
            if(pos != POS_HIGH && pos != POS_WIZ)
            {
                return notify_fail("Only the High Overseer may punish the Lesser Overssers.\n");
                break;
            }
    }

    mixed tmp = CHECK_PUNISHMENT(name, punishment_int);

    switch(command)
    {
        case "query":
            _cmd_punish__query(name, tmp);
            return 1;
        break;


        case "add":
            _cmd_punish__add(name, tmp, punishment_int, punishment_name, tp);
            return 1;
        break;

        case "rem":
            _cmd_punish__remove(name, tmp, punishment_int, punishment_name, tp);
            return 1;
        break;
    }

    return notify_fail("Usage: punish <add|rem|query> <name> <type>\n");
}
