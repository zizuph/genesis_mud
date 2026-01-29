#pragma strict_types

#include "../morgulmage.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Gondor/guilds/morgulmage/morgul_corpse.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "harm";

#define _NO_DEFAULT_FAILURE_MESSAGE
#define _NO_DEFAULT_CONCENTRATE_MESSAGE

#define HIM(x)        ((x)->query_objective())

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

#define BASE_COMBAT_AID      40.0
#define NO_DEFENCE_CAID      98.0
#define NO_MORTIRIO_CAID     20.0
#define SPELL_CAID          (BASE_COMBAT_AID + NO_DEFENCE_CAID + NO_MORTIRIO_CAID)

#define DEFENSIVE_SPELL_EFFECTS \
    ({ MORGUL_SPELL_OBJ_DIR + "ringurth", \
       MORGUL_SPELL_OBJ_DIR + "turniawath" })

#define MORTIRIO_SPELL_EFFECTS \
    ({ MORGUL_SPELL_OBJ_DIR + "mortirio" })

#define DRAMALGOS_LOG ("/d/Gondor/guilds/morgulmage/spells/dramalgos_log")

public void
config_harm_spell()
{
    ::config_harm_spell();

    set_spell_name("dramalgos");
    set_spell_desc("Summon the dark winds of the East, the Storm Winds");

    // 1 herb per cast.
    set_spell_component_factor(COMPONENT_AID_HIGH);    
    set_spell_combat_aid(SPELL_CAID);

    set_ability_stats(STAT_WEIGHTING);

    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_element(SS_ELEMENT_AIR, 20);

    set_spell_class(SPELL_CLASS_4);    
    set_spell_task(TASK_DIFFICULT);

    // First granted at Master Conjurer
    set_morgul_rank(7);

    // Give a percentage chance of not consuming the leftover.
    set_keep_leftover(1);

    // Cast speed isn't influenced by rank.
    set_spell_time_factor(&adjust_time_by_rank(1.75));
}


/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    return ({ "dramalgos_ingr1", "leftover" });
}

string
query_spell_fail() 
{
    return "A lack of concentration results in the storm winds dissipating.\n";
}

private int
caster_is_maintaining_defensive_effects(object caster)
{
    return query_has_maintained_spell_effect(caster, DEFENSIVE_SPELL_EFFECTS);
}

private int
caster_is_maintaining_mortirio_effects(object caster)
{
    return query_has_maintained_spell_effect(caster, MORTIRIO_SPELL_EFFECTS);
}
    
float
query_spell_combat_aid_modifier()
{
    float total_combat_aid = SPELL_CAID;
    float available_combat_aid = BASE_COMBAT_AID;

    string player_name = this_player()->query_real_name();

    if (query_spell_apply_whitehit_aid())
    {
        total_combat_aid += itof(query_white_hit_combat_aid());
        available_combat_aid += itof(query_white_hit_combat_aid());
    }
    
    if (!caster_is_maintaining_defensive_effects(this_player())) 
    {
        available_combat_aid += NO_DEFENCE_CAID;
    }
    
    if (!caster_is_maintaining_mortirio_effects(this_player())) 
    {
        available_combat_aid += NO_MORTIRIO_CAID;
    }

/*
    send_debug_message("dramalgos", capitalize(player_name) +
        ", rank " +this_player()->query_morgul_level()+ ", total raw caid: " +
            ftoi(total_combat_aid)+ ".\n", DRAMALGOS_LOG);
*/

    // Modify combat aid depending on rank of mage
    // Max caid for this spell granted at Lord Wraith
    float caid_mod = (40.0 + min(60.0, 
        (itof(this_player()->query_morgul_level()) * 3.0))) / 100.0;
    
    return  (available_combat_aid / total_combat_aid) * caid_mod * 100.0;

}

void
concentrate_msg(object caster, object *targets, string args)
{
    caster->catch_tell( one_of_list( ({ 
        "With the power the Dark Lord has bestowed upon you, you call " +
        "the storm winds from the East.\n", 
        "Using the powers the Black Master has bestowed upon you, you " +
        "call the storm winds from the East.\n", 
        "With a touch of the Dark Lord's powers, you call the storm winds.\n", 
        "Feeling the power of the Dark Lord flowing through you, you call " +
        "the storm winds.\n", 
        "The power of the Black Master surges through your undead body as " +
        "you call the storm winds from the East!\n", 
                                          })) );

    can_see_caster(caster)->catch_msg(QCTNAME(caster) + " whispers words " +
        "most fell, and a foul wind begins to stir around " +HIM(caster) + ".\n");
}

public void
desc_harm_cast(object caster, object *targets)
{
    if (!sizeof(targets)) return;

    string caster_message, target_message, watcher_message;    
    object target = targets[0];

    caster_message =  "With a quick gesture you release the storm wind "+
        "against "+ target->query_the_name(caster)+ ".\n";
    target_message = caster->query_The_name( target )+ " makes a low "+
        "whistling noise, then quickly gestures in your direction.\n";
    watcher_message = QCTNAME(caster)+ " makes a low whistling noise, "+
        "then quickly gestures in "+ QTPNAME( target )+ " direction.\n";
    
    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets); 
}

public void
desc_harm_damage(object caster, object target, mixed *result)
{
    object corpse_sh;
    string caster_message, target_message, watcher_message;

    int phit = result[0];
    string how, what, bolt;
    bolt = "a single bolt";
    what = "misses ";
    how = "";

    if (phit > 0)
    {
        what = "strikes ";
    }
    if (phit > 10)
    {
        how = " hard";
    }
    if (phit > 20)
    {
        bolt = "a sharp bolt";
    }
    if (phit > 30)
    {
        bolt = "three small bolts";
        what = "strike ";
        how = "";
    }
    if (phit > 40)
    {
        bolt = "three spear-shaped bolts";
    }
    if (phit > 50)
    {
        what = "slam against ";
    }
    if (phit > 60)
    {
        bolt = "three large spear-shaped bolts";
    }
    if (phit > 70)
    {
        how = ", driving you back";
    }
    if (phit > 80)
    {
        what = "smash ";
        how = " onto the ground";
    }
    if (phit > 90)
    {
        what = "squash ";
        how = " to pulp on the ground";
    }

    watcher_message = capitalize(bolt)+ " of wind "+ what + 
                      target->query_objective()+ how + ".\n";
    target_message = capitalize(bolt)+ " of wind "+ what+ "you"+ how+ ".\n";
        
    caster->catch_msg(watcher_message);
    target->catch_msg(target_message);
    target->tell_watcher(watcher_message, target, ({ caster, target }));

    if (objectp( target ) && target->query_hp() <= 0)
    {
        corpse_sh = clone_object( MORGUL_DEATH_SHADOW );
        corpse_sh->shadow_me( target );
        corpse_sh->set_death_cause( DRAMALGOS_CS );
        corpse_sh->set_death_variant( random( DRAMALGOS_VR ) );
        target->do_die(caster); 
        corpse_sh->remove_shadow();
    }

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int dam = result[3];
    string player_name = caster->query_real_name();
    int caid_mod = ftoi(query_spell_combat_aid_modifier());
    int time_mod = ftoi((100.0 * query_spell_time_factor()));

    send_debug_message("dramalgos", capitalize(player_name)
        + " (lvl " +caster->query_morgul_level()+ 
        ") dramalgos damage: " +dam+ ", caid mod: " +
        caid_mod + ", % time mod: " +time_mod+ ".", DRAMALGOS_LOG);
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
