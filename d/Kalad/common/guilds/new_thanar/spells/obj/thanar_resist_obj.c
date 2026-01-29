/*
* Standard Spell Resistance Object
*
* This is the spell object for the standard Genesis Magic System Resistance
* spell.
*
* Originaly created by Petros, March 2010, used by Mirandus, 2018
*/

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "../../local.h"

inherit "/d/Genesis/specials/std/spells/obj/resistance_obj";

/*
* Function:    create_spell_object
* Description: Override this to customize properties for the spell object
*/
public void
create_spell_object()
{
    set_name("_thanar_resistance_object_");
    set_short("provides magic resistance to Thanar Caster NPCs");
    set_long("This is the standard resistance spell's object. It protects "
        + "one against certain elements.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
        "created to protect against magic.\n");

}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();
    if (objectp(target))
    {
        target->catch_tell("Dark shadows emerge and shrouds you in " +
            "darkness.\n");
        tell_room(environment(target), QCTNAME(target) + " is shrouded by" +
            " dark shadows.\n", ({ target }));
    }    
}


/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell(" The shadows surrounding you disappear.\n");
        tell_room(environment(target), QCTNAME(target) + " is no"
            + " longer surrounded by dark shadows.\n", ({ target }));
    }
}

