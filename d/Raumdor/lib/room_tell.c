/*
 * Yet another room tell system, this one using the 'ticker' object. Plus,
 * it is newer than all of those others, so therefore better.
 *
 * Features:
 *  - No iniialization steps
 *  - Tells optionally randomized
 *  - Tells optionally skipped at random
 *  - Tells and groups of tells can be removed by ID
 *  - Supports any arbitrary tell time (delay) over 0.0
 *  - Strings can be VBFC
 *
 * Disadvantages:
 *  - Author leaves illogical, irrelevant, and possibly arrogant comments
 *  - Doesn't accomplish much if your rooms don't use the same tell time
 *  - Long-nosed armadillos normally give birth to monozygotic quadruplets
 *
 * Usage:
 *
 *  add_room_tell(({
 *      "One tell.\n",
 *      "Two tell.\n",
 *      "Green tell.\n",
 *      "Blue tell.\n",
 *  }));
 *  int temp_tell = add_room_tell("This won't happen for long.\n");
 *  set_alarm(1000.0, 0.0, &remove_room_tell(temp_tell)); 
 *
 * 2018 Malus
 *
 */

#pragma no_clone
#pragma strict_types

#include "defs.h"
#define TICKER (LIB_DIR + "ticker")

private static int      count = 0,
                        registered = 0,
                        skip = 0,
                        randomize = 1;
private static float    tell_time = 120.0;
private static mapping  tell_list = ([]);
private static string  *tells_remaining = ({});

/*
 * Function Name:   query_room_tells
 *   Description:   All tell strings currently used
 *     Arguments:
 *       Returns:   string *
 */
public string *
query_room_tells()
{
    string *tells = ({});
    foreach (int id, string *list: tell_list)
        tells += list;

    return tells;
}

/*
 * Function Name:   do_room_tell
 *   Description:   Attempt one tell in the room.
 *     Arguments:   time counter
 *       Returns:   0 - Tell performed
 *                  1 - Tell skipped
 */
public int
do_room_tell()
{
    int num = 0;
    string tell;

    if (!sizeof(tells_remaining))
        tells_remaining = query_room_tells();

    if (randomize)
        num = random(sizeof(tells_remaining));

    tell = tells_remaining[num];
    tells_remaining = exclude_array(tells_remaining, num, num);

    if (skip && !random(skip))
        return 1;

    tell_room(this_object(), tell);

    return 0;
}
/*
 * Function Name:   set_room_tell_skip
 *   Description:   Set chance of skipping a message each call
 *     Arguments:   int chance <=0 - disabled
 *                              >0 - 1/chance probability of skipping
 *       Returns:   void
 */
public void
set_room_tell_skip(int num)
{
    if (num < 0)
        num = 0;
    skip = num;
}

/*
 * Function Name:   set_room_tell_randomize
 *   Description:   Set whether to randomize message order
 *     Arguments:   int i - 0 disabled, else enabled
 *       Returns:   void
 */
public void
set_room_tell_randomize(int i)
{
    randomize = i;
}

private void
unregister_room_tells()
{
    if (registered)
    {
        TICKER->unregister(registered);
        registered = 0;
    }
}

private void
register_room_tells()
{
    if (!registered)
        registered = TICKER->register(tell_time, &do_room_tell());
}

/*
 * Function Name:   set_room_tell_time
 *   Description:   Set the time between calls to do_room_tell()
 *     Arguments:   float/int time: Interval
 *       Returns:   void
 */
public void
set_room_tell_time(mixed time)
{
    if (intp(time))
        time = itof(time);
    else if (!floatp(time))
       throw("time must be float or int");

    if (tell_time != time)
        unregister_room_tells();

    tell_time = time;
    if (m_sizeof(tell_list))
        register_room_tells();
}

/*
 * Function Name:   query_room_tell_time
 *   Description:   Returns the time between calls to do_room_tell()
 *     Arguments:   
 *       Returns:   (float) room tell time
 */
public float
query_room_tell_time()
{
    return tell_time;
}

/*
 * Function Name:   add_room_tell
 *   Description:   Adds one or more tells to a room
 *     Arguments:   mixed tell: The text of the desired message, or an array
 *                  of such strings. Can be VBFC.
 *       Returns:   (int) id: Value needed to remove this tell
 */
public int 
add_room_tell(mixed tell)
{
    if (stringp(tell))
        tell = ({tell});
    else if (!pointerp(tell) || !sizeof(tell) || typeof(tell[0]) != T_STRING)
        throw("tell must be a string or array of strings");

    tell_list[++count] = tell;
    register_room_tells();

    return count;
}

/*
 * Function Name:   remove_room_tell
 *   Description:   Remove tell(s) from the list of tells.
 *     Arguments:   mixed id: The id or array of ids from add_room_tell()
 *       Returns:   void
 */
public void
remove_room_tell(mixed id)
{
    if (intp(id))
        id = ({id});
    else if (!pointerp(id) || !sizeof(id) || typeof(id[0]) != T_INTEGER)
        throw("id must be an int or array of ints");

    foreach (int i: id)
        m_delkey(tell_list, id);

    tells_remaining = ({});
    if (!m_sizeof(tell_list))
        unregister_room_tells();
}
