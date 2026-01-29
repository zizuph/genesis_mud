/*
 * Intimidate Shadow
 * 
 * The purpose of this shadow is to check whether the person is outside
 * or inside, and to set the intimidate effect accordingly.
 *
 * Created by Petros, January 2009
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
has_intimidate_shadow()
{
    return 1;
}

public void
remove_intimidate_shadow()
{
    remove_shadow();
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
    int oldIsInside, newIsInside;
    
    oldIsInside = environment(shadow_who)->query_prop(ROOM_I_INSIDE);
    results = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
    newIsInside = environment(shadow_who)->query_prop(ROOM_I_INSIDE);
    // After moving, check to see if we are still inside. If not, we
    // remove the intimidate effects
    object * objs = filter(all_inventory(shadow_who), 
                                &->id("da_intimidate_object"));
    if (!sizeof(objs))
    {
        set_alarm(0.0, 0.0, &remove_intimidate_shadow());
        return results;
    }
    
    if (oldIsInside ^ newIsInside)
    {
        if (newIsInside)
        {                                        
            objs[0]->start_intimidate_effects(shadow_who);
            shadow_who->catch_tell("You feel a growing sense of doom as "
                + "you enter the enclosed space, the curses of the "
                + "Dark Queen still troubling you.\n");
        }
        else
        {
            objs[0]->remove_intimidate_effects(shadow_who);
            shadow_who->catch_tell("Your sense of doom fades as you "
                + "find yourself out in the open and you feel a bit "
                + "more at ease.\n");
        }
    }
           
    return results;       
}
