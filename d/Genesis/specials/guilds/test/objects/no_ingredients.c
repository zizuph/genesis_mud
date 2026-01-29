/*
 * No Ingredients Object
 *
 * This object if cloned autoloads with a wizard
 * and sets the property that allows wizards to not need ingredients
 * using the Genesis new spell system.
 *
 * Created by Petros, December 2009
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <files.h>

inherit "/std/object";

// Defines
#define WIZ_IGNORE_INGREDIENTS_PROP "_wizard_ignore_spell_ingredients"

/*
 * Function name: create_object
 * Description  : Constructor. Called to create the object when it is cloned.
 */
void
create_object()
{
    set_name("clasp");
    add_adj("small");
    add_adj("onyx");
    set_long("The clasp will allow you to cast spells without "
        + "needing ingredients.\n");
    
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
}

public int
can_ignore_ingredients(object caster)
{
    if (!objectp(caster))
    {
        return 0;
    }
    
    // Wizards, juniors, and npcs can ignore components.
    if (caster->query_wiz_level()
        || wildmatch("*jr", caster->query_real_name())
        || !IS_PLAYER_OBJECT(caster))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function name: enter_env
 * Description  : This function is called whenever this object enters a new
 *                environment. We add the LIVE_I_ALWAYSKNOWN property to
 *                the environment if the environment is a wizard.
 * Arguments    : object inv  - the environment this object is entering.
 *                object from - the possible place this object came from.
 */
void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);

    if (can_ignore_ingredients(inv))
    {
    	inv->add_prop(WIZ_IGNORE_INGREDIENTS_PROP, 1);
    }
}

/*
 * Function name: leave_env
 * Description  : This function is called whenever this object leaves its
 *                environment. We remove the LIVE_I_ALWAYSKNOWN property
 *                from the environment if the environment is a wizard. Note
 *                that this function is also called when this object is
 *                destructed.
 * Arguments    : object inv - the environment this object is leaving.
 *                object to  - the possible new destination of this object.
 */
void
leave_env(object inv, object to)
{
    ::leave_env(inv, to);

    if (can_ignore_ingredients(inv))
    {
    	inv->remove_prop(WIZ_IGNORE_INGREDIENTS_PROP);
    }
}

/*
 * Function name: query_auto_load
 * Description  : Return the filename of this module to allow it to be
 *                autoloadable.
 * Returns      : string - the filename of this module.
 */
string
query_auto_load()
{
    return MASTER;
}
