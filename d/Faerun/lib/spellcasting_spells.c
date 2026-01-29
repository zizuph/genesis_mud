/*
 *  faerun/lib/spellcasting_spells.c
 *
 *  This object is used by the spellcasting inherit, it should not be called
 *  directly.
 *
 *  Created by Wully, 12-2-2004
 */

#include <macros.h>
#include "/d/Faerun/defs.h"

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

/*
 * Functionn name: create_object
 * Description   : Constructor
 */
void create_object()
{
    // Only set it up for clones
    if (!IS_CLONE) return;

    // Make sure it isnt visibile, weights nothing etc
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VALUE, 0);
    set_no_show();
}

/*
 * Function name: enter_env
 * Description  : Add spells to our environment when we enter one
 */
void enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}

/*
 * Function name: leave_env
 * Description  : Destroy our spells when we leave an environment
 */
void leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

/*
 * Function name: remove_object
 * Description  : Destroy the object and the created spell objects
 */
void remove_object()
{
    cleanup_spells();
    ::remove_object();
}

