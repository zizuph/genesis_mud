#include "../../morgulmage.h"

#include <stdproperties.h>
#include <macros.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_OBJ_DIR + "summon_obj";

object paralyze;
object shadow;

public void 
create_spell_object()
{
    set_name("_crabandir_object_");
    set_short("crabandir spell object");    
    set_long("This is the standard summon spell's object. It exists "
        + "to keep track of the caster's maintained effects.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object "
        + "created by the Morgul Mage crabandir spell.\n");

    set_spell_effect_desc("summoned crebain");    
    // set_dispel_time(300 + random(180)); 
}

public int
setup_spell_effect()
{
    object original_target = query_effect_target();

    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }

    // Override the effect target back what it originally was
    object crows = query_effect_target();
    set_spell_effect_target(original_target);

    setuid();
    seteuid(getuid());
    paralyze = clone_object(MORGUL_SPELL_OBJ_DIR + "crabandir_paralyze");
    paralyze->set_stop_fun("remove_craban");
    paralyze->set_stop_object(this_object());
    paralyze->set_stop_message("You dismiss the crebain.\n");
    paralyze->set_fail_message( "You can only watch through the eyes of "
        + "the craban, but you have no control over it.\nYou can steer your "
        + "awareness back to your undead body by using the command "
        + "\"peluvo\".\n");
    paralyze->set_stop_verb("peluvo");
    paralyze->move(query_effect_caster(), 1);

    shadow = clone_object(MORGUL_SPELL_OBJ_DIR + "crabandir_sh");
    shadow->set_spell_object(this_object());
    shadow->shadow_me(query_effect_caster());

    crows->set_spell_object(this_object());
    crows->start_search(query_effect_target(), query_effect_caster());
    return result;
}

public varargs int
dispel_spell_effect(object dispeller)
{
    object caster = query_effect_caster();

    int result = ::dispel_spell_effect(dispeller);
    if (!result) return result;

    if (objectp(paralyze)) 
    {
        caster->catch_tell("You are in control of your undead "
            + "body again.\n");

        tell_room(environment(caster), "The body of "
            + QTNAME(caster) + " begins to stir again.\n"
            + capitalize(caster->query_possessive()) 
            + " spirit seems to have returned to "
            + caster->query_possessive() + " undead body.\n", 
            caster);        
        
        paralyze->remove_object();
    }

    if (objectp(shadow))
    {
        shadow->remove_shadow();
    }
}

public void
remove_craban()
{
    set_alarm(0.0, 0.0, &dispel_spell_effect(this_player()));
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to the target.
 */
public void
hook_spell_effect_started()
{
    object caster = query_effect_caster();

    tell_room(environment(caster), QCTNAME(caster) + " slumps to the ground.\n"
        + capitalize(caster->query_possessive()) + " undead body is like an "
        + "empty vessel, left behind by a spirit that departed elsewhere.\n", 
        ({ caster }), caster);

    caster->catch_tell("Your awareness enters the crabain which you summoned."
        + "\nYou lose the control over your undead body and start seeing "
        + "with the eyes of the craban.\n");
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object caster = query_effect_caster();
    if (!objectp(caster))
    {
        return;
    }
    
    if (!objectp(summon_object))
    {
        caster->catch_tell("You sense that your magically summoned "
            + "monster has faded from existence.\n");
        return;
    }
    
    caster->catch_tell("Your sense the magically summoned " 
        + summon_object->short() + " fade from existence.\n");
    tell_room(environment(summon_object), QCTNAME(summon_object)
        + " disappears.\n", ({ caster }));
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading()
{
    object caster = query_effect_caster();
    if (!objectp(caster) || !objectp(summon_object))
    {
        return;
    }
    
    caster->catch_tell("Your sense the magically summoned " 
        + summon_object->short() + " begin to fade from existence.\n");    
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
    
    if (objectp(caster) && objectp(summon_object))
    {
        caster->catch_tell("You are mentally unable to maintain "
            + "the summoned " + summon_object->short() + ".\n");
    }    
}
