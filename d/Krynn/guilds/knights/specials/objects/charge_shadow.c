/*
 * Knight Charge Shadow
 *
 * While a Knight is charging, he should not attack someone else, nor
 * should he be able to be attacked. Previously, the OBJ_M_NO_ATTACK
 * property was simply set. This caused a lot of problems especially
 * when used in conjunction with other abilities that set OBJ_M_NO_ATTACK
 * such as the rescue ability.
 *
 * Created by Petros, November 2008
 */
 
#include <stdproperties.h>
#include <std.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"
#include "../../guild.h"

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define  PLAYER_I_CANNOT_BLOCK    "_player_i_cannot_block"

public int
has_knight_charge_shadow()
{
    return 1;
}

public void
remove_knight_charge_shadow()
{
    remove_shadow();
}

/*
 * Function name: query_prop
 * Description  : Find the value of a property. This function is usually
 *                implemented as CFUN, i.e. as real C implementation in the
 *                gamedriver as it is used so often. You should NOT mask this
 *                function in code. Use VBFC on the property value, if you
 *                must.
 * Arguments    : mixed prop - the name of the property (usually a string).
 * Returns      : mixed - the value of the property, or 0 if the property did
 *                    not exist..
 */
public mixed
query_prop(string prop)
{
    if (prop == OBJ_M_NO_ATTACK)
    {
        object attacker = this_interactive();
        object player = query_shadow_who();
        return player->query_The_name(attacker) + " is too far away for "
            + "you to attack.\n";    
    }
    else if (prop == PLAYER_I_CANNOT_BLOCK)
    {
        return "You cannot block while you are charging!\n";
    }
    
    return shadow_who->query_prop(prop);
}

/*
 * Function name: remove_prop
 * Description:   Removes a property string from the property list.
 * Arguments:     prop - The property string to be removed.
 */
public void
remove_prop(string prop)
{    
    shadow_who->remove_prop(prop);

    if (prop == LIVE_O_STEED)
    {
        CHARGE_ABILITY->stop_ability(shadow_who);
        set_alarm(0.0, 0.0, &remove_knight_charge_shadow());        
    }
}

/*
 * Function name: add_prop
 * Description:   Add a property to the property list
 *                If the property already exist, the value is replaced
 *                If a function "add_prop" + propname is declared or
 *                is shadowing this_object then that function is called
 *                prior to the setting of the property. 
 *                NOTE
 *                  If the optional function above returns something other
 *                  than 0. The property will NOT be set.
 *
 * Arguments:     prop - The property string to be added.
 *                val: The value of the property
 * Returns:       None.
 */
public void
add_prop(string prop, mixed val)
{
    shadow_who->add_prop(prop, val);

    if (prop == LIVE_O_STEED && !val)
    {
        CHARGE_ABILITY->stop_ability(shadow_who);
        set_alarm(0.0, 0.0, &remove_knight_charge_shadow());
    }    
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
    // If the Knight moves while charging, we want to stop the ability
    // and remove this shadow so they can be attacked again.
    
    int result = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
    if (!result) // success
    {
        CHARGE_ABILITY->stop_ability(shadow_who);
        
        send_debug_message("charge_shadow", "Player has moved, removing "
            + "shadow.");
            
        set_alarm(0.0, 0.0, &remove_knight_charge_shadow());
    }
    return result;
}


