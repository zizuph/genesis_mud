#pragma strict_types
#pragma save_binary

#include "../../morgulmage.h"

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

inherit "/d/Genesis/specials/std/spells/obj/delayedtrigger_sh";

#define _NO_PREP_TIME_ADJUSTMENT
#include "../generic_functions.c"

int already_hit = 0;

public void initialize_shadow(object spell_object, mapping spell_input)
{
    spell_object->set_spell_effect_desc("gorothnatha");
    spell_object->set_short("Dread Bite");
    spell_object->set_maintain_mana(0);
    
    int power = spell_object->query_spell_effect_power();
    // Power determines how long the spell lasts
    int duration = ftoi(log(itof(power)) * 300.0);
    spell_object->set_dispel_time(duration);
    
    set_trigger_spell_filename(MORGUL_SPELL_DIR + "gorothnatha_harm");
    set_resolve_spell_parameters(spell_input["caster"], spell_input["targets"], 
        spell_input["resist"], spell_input["result"]);
}

public varargs mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
{
    // First call the default hit_me and get the results.
    mixed hitme_results = shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);

    // Ignore dodge and parry
    if (sizeof(hitme_results) && (hitme_results[0] < 0)) {
        return hitme_results;
    }

    if (!already_hit) {
        already_hit = 1;
        
        shadow_who->add_prop(MORGUL_M_GOROTHNATHA_DATA, ([
                "wcpen" : wcpen,
                "dt" : dt,
                "attacker" : attacker,
                "attack_id" : attack_id,
                "target_hitloc" : target_hitloc
            ]));

        query_trigger_spell_filename()->teleledningsanka();
        mixed resists = find_object(query_trigger_spell_filename())->use_spell_resist(
            stored_inputs["caster"], attacker, "gorothnatha");

        set_resolve_spell_parameters(stored_inputs["caster"], ({ attacker }), 
            ({ resists }), stored_inputs["result"]);

        set_alarm(0.0, 0.0, &invoke_triggered_spell(query_trigger_spell_filename()));
    }
        
    return hitme_results;
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Dark powers seem to swirl around"
            + " you, awaiting some final stroke.\n");
        can_see_caster(target)->catch_msg(QCTNAME(target) + " seems suddenly"
            + " at the center of swirling dark powers which await some"
            + " final stroke.\n", target);
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target) && !already_hit)
    {
        target->catch_tell("Having no focus for their energies, the dark"
          + " powers fly out from you and disperse.\n");
        can_see_caster(target)->catch_msg(QCTNAME(target) + " is released "
            + "from the dark powers, which seem to have found no focus for"
            + " their energies.\n", target);
    }
}

/*
 * Function:    hook_spell_effect_warn_fading
 * Description: Override this to customize the message for when
 *              the effect has only a minute left.
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();
    
    if (objectp(target))
    {
        target->catch_tell("You sense a dangerous instability beginning to"
          + " form in the dark powers which swirl about you!\n");
    }
}

/* 
 * Function:    hook_spell_effect_not_maintained
 * Description: Override this to describe the effect when the caster
 *              cannot maintain the effect.
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();
    
    if (objectp(caster))
    {
        caster->catch_tell("Your mind exhausted, you find yourself"
          + " unable to match the demands of the dark powers which"
          + " swirl about you!\n");
    }
}

