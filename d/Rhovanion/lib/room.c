#pragma save_binary

#pragma strict_types
 
inherit "/std/room";
 
#include "/d/Gondor/common/lib/time.h"
#include <language.h>
#include <stdproperties.h>
 
#define LIMITED_CHECK_CALL 1
 
static mapping exit_mask = ([]);
static mixed fake_exits = ({});
 
/*
 * Function name: fake_exit
 * Description:   Lets us add a 'fake' exit that will be shown.
 * Arguments:     direction - The direction we want to fake.
 */
 
public void
fake_exit(mixed direction)
{
    fake_exits += ({ direction });
}
 
/*
 * Function name: unfake_exit
 * Description:   Removes a fake exit
 * Arguments:     direction - the direction to unfake
 */
 
public int
unfake_exit(mixed direction)
{
    int i;
    i = member_array(direction, fake_exits);
    if (i != -1)
        fake_exits = exclude_array(fake_exits, i, i);
    return (i != -1);
}
 
/*
 * Function name: mask_exit
 * Description:   Set a variable describing a masking for this exit
 * Arguments:     exit - the direction of the exit to possibly hide
 *                mask - type function (return value int), vbfc string, or
 *                       int. Hide the exit if 1 (when evaluated).
 */
public void
mask_exit(string exit, mixed mask)
{
    exit_mask[exit] = mask;
}
 
/*
 * Function name: unmask_exit
 * Description:   Remove a direction from that masking map
 * Arguments:     exit - the direction to remove
 * Returns:       1 if the direction was masked, else 0
 */
 
public int
unmask_exit(string exit)
{
    if (member_array(exit, m_indices(exit_mask)) < 0)
        return 0;
    exit_mask = m_delete(exit_mask, exit);
    return 1;
}
 
/*
 * Function name: add_mask_exit
 * Description:   do both add_exit and mask_exit in one function.
 * Arguments:     maskval - as in mask_exit, others as in add_exit
 */
 
public varargs void
add_mask_exit(mixed maskval, mixed room, string cmd, mixed efunc, mixed tired)
{
    mask_exit(cmd, maskval);
    add_exit(room, cmd, efunc, tired);
}
 
/*
 * Function name: query_exit_mask
 * Description:   tell us what the mask value is for a particular direction
 * Arguments:     exit - the direction to test
 * Returns:       the value (type function, string or int)
 */
 
public mixed
query_exit_mask(string exit)
{
    return exit_mask[exit];
}
 
/*
 * Function name: query_all_mask
 * Description:   get the whole exit mask mapping
 * Returns:       the mapping
 */
public mapping
query_all_mask()
{
    return exit_mask;
}
 
/*
 * Function name: exit_description
 * Description:   describe the exits - modified from the original to
 *                conditionally hide exits.
 */
public varargs string
exits_description()
{
    string *exits, ex;
    int i, j;
    mixed k;
 
    exits = query_exit_cmds() + map(fake_exits, check_call);
    i = sizeof(exits);
    while(i--)
    {
#ifdef LIMITED_CHECK_CALL
        {
            k = exit_mask[exits[i]];
            if (functionp(k))
                k = k();
            else
                k = check_call(k);
            if (k)
                exits = exclude_array(exits, i, i);
        }
#else
        if (check_call(exit_mask[exits[i]]))
            exits = exclude_array(exits, i, i);
#endif
    }
    i = sizeof(exits);
    if (!i)
        return "";
 
    if (i == 1)
        return "There is one obvious exit: " + exits[0] + ".\n";
 
    ex = "There are " + LANG_WNUM(i) + " obvious exits: " + exits[0];
 
    for (i = 1, j = sizeof(exits); i < j; i++)
        ex += ", " + exits[i];
    return break_string(ex + ".\n", 76);
}
 
/*
 * Function name: check_for_door_open
 * Description:   Return 1 if the door is not open, to mask the exit.
 * Arguments:     dir - the direction the door leads.
 * Returns:       1 - door is not open (or not there); 0 - door is open.
 */
public int
check_for_door_open(string dir)
{
    object *ob;

    ob = filter(query_prop(ROOM_AO_DOOROB), &operator(!=)(, -1) @
        &member_array(dir) @ &->query_pass_command());
    if (!sizeof(ob))
        return 1;
    return !ob[0]->query_open();
}
 
/*
 * Function name: add_door_to_exits
 * Description:   add a door to the list of shown exits, when open
 * Arguments:     dir - the direction the door leads
 */
public void
add_door_to_exits(string dir)
{
    fake_exit(dir);
    mask_exit(dir, &check_for_door_open(dir));
}