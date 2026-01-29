/*
 *   Oneiro (dream walk) spell for the Spirit Circle. 
 *
 *   The spell sets up a paralysis object in the player that does the
 *   work in the spell.
 *
 *   Coded by Bishop of Calia, 
 */
 
 
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/newmagic/spell";
 
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <composite.h>
#include "defs.h"
#include SPIRIT_HEADER
 
string
query_spell_level()
{
    return "Elder";
} 
 

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{   
    if (caster == 0)
    {
        set_spell_name("oneiro");
        set_spell_desc("Dreamwalk");
        set_spell_element(SS_ELEMENT_SPIRIT, 90);
        set_spell_form(SS_FORM_DIVINATION,60);
        set_spell_task(TASK_ROUTINE - caster->query_casting_bonus());
        set_spell_ingredients(({"glittering diamond"}));
        set_spell_target(spell_target_caster);
        set_spell_target_verify(spell_verify_present);
        set_spell_object(SPIRIT_SPELLS + "oneiro_ob");
        set_spell_mana(120);
        set_spell_time(6);
        set_spell_vocal(0);
        set_spell_offensive(0);
        set_spell_peaceful(1);
    
        add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
      
        if (caster->query_intoxicated())
        {
             caster->catch_msg("You cannot use Psuchae's gifts while intoxicated!\n");
             return 1;
        }
        if (caster->query_alignment() < 0)
        {
            caster->catch_msg("You cannot use Psuchae's gifts while you are not "+
                "good aligned.\n");
            return 1;
        }
        return 0;
    }
    else
    {
        if (objectp(present("_skiamorfi_object_", caster)))
        {
            caster->catch_tell("You cannot use this gift while in shadow form.\n");
            return 1;
        }
        return 0;
    }
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */
public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You concentrate on the powers of Psuchae.\n");
    say(QCTNAME(caster) + " appears to be in deep concentration.\n");
}


/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object spellob;

    if (random(100) < resist[0])
    {
        caster->catch_tell("You complete the spell, but it seems to " +
            "have no effect.\n");
        return;
    }


    caster->catch_tell("Completing your casting of Oneiro, you lie down and" +
        " prepare to leave the waking world.\n");
    tell_room(environment(caster), QCTNAME(caster) + " completes " + 
        caster->query_possessive() + " spell and lies down, closing " +
        caster->query_possessive() + " eyes.\n", ({caster}));
    
    setuid();
    seteuid(getuid());
    spellob = make_spell_effect_object(query_spell_object(), caster, caster, 
        resist[0], result);
    spellob->move(caster, 1);    
}

 
   