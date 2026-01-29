/*
/*
 * Blind spell object used in Kalad.
 * 
 *
 * Created by Zignur, Nov 2017.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit "/d/Genesis/specials/std/spells/obj/blind_obj";


/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();
    
    if (objectp(target))
    {
        target->catch_tell("Dark shadows obscure your vision.\n" +
        "You have been blinded!\n");
    }
    
    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " has been blinded!\n");
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
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();

    if (objectp(target))
    {
        target->catch_tell("The shadows vanish from your eyes.\n");
    }

    if (objectp(caster))
    {
        caster->catch_msg(QCTNAME(target) + " seems to be able to "
            + "see again.\n");
    }
}
/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    ::create_spell_object();
    set_dispel_time(15);
}

