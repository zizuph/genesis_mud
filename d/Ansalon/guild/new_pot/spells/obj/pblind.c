/* 
 * pblind object - simple blindness
 */

#include "../../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "blind_obj";

#define BLIND_SUBLOC "pot_blind_subloc"
#define BLIND_CURSE "_pot_blind_curse"

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
    query_effect_target()->remove_subloc(BLIND_SUBLOC);
    return 1;
}

/*
 * Function:    hook_blind_begin
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_blind_begin(object actor, object target, object *effects)
{
    if (objectp(actor) && objectp(target))
    {
        if (!target->query_prop(BLIND_CURSE))
        {
            actor->catch_msg(QCTNAME(target) + " has been blinded!\n");
        }
        else
        {
            actor->catch_msg(QCTNAME(target) +
                " has been further blinded!\n");
        }
    }
    if (objectp(target))
    {
        if (!target->query_prop(BLIND_CURSE))
        {
            target->catch_tell("You have been blinded!\n");
        }
        else
        {
            target->catch_tell("You have been further blinded!\n");
        }
        target->inc_prop(BLIND_CURSE, 1);
    }
}

/*
 * Function:    hook_blind_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_blind_ended(object actor, object target, object *effects)
{
    if(target->query_ghost())
        return;

    target->dec_prop(BLIND_CURSE);

    if (objectp(target))
    {
        if (!target->query_prop(BLIND_CURSE))
        {
            target->catch_tell("The black fire leaves your eyes, and you can "+
			    "see again.\n");
        }
    }
    if (objectp(actor) && !target->query_prop(BLIND_CURSE))
    {
        actor->catch_msg("The black fire leaves " +QTPNAME(target) +
            " eyes.\n");
        target->query_combat_object()->
            tell_watcher("The black fire leaves " + QTPNAME(target) +
            " eyes.\n", ({ actor }), ({ actor }));
    }
}

public void hook_blind_failed(object actor, object target)
{
    if (objectp(actor))
    {
        actor->catch_msg(
            "The black fire appears to have no effect.\n");
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

    if (subloc != BLIND_SUBLOC)
        return "";

    if (for_obj == me)
        return "Your eyes are blinded by a blanket of black fire.\n";

    return C(HIS(me)) + " eyes are covered by a blanket of black fire.\n";
}
