#pragma strict_types

#include "../morgulmage.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Gondor/guilds/morgulmage/morgul_corpse.h"
// #include "/d/Genesis/specials/debugger/debugger_tell.h"

inherit "/d/Genesis/specials/std/spells/harm";

#define _NO_DEFAULT_FAILURE_MESSAGE
#define _NO_DEFAULT_CONCENTRATE_MESSAGE

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

#define BASE_COMBAT_AID     120.0
#define NO_NARO_CAID        55.0
#define NO_FEAR_CAID        50.0
#define NO_MORTIRIO_CAID    20.0
#define SPELL_CAID          (BASE_COMBAT_AID + NO_NARO_CAID + NO_FEAR_CAID + NO_MORTIRIO_CAID)

#define FEAR_SPELL_EFFECTS \
    ({ MORGUL_SPELL_OBJ_DIR + "faugoroth" })

#define NARO_SPELL_EFFECTS \
    ({ MORGUL_SPELL_OBJ_DIR + "naro_drego_obj" })

#define MORTIRIO_SPELL_EFFECTS \
    ({ MORGUL_SPELL_OBJ_DIR + "mortirio" })

#define MORTHUL_LOG ("/d/Gondor/guilds/morgulmage/spells/morthul_log")

public void
config_harm_spell()
{
    ::config_harm_spell();

    set_spell_name("morthul");
    set_spell_desc("Damage your opponent with the Black Breath");

    // Arman (AoB) - must require at least a vocal or visual requirement.    
    set_spell_vocal(0);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(SPELL_CAID);

    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_element(SS_ELEMENT_DEATH, 20);
    
    set_spell_task(TASK_DIFFICULT);

    set_morgul_rank(13);

    set_spell_time_factor(&adjust_time_by_rank(1.5));
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    return ({ "_morgurth_charge", "leftover" });
}

string
query_spell_fail() 
{
    return "A lack of concentration forces you to choke on your fell breath.\n";
}

public int
query_ability_offensive(object *targets)
{
    if (targets[0]->has_undead_shadow()) return 0;
    return 1;
}

private int
caster_is_maintaining_fear_effects(object caster)
{
    object enemy = caster->query_attack();
    object *target;
    string name = caster->query_real_name();

    if (sizeof(target = filter(enemy->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_faugoroth_stun())))
    {   
        return 1;
    }
    else
    {
        return 0;
    }
}

private int
caster_is_maintaining_naro_effects(object caster)
{
    // Currently only checks for drego nin.. need to check for 
    // maetho and libo makil
    return query_has_maintained_spell_effect(caster, NARO_SPELL_EFFECTS);
}

private int
caster_is_maintaining_mortirio_effects(object caster)
{
    return query_has_maintained_spell_effect(caster, MORTIRIO_SPELL_EFFECTS);
}
    
float
query_spell_combat_aid_modifier()
{
    float total_combat_aid = BASE_COMBAT_AID;
    string player_name = this_player()->query_real_name();
    
    if (!caster_is_maintaining_fear_effects(this_player())) 
    {
        total_combat_aid += NO_FEAR_CAID;
    }
    
    if (!caster_is_maintaining_naro_effects(this_player())) 
    {
        total_combat_aid += NO_NARO_CAID;
    }

    if (!caster_is_maintaining_mortirio_effects(this_player())) 
    {
        total_combat_aid += NO_MORTIRIO_CAID;
    }
        
    return (total_combat_aid / SPELL_CAID) * 100.0;
}

void
concentrate_msg(object caster, object *targets, string args)
{
    caster->catch_tell("You delve deeply into the powers given you by the "
        + "Father of Gifts. With a sharp intake of breath, you prepare to "
        + "invoke Morthul!\n");

    can_see_caster(caster)->catch_msg("The air around you seems to "
        + "stiflingly thicken as " + QTNAME(caster) + " inhales deeply, "
        + "causing you to gasp for breath.\n");
}

private void
desc_harm_cast_normal(object caster, object target)
{
    caster->catch_tell("You quickly snatch " + target->query_the_name(caster)
        + " by the throat with a powerful, crushing grip and pull "
        + target->query_objective() + " closer to your gaping maw.\n"
        + "With a malicious bellow, you turn in the direction of "
        + target->query_the_name(caster) + " and spew forth "
        + "from the bowels of Mordor a wretched Black Breath.\n");
        
    target->catch_tell(caster->query_The_name(target) + " gestures "
        + "quickly in your direction. Suddenly you find yourself being "
        + "pulled forward, inescapably bound by " + caster->query_possessive() 
        + " grip.\n"
        + caster->query_The_name(target) + " disgourges copious amounts of "
        + "noxious fumes from beneath " + caster->query_possessive() 
        + " a black hood, hitting you directly in the face.\n");
}

private void
desc_harm_cast_member(object caster, object target)
{
    if (IS_APPRENTICE(target) && !IS_APPRENTICE(caster))
    {
        caster->catch_tell("You violently grab " 
            + target->query_the_possessive_name(target) + " throat, drawing "
            + target->query_objective() + " to you. You devote but a single "
            + "dark wisp of caustic fumes from your lifeless lungs and note "
            + "that the effects of your gift are not restoratively "
            + "insignificant.\n");
        
        target->catch_tell("You suddenly feel choked with a devastating grip. "
            + caster->query_The_name(target) + " bellows at you with a fell "
            + "breath.  As the swirling fumes envelop you, you sense a "
            + "rejuvenating feeling befall you.\n");
    }
    else
    {
        int caster_level = caster->query_morgul_level(-1);
        int target_level = target->query_morgul_level(-1);
    
        if (target_level >= caster_level)
	{
            caster->catch_tell("You send forth a steady gale of fell breath "
                + "at " + target->query_the_name(caster) + ", rejuvinating "
                + target->query_objective() + " with the gift of your "
                + "Master.\n");
            
            target->catch_tell(caster->query_The_name(target) + " raises "
                + caster->query_possessive() + " face close to yours and "
                + "blows a fell, restorative breath into your face.\n");
        }
	else
	{
            caster->catch_tell("You grab " 
                + target->query_the_possessive_name(target) + " throat, "
                + "drawing " + target->query_objective() + " to you and "
                + "deigning to grant " + target->query_objective() + " the "
                + "power of your fell restorative breath.\n");
                
            target->catch_tell("A powerful, cold hand grasps you by the "
                + "throat as " + caster->query_the_name(target) + " draws "
                + "you closer, blowing " + caster->query_possessive() 
                + " fell breath into your face.\n");
        }
    }
}

private void
desc_harm_cast_undead(object caster, object target)
{
    caster->catch_tell("You seize " + target->query_the_name(caster) 
        + " by the throat and feel the malice and contempt for "
        + "all life bubble in your belly. As the caustic fumes of Mordor "
        + "exit your lungs and envelop " + target->query_the_name() + ", "
        + target->query_pronoun() + " seems to stand a little "
        + "firmer under your grasp.\n");

    target->catch_tell("A powerful, cold hand grasps you by the "
        + "throat as " + caster->query_the_name(target) + " draws "
        + "you closer, blowing " + caster->query_possessive() 
        + " fell breath into your face.\n");
}

private void
desc_harm_cast_watcher(object caster, object target)
{
    caster->tell_watcher("With unnatural speed, " + QTNAME(caster)
        + " grabs " + QTNAME(target) + " by the throat pulling "
        + target->query_objective() + " uncomfortably close.\n"
        + QCTNAME(target) + " turns even more pallid as " + QTNAME(caster)
        + " encompasses " + target->query_objective() + " with a relentless "
        + "barage of strangling breath.\n", target, ({ caster, target }));
}

private void
desc_harm_cast_tall(object caster, object target)
{
    caster->catch_tell("With a sharp gaze and a soft, alluring whisper, "
        + "you force " + target->query_the_name(caster) + " to lower "
        + target->query_possessive() + " head to your level in fell "
        + "acceptance of the inevitable.\n"
        + "With a malicious grin, you spit your terrible breath into "
        + target->query_the_possessive_name(caster) 
        + " petrified face.\n");

    target->catch_tell("A feeling of listenessness befalls you as "
        + caster->query_the_name(target) + " whispers something inaudible "
        + "in your direction. You struggle helplessly as your head lowers "
        + "to meet " + caster->query_possessive() + " gaze. \n"
        + caster->query_The_name(target) + " grins maliciously and suddenly "
        + "you find yourself choked by " + caster->query_possessive() 
        + " blinding, defiling, dreadful breath.\n");
}

private void
desc_harm_cast_tall_watcher(object caster, object target)
{
    caster->tell_watcher("The heaviness of the air around you increases "
        + "as you hear " + QTNAME(caster) + " whisper something in the "
		+ "direction of " + QTNAME(target) + ".\n"
        + "Helpless to resist, " + QTNAME(target) 
        + " lowers " + target->query_possessive() + " head to meet the "
	    + "gaze of " + QTNAME(caster) + " and is violently choked by a "
        + "cloud of "+ caster->query_possessive() + " ghastly breath.\n" 
        , target, ({ caster, target }));
} 

public void
desc_harm_cast(object caster, object *targets)
{
    if (!sizeof(targets)) return;
    
    object target = targets[0];
    int target_to_tall = target->query_prop(CONT_I_HEIGHT) > 
        ftoi(1.3 * itof(caster->query_prop(CONT_I_HEIGHT)));
        
    if (target->has_undead_shadow() && IS_MEMBER(target))
    {
        desc_harm_cast_member(caster, target);
        desc_harm_cast_watcher(caster, target);
    }
    else if (target->has_undead_shadow())
    {
        desc_harm_cast_undead(caster, target);
        desc_harm_cast_watcher(caster, target);
    }
    else if (target_to_tall)
    {
        desc_harm_cast_tall(caster, target);
        desc_harm_cast_tall_watcher(caster, target);
    }
    else
    {
        desc_harm_cast_normal(caster, target);
        desc_harm_cast_watcher(caster, target);
    }
}

private string describe_damage(int percentage)
{
    switch(percentage)
    {
        case   0..3: return "barely hurt";
        case   4..8: return "slightly hurt";
        case  9..15: return "somewhat hurt";
        case 16..25: return "rather hurt";
        case 26..40: return "hurt";
        case 41..65: return "very hurt";
        default    : return "extremely hurt";
     
    }
}

public void
desc_harm_damage(object caster, object target, mixed *result)
{
    if (target->has_undead_shadow()) return;
    
    string how = describe_damage(result[0]);
    object corpse_sh;

    target->catch_tell("You feel " + how + ".\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
        how + ".\n");
    caster->tell_watcher(QCTNAME(target) + " appears " + how + ".\n",
        target, ({ caster, target }));

    if (objectp( target ) && target->query_hp() <= 0)
    {
        corpse_sh = clone_object( MORGUL_DEATH_SHADOW );
        corpse_sh->shadow_me( target );
        corpse_sh->set_death_cause( MORTHUL_CS );
        corpse_sh->set_death_variant( random( MORTHUL_VR ) );
        target->do_die(caster); 
        corpse_sh->remove_shadow();
    }

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int dam = result[3];
    string player_name = caster->query_real_name();
    int caid_mod = ftoi(query_spell_combat_aid_modifier());
    int time_mod = ftoi((100.0 * query_spell_time_factor()));

    send_debug_message("morthul", capitalize(player_name)
        + " morthul damage: " +dam+ ", caid mod: " +
        caid_mod + ", % time mod: " +time_mod+ ".", MORTHUL_LOG);
}

/*
 * Function:    resolve_harm_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
    MORGUL_MASTER->increase_activity(caster, ACTIVITY_COMBAT_SPELL);
}
