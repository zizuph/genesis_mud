#include "defs.h"

private void
_cmd_lesser__appoint(string name, string position_name)
{
    int position = member_array(position_name, OVERSLOTS);

    if(position == -1 || position == POS_HIGH || position == POS_WIZ)
    {
        write("That is not a valid Lesser Overseer position.\n");
        return;
    }

    if(strlen(MANAGER->query_overseer_by_position(position)))
    {
        write("That Overseer position is already taken.\n");
        return;
    }

    object player = find_player(name);

    if(!interactive(player))
    {
        write(capitalize(name) + " is not present in the realms.\n");
        return;
    }

    if(!IS_MEMBER(player))
    {
        write(capitalize(name) + " is not a Gladiator.\n");
        return;
    }

    if(MANAGER->query_overseer_position(name) != POS_NONE)
    {
        write(capitalize(name) + " already holds an Overseer position.\n");
        return;
    }

    if(!ADD_OVERSEER(name, position_name))
    {
        write("An unknown error occured, please make a report.\n");
        return;
    }

    string msg = "You appoint " + capitalize(name) + " to the " +
        capitalize(position_name) + " Overseer position.\n";
    write(msg);
    WRITE_LOG(LOG_LESSER, TP, ": "+ msg);

    player->catch_tell(
        "You have been appointed to the " + capitalize(position_name) +
        " position by the High Overseer.\n"
    );

    object cuirasse = present(CUIR_ID, player);
    cuirasse->configure_cuirasse(player);
}

private void
_cmd_lesser__demote(string name)
{
    int position = MANAGER->query_overseer_position(name);

    if(position == POS_NONE)
    {
        write(capitalize(name) + " does not hold an Overseer position.\n");
        return;
    }

    if(!REM_OVERSEER(name))
    {
        write("An unknown error occured, please make a report.\n");
        return;
    }

    object tp = this_player();
    object player;
    string msg;

    if(name == tp->query_real_name())
    {
        msg = "You retire your position of High Overseer.\n";
        player = tp;
    } else {
        msg = "You demote "+ capitalize(name) + " from the " +
            capitalize(OVERSLOTS[position]) + " Overseer position.\n";

        player = find_player(name);

        if(interactive(player))
        {
            tell_object(player, "The High Overseer has stripped " +
                "you of your Overseer position.\n");
        }
    }

    write(msg);
    WRITE_LOG(LOG_LESSER, tp, ": "+ msg);

    if(!player)
    {
        return;
    }

    object cuirasse = present(CUIR_ID, player);
    cuirasse->configure_cuirasse(player);
}

/*
 * This function is for the High Overser to control the lesser overseer
 * positions.  Demote, Appoint, etcetera.
 */
public int
_cmd_lesser(string str)
{
    string *arr = explode((strlen(str) ? lower_case(str) : ""), " ");
    int sz = sizeof(arr);
    string command = (sz > 0 ? arr[0] : 0);
    string name = (sz > 1 ? arr[1] : 0);
    string position_name = (sz > 2 ? arr[2] : 0);

    switch(command)
    {
        case "appoint":
            if(!position_name)
            {
                break;
            }

            _cmd_lesser__appoint(name, position_name);
            return 1;
        break;
        case "demote":
            _cmd_lesser__demote(name);
            return 1;
        break;
    }

    return notify_fail("Usage: lesser <appoint | demote> <name> [position]\n");
}
