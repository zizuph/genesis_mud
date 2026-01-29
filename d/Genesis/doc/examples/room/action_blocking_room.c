/*
 * /doc/examples/room/action_blocking_room.c
 *
 * This demonstrates how to have a room block actions within it.
 */

inherit "/std/room";

#include <stdproperties.h>
#include <cmdparse.h>

void
create_room()
{
    set_short("Narrow tunnel");
    set_long("The walls of this narrow tunnel make movement difficult.\n");

    add_prop(ROOM_I_INSIDE, 1);
}

/*
 * Function name: block_action
 * Description:   Called to see if this room wants to prevent a living
 *                inside from performing an action.  This will be called
 *                once for each target.
 * Arguments:     string cmd - the command name
 *                object actor - the actor
 *                object target - the target of the action
 *                int cmd_attrs - the command's attributes (from cmdparse.h)
 * Returns:       0 - Command allowed
 *                1 - Command blocked without a failure message
 *                string - Command blocked, use return value as failure message
 */
public mixed
block_action(string cmd, object actor, object target, int cmd_attrs)
{
    /* The room prevents high activity actions */
    if (cmd_attrs & ACTION_HACTIVITY)
    {
        return "The tunnel is too tight to move around in.\n";
    }

    /* All other actions use the default */
    return ::block_action(cmd, actor, target, cmd_attrs);
}
