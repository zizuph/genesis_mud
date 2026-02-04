/* 
 * Minstrel Lento quickness debuff object
 */

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"
#include "../../guild_defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/haste_obj";

#define MINSTREL_LENTO_EFFECT "_minstrel_lento_effect"
#define LOST_MUSE_EFFECT "_minstrel_lost_muse_effect_active"

/*
 * Function:    convert_aid_to_quickness
 * Description: LIVE_I_QUICKNESS uses a system that is based on a
 *              number between 1-500. Haste combat aid is based on
 *              calculation of (haste / 500 - haste). We simply
 *              convert the combat aid for the aid into the haste
 *              number that can be plugged in.
 */
public int
convert_caid_to_haste(object player, int aid)
{ 
    int quickness = ::convert_caid_to_haste(player, aid);
    // This is an anti-haste spell, so it provides negative quickness
    // of equivalent value to a positive haste spell of the same caid
    return -quickness;
}

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_lento_object_");
    set_short("Minstrel lento song object");    
    set_long("This is the Minstrel lento song object, based on the " +
        "standard haste debuff spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by " +
        "the lento song.\n");
    set_spell_effect_desc("song of lethargy"); 
    set_spell_effect_notes("This torpid Song of Power disrupts the " +
        "natural tempo of a Minstrel's enemies. Up to three enemies are " +
        "affected by this Song of Power. It should be noted that the slowing " +
        "fades shortly after the Minstrel moves away from the presence " +
        "of the enemies.\n\nAs with all Songs of Power inspired by a " +
        "Lost Muse, only one can be effectively performed at a time.\n");   
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
    int power = query_spell_effect_power();
    // Power determines how long the spell lasts
    // play and sing skills: 60,50   100,100
    // 100 stat  duration:   35      38  
    // 200 stat  duration:   42      47  
   
    // int duration = ftoi(itof(power)); 
    // set_dispel_time(duration);
    return result;
}

/*
 * Function:    query_spell_effect_still_valid()
 * Description: For a maintained spell effect, this allows the spell
 *              effect to determine whether it is still valid or not.
 *              In the maintain_spell_effects function, it will dispel
 *              the effect object if it determines that it is no longer
 *              valid.
 */
public int
query_spell_effect_still_valid()
{
    object target = query_effect_target();
    object caster = query_effect_caster();

    if (!target)
        return 0;
    if(present(caster, environment(target)))
        return 1;
    else
        return 0;
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
    object caster = query_effect_caster();

    if (objectp(target))
    {
        target->catch_tell("A torpid Song of Lethargy fills the air, " +
            "slowing your natural tempo slightly.\n");
        if(random(2))
            tell_room(environment(target), QCTPNAME(target)+ " natural " +
            "tempo slows with the lethargic music.\n", ({ target }));
        else if(random(2))
            tell_room(environment(target), QCTPNAME(target)+ " pace " +
            "slows with the lethargic music.\n", ({ target }));
        else
            tell_room(environment(target), QCTNAME(target)+ " looks " +
            "relaxed from the lethargic music.\n", ({ target }));
    }  

    target->add_prop(MINSTREL_LENTO_EFFECT, 1);

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

    target->remove_prop(MINSTREL_LENTO_EFFECT);

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        if(caster != target)
        {
            caster->catch_tell("You notice the lethargy caused by your Song " +
               "of Power leaves " +target->query_the_name(caster)+ ".\n");
            target->catch_tell("You feel the lethargy caused by " +QTPNAME(caster)+
               " Song of Power leave you.\n");
        }
        else
            caster->catch_tell("You feel the lethargy of your Song " +
               "of Power leave you.\n");
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
        caster->catch_tell("Mentally drained, you are unable to maintain " +
           "the Song of Lethargy against your enemies.\n");
    }    
}

/*
 * Function:    query_haste_subloc_description
 * Description: When someone examines a person with this spell effect,
 *              they will see whatever is returned by this function.
 */
public string
query_haste_subloc_description(object on, object for_obj)
{
    if (for_obj == on)
        return  "You are moving more lethargically than usual.\n";
    else
        return capitalize(on->query_pronoun()) + " is moving lethargically.\n";
}
