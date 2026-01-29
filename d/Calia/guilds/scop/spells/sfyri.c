/*
 * sfyri.c
 *
 * Sfyri (Spiritual Hammer) spell for the Spirit Circle of Psuchae
 *
 * This spell bears no resemblance to Jaacar's original spell. This
 * spell creates an actual hammer that is a holdable object and can
 * be thrown in combat by the caster. All the interesting code is in
 * the spell object, here we just do setup.
 * Bishop, May 2004.
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
    return "Master";
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object* targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object* targets, string argument)
{   
    if (caster == 0)
    {
        set_spell_name("sfyri");
        set_spell_desc("Spiritual Hammer");
        set_spell_element(SS_ELEMENT_SPIRIT, 50);
        set_spell_form(SS_FORM_CONJURATION,30);
        set_spell_task(TASK_ROUTINE);
        set_spell_ingredients(({"_sfyri_component_", "_leftover_rib"}));
        set_spell_target(spell_target_caster);
        set_spell_target_verify(spell_verify_present);
        set_spell_object(SPIRIT_SPELLS + "sfyri_obj");
        set_spell_mana(192);
        set_spell_time(6);
        set_spell_vocal(0);
        set_spell_offensive(0);
        set_spell_peaceful(1);
        set_spell_stationary(1);
    
        add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
     }
    else
    {
        if (caster->query_intoxicated())
        {
            caster->catch_tell("You cannot use Psuchae's gifts " +
                               "while intoxicated!\n");
            return 1;
        }
        if (caster->query_alignment() < 0)
        {
            caster->catch_tell("You cannot use Psuchae's gifts " +
                               "while you are not good aligned.\n");
            return 1;
        }
  
        if (objectp(present("_sfyri_hammer_", caster)))
        {
            caster->catch_tell("You already have a spiritual hammer!\n");
            return 1;
        }
    }
    return 0;
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
    object hammer;

    caster->catch_tell("Completing the Sfyri conjuration, you " +
                       "call upon Psuchae to bequeath a hammer " +
                       "of spirit upon you. The air in front of " +
                       "you quivers, and a shadowy nexus springs " +
                       "into being. Your hand guided by your deity, " +
                       "you reach within the nexus, pulling forth " +
                       "a dull grey hammer! The nexus collapses as " +
                       "soon as you withdraw your hand.\n");
    caster->catch_tell("If you want to return the hammer to Psuchae, " +
                       "do <hammerdispel>.\n");

    tell_room(environment(caster), QCTNAME(caster) + " completes the " +
              "spell, " + caster->query_possessive() + 
              " eyes expectant. The air in front of " +
              caster->query_objective() + " quivers, a shadowy " +
              "nexus springing into being! Exultant, " +
              QTNAME(caster) + " reaches within the nexus, " +
              "pulling forth a dull grey hammer. The nexus " +
              "collapses as soon as " + caster->query_pronoun() +
              " withdraws " + caster->query_possessive() +
              " hand.\n", caster);
    setuid();
    seteuid(getuid());
    hammer = make_spell_effect_object(query_spell_object(), caster, caster, 
                                      resist[0], result);
    hammer->move(caster, 1);
}
