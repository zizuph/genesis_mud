/*
 * Dragonfear Shadow
 * 
 * This shadow is called whenever a dragon leaves or enters a room,
 * allowing it to properly refresh its strength without using a
 * repeating alarm.
 *
 * Created by Petros, March 2009
 */

#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include <filter_funs.h>

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

public int
has_dragonfear_shadow()
{
    return 1;
}

public void
remove_dragonfear_shadow()
{
    remove_shadow();
}

public void
refresh_dragon_fear()
{
    object fear_obj;
    
    if (!objectp(fear_obj = present("ansalon_krynn_dragonfear", shadow_who)))
    {
        set_alarm(0.0, 0.0, remove_dragonfear_shadow);
        return;
    }
    
    fear_obj->refresh_dragon_fear();
}

/*
 * Function name: move_living
 * Description:   Posts a move command for a living object somewhere. If you
 *                have a special exit like 'climb tree' you might want to
 *                use set_dircmd() and set it to 'tree' in the room to allow
 *                teammembers to follow their leader.
 * Arguments:     how:      The direction of travel, like "north".
 *                          "X" for teleportation, team does not follow.
 *                          "M" if you write leave and arrive messages yourself.
 *                to_dest:  Destination
 *                dont_follow: A flag to indicate group shall not follow this
 *                          move if this_object() is leader
 *                no_glance: Don't look after move.
 *
 * Returns:       Result code of move:
 *                      0: Success.
 *
 *                      3: Can't take it out of it's container.
 *                      4: The object can't be inserted into bags etc.
 *                      5: The destination doesn't allow insertions of objects.
 *                      7: Other (Error message printed inside move() func)
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int results;
    
    results = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
    refresh_dragon_fear();

    return results;
}
