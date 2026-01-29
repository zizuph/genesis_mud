/*
 * Support files for moving units.
 *
 * Hooks into the pathfinding module.
 */
#pragma strict_types

#include <macros.h>

static int move_alarm;
static mapping move_queue;
static object  move_destination;
static float   move_speed;
static function move_callback;

static void move_path();

#define PATHFINDER "/d/Khalakhor/lib/gks/pathfinder"

/*
 * Function Name: move_to
 * Description  : Attempt to find a path and move to the
 *                the target room.
 * Arguments    : string/object - destination room
 *                float speed   - time between each move
 *                function      - function to call when the destination
 *                                is reached.
 * Returns      : true if a path was found
 */
varargs int
move_to(mixed destination, float speed = 3.0, function callback = 0)
{
    object dest_ob;
    mixed path;
    
    if (stringp(destination))
    {
        if (LOAD_ERR(destination))
            return 0;
        dest_ob = find_object(destination);
    }

    if (!objectp(dest_ob))
    {
        return 0;
    }

    if (!environment()->query_local_coords() ||
        !dest_ob->query_local_coords())
    {
        return 0;
    }
    
    path = PATHFINDER->find_path(environment(), dest_ob);
    if (!path)
    {
        return 0;
    }

    move_destination = dest_ob;
    move_queue = path;
    move_speed = speed;
    move_callback = callback;

    if (!get_alarm(move_alarm))
        move_alarm = set_alarm(move_speed, 0.0, &move_path());
}

static void
move_path()
{
    string cmd;    

    if (environment() == move_destination)
    {
        if (functionp(move_callback))
            move_callback();
        
        move_queue = 0;
        move_destination = 0;
        move_callback = 0;        
        return;
    }
    
    if (cmd = move_queue[environment()])
    {
        command(cmd);
        return;
    }

    /* If we lost the past attempt to find a new way */
    if (!move_to(move_destination, move_speed, move_callback))
    {
        move_queue = 0;
        move_destination = 0;
        move_callback = 0;
    }
}

/*
 * Called from enter_env in the monster base to hook
 * into the movement.
 */
int
move_enter_env(object dest, object from)
{
    if (move_destination)
        move_alarm = set_alarm(move_speed, 0.0, &move_path());
}

     
