/*
 * infravision_sh
 * Zizuph, January, 2023
 */

// To test:
// Call *yourname add_autoshadow full/path/name

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>

inherit "/std/shadow";

int other_live_i_see_dark = 0;
int prepping = 0;

public int
racial_can_see_through_dark()
{
    object  room;
    int     natural,
            personal,
            artificial;
    
    room = environment(shadow_who);
    natural = room->query_prop(ROOM_I_LIGHT);
    personal = shadow_who->query_prop(OBJ_I_LIGHT);
    artificial = room->query_prop(OBJ_I_LIGHT);

    // Check if the room is naturally dark.
    if (natural < 1 && natural <= artificial)
    {
        //Check if you are using darkness items.
        if (personal < 0)
            return 0;
        
        // No magical interference.
        return 1;
    }
    
    return 0;
}

/*
 * Function name: racial_see_in_dark
 * Description  : Gives the player nightvision when circumstances allow.
 * Arguments    : None
 */
public int
infravision_see_in_dark()
{
    if (other_live_i_see_dark)
    {
        return other_live_i_see_dark;
    }
    return racial_can_see_through_dark();
}

public void remove_infravision_shadow()
{
    remove_shadow();
}

public void
initialize_infravision()
{
    prepping = 1;
    other_live_i_see_dark = shadow_who->query_prop(LIVE_I_SEE_DARK);
    shadow_who->add_prop(LIVE_I_SEE_DARK, infravision_see_in_dark);
    prepping = 0;
}

public void
shadow_me(mixed who)
{
    ::shadow_me(who);
    initialize_infravision();
}

/*
 * Function   : remove_shadow
 * Description: Removes the shadow without removing the shadowed object.
 */
public void 
remove_shadow()
{
    prepping = 1;
    shadow_who->add_prop(LIVE_I_SEE_DARK, other_live_i_see_dark);
    ::remove_shadow();
}


public int add_prop_live_i_see_dark(mixed value)
{
    if (prepping)
    {
        return 0;
    }
    int delta = value - infravision_see_in_dark();
    other_live_i_see_dark += delta;
    return 1;
}

public int remove_prop_live_i_see_dark()
{
    return add_prop_live_i_see_dark(0);
}

/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 */
public void
enter_env(object dest, object from)
{
    shadow_who->enter_env(dest, from);
}

