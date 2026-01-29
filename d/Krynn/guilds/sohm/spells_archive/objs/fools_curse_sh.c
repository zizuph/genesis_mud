/*
 * Fools curse cantrip for SOHM
 * 
 * This is a shadow for spell effects. It gets cloned by the shadow
 * spell object. One should inherit from this shadow only when defining shadow
 * effects. The shadow_obj.c file should automatically clone the right shadow.
 *
 * The shadow should be cloned when the effect is
 * added, and removed when the is gone. 
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/specials/std/spells/obj/shadow_base_sh";

#include "../defs.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

/*
 * Function:    initialize_shadow
 * Description: Should do all the initialization effects for this 
 *              particular shadow. Shadows derived from this one should
 *              override this.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("fool's curse");
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();
    object owner = environment(target);
    string old_long = target->query_long();

    if (objectp(target))
    {
        tell_room(owner, "Foul-smelling steam rises off the " + target->short() + " as a shadowy curse " +
           "entwines around it.\n", 
            ({ target }));
        tell_room(environment(owner), "Foul-smelling steam rises off the " + target->short() + " as a shadowy " +
           "curse entwines around it.\n", 
            ({ owner }));
    } 


    spell_object->set_dispel_time(10);

    target->add_prop(OBJ_M_NO_SELL,"After examining it the shopkeeper refuses to buy an item that seems cursed!\n");
    target->set_long(old_long + "A sinister-looking curse seems to crawl over it.\n");
    target->add_prop("_sohm_fools_curse", 1);
   
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{


}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{

}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
   
}

/*
string 
long(string str, object for_obj)
{
    return (shadow_who->long(str, for_obj) 
        + "A sinister-looking curse seems to crawl over it.\n");
}
*/

