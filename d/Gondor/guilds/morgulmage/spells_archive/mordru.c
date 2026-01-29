#pragma strict_types

#include "../morgulmage.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
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

#define HIS(x)        ((x)->query_possessive())
#define HIM(x)        ((x)->query_objective())

#define NARO_SPELL_EFFECTS \
    ({ MORGUL_SPELL_OBJ_DIR + "naro_drego_obj" })

#define MORTIRIO_SPELL_EFFECTS \
    ({ MORGUL_SPELL_OBJ_DIR + "mortirio" })

#define MORDRU_LOG ("/d/Gondor/guilds/morgulmage/spells/mordru_log")

public void
config_harm_spell()
{
    ::config_harm_spell();

    set_spell_name("mordru");
    set_spell_desc("Harm your enemy with the phantoms of the Black Dread");
    
    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(SPELL_CAID);

    set_spell_form(SS_FORM_ILLUSION, 40);
    set_spell_element(SS_ELEMENT_DEATH, 40);
    
    set_spell_task(TASK_HARD);

    set_morgul_rank(21);

    set_spell_time_factor(&adjust_time_by_rank(1.5));
    set_spell_resist(&spell_resist_damage_type(MAGIC_I_RES_ILLUSION));
}

/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    return ({ "_naicelum_charge", "leftover" });
}

string
query_spell_fail() 
{
    return "A lack of concentration results in the phantoms of the Black " +
        "Dread to dissipate.\n";
}

private int
caster_using_fear_effects(object caster)
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
    
    if (!caster_using_fear_effects(this_player())) 
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
    object target = targets[0];

    caster->catch_msg("You rise menacingly before " +
        target->query_the_name(caster)+
        ", casting long shadows over " +HIM(target)+ " upon which " +
        "you invoke the terrible Black Dread!\n");
    target->catch_msg(caster->query_The_name(target)+ " rises menacingly, " +
        "casting long shadows over you that agitate unnaturally " +
        "like tormented phantoms.\n");
    target->tell_watcher(QCTNAME(caster)+ " rises menacingly before " +
        QTNAME(target)+ ", casting long shadows around " +HIM(target)+
        " that agitate unnaturally like tormented phantoms.\n", target, 
        ({ caster, target }));

}

public void
desc_harm_cast(object caster, object *targets)
{
    if (!sizeof(targets)) return;
    
    string caster_message, target_message, watcher_message;    
    object target = targets[0];

    caster_message =  "You shriek 'Badzurz Mor Doraz Ob Dru!' and the " +
        "shadows answer your call, swarming "+ target->query_the_name(caster)+ 
        " and rending " +HIS(target)+ " mind with doom and darkness.\n";
    target_message = caster->query_The_possessive_name( target )+ " piercing "+
        "shriek of invocation is answered by the shadows, " +
        "engulfing you hungrily and rending your mind with darkness " +
        "and doom.\n";
    watcher_message = QCTPNAME(caster)+ " piercing shriek of invocation is " +
        "answered by the shadows, engulfing " +QTNAME(target)+ 
        " with dark phantoms that rend " +HIS(target)+ " mind hungrily.\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets); 
}

private string describe_damage(int percentage)
{
    switch(percentage)
    {
        case   0..3: return "undaunted"; 
        case   4..8: return "wrenched"; 
        case  9..15: return "torn"; 
        case 16..25: return "ravaged"; 
        case 26..40: return "desolated"; 
        case 41..65: return "ruined"; 
        default    : return "devoured"; 
     
    }
}

public void
desc_harm_damage(object caster, object target, mixed *result)
{   
    string how = describe_damage(result[0]);

    target->catch_tell("You feel " + how + " by the shadows.\n");
    caster->catch_tell(target->query_The_name(caster) + " appears " +
        how + " by the shadows.\n");
    caster->tell_watcher(QCTNAME(target) + " appears " + how + 
        " by the shadows.\n", target, ({ caster, target }));

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int dam = result[3];
    string player_name = caster->query_real_name();
    int caid_mod = ftoi(query_spell_combat_aid_modifier());
    int time_mod = ftoi((100.0 * query_spell_time_factor()));

    send_debug_message("mordru", capitalize(player_name)
        + " mordru damage: " +dam+ ", caid mod: " +
        caid_mod + ", % time mod: " +time_mod+ ".", MORDRU_LOG);
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
