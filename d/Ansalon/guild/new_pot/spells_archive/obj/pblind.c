/* 
 * pblind object - simple blindness
 */

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>

inherit "/d/Genesis/specials/std/spells/obj/blind_obj";

#define BLIND_SUBLOC "pot_blind_subloc"
#define BLIND_CURSE "_pot_blind_curse"

object pot_caster = TO->query_spell_effect_caster();

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    add_name(BLIND_ID);
    set_spell_effect_desc("blind");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "PoT magical object blinding the affected.\n");

    set_dispel_time(20);

}

/*
 * Function:    setup_spell_effect
 * Description: This is called to set up all the things for the
 *              spell. Must call the parent's setup_spell_effect
 *              in order to get the maintainence stuff.
 */
public int
setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }
    query_effect_target()->inc_prop(LIVE_I_BLIND);
    query_effect_target()->add_subloc(BLIND_SUBLOC, TO);
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    int result = ::dispel_spell_effect(dispeller);
    if (!result)
    {
        return result;
    }
    
    query_effect_target()->dec_prop(LIVE_I_BLIND);
    query_effect_target()->remove_subloc(BLIND_SUBLOC);
    return 1;
}

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
        target->catch_tell("You have been blinded!\n");
        target->add_prop(BLIND_CURSE, 1);
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

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        target->catch_tell("The black fire leaves your eyes, and you can "+
			"see again.\n");
        target->remove_prop(BLIND_CURSE);
    }
    if (objectp(caster))
    {
        caster->catch_msg("The black fire leaves " +QTPNAME(target) +
            " eyes.\n");
        target->tell_watcher("The black fire leaves " +QTPNAME(target) +
            " eyes.\n", ({ caster }), ({ caster }));
    }
}

public string
query_subloc_name(string element) 
{
    return BLIND_SUBLOC;
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
        return "Your eyes are blinded by a blanket of black fire.\n";

    return C(HIS(me)) + " eyes are covered by a blanket of black fire.\n";
}

