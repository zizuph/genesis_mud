/*
 * Standard Spell Resistance Object
 *
 * This is the spell object for the standard Genesis Magic System Resistance
 * spell. 
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>
#include "/d/Shire/common/defs.h"
#include "../../herald.h"

inherit "/d/Genesis/specials/new/magic/spells/objs/resistance_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_namotir_protect_death_object_");
    set_short("ward against death magic object");    
    set_long("This is the standard resistance spell's object. It "
        + "protects one against certain elements.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created to protect against death magic.\n");
    set_spell_effect_desc("Namo's protection");    
}


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You are warded from death magics.\n");
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
        target->catch_tell("You feel your protection against " +
           "death magic disappear.\n");
        tell_room(environment(target), QCTNAME(target) + " is no longer " +
           "channelling the protections granted by Nemo, Keeper of " +
           "the Dead.\n", ({ target }));
    }

}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object target = query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You feel you will not be able to maintain " +
            "your channelling of namotir for much longer.\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained()
{
    object caster = query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "namotir.\n");
    }    
}