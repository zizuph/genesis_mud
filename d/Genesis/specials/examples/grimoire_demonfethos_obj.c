/* 
 * tutorial demonfethos stoneskin spell object
 */

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/stoneskin_obj";

#define PROTECTION_SUBLOC "demonfethos_protection_subloc"

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_demonfethos_object_");
    set_short("tutorial demonfethos spell object");    
    set_long("This is the tutorial protection spell object, based on the standard " +
        "stoneskin spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by the demonfethos spell.\n");
    set_spell_effect_desc("protection from demons");  
    set_spell_effect_notes("'Demonfethos' is a magical shield that will protect " +
        "the caster from some attacks from demons. Be warned, it only provides " +
        "protection from demons specifically!\n\nAll spells use mana, and spells that " +
        "are maintained such as this one will drain a small amount of mana as long " +
        "as the caster keeps it active.\n\nA caster's mana pool is determined by " +
        "one's intelligence, while mana regeneration speed is impacted by one's " +
        "wisdom and spellcraft skill.\n");  
}

/*
 * Function:    query_damage_modification_file
 * Description: Mask this function if you want to customize the attack_modified
 *              messages in the damage modification. 
 */
public string
query_damage_modification_file()
{    
    return "/d/Genesis/specials/examples/demonfethos_dam_mod_obj_base";
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
        target->catch_tell("You feel an intricate protective web of magic surround " +
           "you, and you feel less vulnerable to attacks from demons.\n\nFor more " +
           "information about your maintained spells, check your <spelleffects>.\n");
        tell_room(environment(target), QCTNAME(target) + " is surrounded by an intricate " +
           "protective web of magic.\n", ({ target }));
    }  

    target->add_prop(PROTECTION_SUBLOC, 1);  
}

public int setup_spell_effect()
{
    int result = ::setup_spell_effect();
    if (!result)
    {
        return result;
    }
    set_dispel_time(180);
    return result;
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
    object caster = query_effect_caster();

    if(target->query_ghost())
        return;
    
    if (objectp(caster))
    {
        caster->catch_tell("You feel the magical shield of protection " +
        "leave you, and you are more vulnerable to the attacks of demons.\n");
    }

    target->remove_prop(PROTECTION_SUBLOC);
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
        target->catch_tell("You feel the magical shield of protection begin to wane.\n");
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
        caster->catch_tell("Mentally drained, the magical shield of protection "+
           " leaves you.\n");
    }    
}

/*
 * Function:    query_stoneskin_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_stoneskin_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are surrounded by an intricate web of magical energy, providing " +
                "some protection from the attacks of demons.\n";
    else
        return capitalize(on->query_pronoun()) + " is surrounded by an intricate web of " +
            "protective magical energy.\n";
}

