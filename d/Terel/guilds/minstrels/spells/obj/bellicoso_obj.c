/* 
 * Minstrel Bellicoso enemy panic debuff object
 */

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Terel/common/terel_defs.h"
#include "../../guild_defs.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "objs/paranoia_obj";

#define FLEE_FUNC(x)  (F_PANIC_WIMP_LEVEL((x)->query_stat(SS_DIS)) < (x)->query_panic())

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_bellicoso_object_");
    set_short("Minstrel bellicoso song object");    
    set_long("This is the Minstrel bellicoso song object, based on the " +
        "standard paranoia debuff spell's object.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object created by " +
        "the bellicoso song.\n");
    set_spell_effect_desc("song of aggression"); 
    set_spell_effect_notes("This aggressive Song of Power has a chance of " +
        "generating panic in your enemies. Up to three enemies are " +
        "affected by this Song of Power. It should be noted that the panic " +
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
   
    int duration = ftoi(itof(power)) / 10; 
    set_dispel_time(duration);
    return result;
}

/*
 * Function:    query_paranoia_effect_interval
 * Description: Returns the time before the next paranoia effect should happen.
 */
public float
query_paranoia_effect_interval()
{
    return 5.0 + itof(random(10));
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
        target->catch_tell("The sounds around you make you feel very uneasy.\n");
        tell_room(environment(target), QCTNAME(target)+ " looks " +
            "uneasy at the sound of the Song of Aggression.\n", ({ target }));
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
    object caster = query_effect_caster();

    if(target->query_ghost())
        return;

    if (objectp(target))
    {
        if(caster != target)
        {
            caster->catch_tell("You cease performing your Song " +
               "of Aggression against " +target->query_the_name()+ ".\n");
            target->catch_tell("You feel the uneasiness caused by " +QTPNAME(caster)+
               " Song of Power leave you as " +caster->query_possessive()+ 
               "performance ceases.\n");
        }
        else
            caster->catch_tell("You feel the uneasiness of your Song " +
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
           "the Song of Aggression against your enemies.\n");
    }    
}

/*
 * Function    : hook_do_paranoid_effect
 * Description : Function to be overridden to provide specific paranoia messages.
 * Arguments   : object caster - The person responsible for the paranoid, can be 0.
 *             : object target - The person being paranoid.
 *             : mixed * history - Historical context of the previous paranoid
 *                                 effects already experienced. Can help to 
 *                                 determine the next effect.
 */
public void
hook_do_paranoid_effect(object caster, object target, mixed * history)
{
    // max of 50-200 panic generated per tick (progressively gets bigger)
    int amount = min(50, max(1, (query_spell_effect_power() / 8)));

    // DEBUG("amount: " +amount+ ".");
    // DEBUG("spell power: " +query_spell_effect_power()+ ".");
 
    // We update the history
    if (!pointerp(history))
    {
        history = ({ 1 });
    }
    else
    {
        history = ({ history[0] + 1 }) + history;
    }
    
    if (objectp(target))
    {
        switch (history[0] % 20)
        {
        case 0..1:
            target->catch_msg("You feel more uneasy.\n");
            tell_room(environment(target), QCTNAME(target)+ " looks " +
              "uneasy.\n", ({ target }));
            target->add_panic(amount);
            if(FLEE_FUNC(target))
                target->run_away();
            break;

        case 2..3:
            target->catch_msg("You feel very uneasy.\n");
            tell_room(environment(target), QCTNAME(target)+ " looks " +
              "very uneasy.\n", ({ target }));
            target->add_panic(amount * 2);
            if(FLEE_FUNC(target))
                target->run_away();
            break;

        case 4..5:
            target->catch_msg("You feel a bit panicky.\n");
            tell_room(environment(target), QCTNAME(target)+ " looks " +
              "a bit panicky.\n", ({ target }));
            target->add_panic(amount * 3);
            if(FLEE_FUNC(target))
                target->run_away();
            break;
        
        default:
            target->catch_msg("You begin feeling very panicky.\n");
            tell_room(environment(target), QCTNAME(target)+ " is " +
               "looking very panicky.\n", ({ target }));
            target->add_panic((amount * 4));
            if(FLEE_FUNC(target))
                target->run_away();
            break;
        }
    }
    
    // Set the next paranoia effect alarm
    paranoid_effect_alarm =
        set_alarm(query_paranoia_effect_interval(),
                  0.0,
                  &hook_do_paranoid_effect(query_effect_caster(),
                                           query_effect_target(),
                                           history));    
}
