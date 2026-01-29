#pragma strict_types

#include "../morgulmage.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include "/d/Gondor/guilds/morgulmage/morgul_corpse.h"

inherit "/d/Genesis/specials/std/spells/harm";

#define _NO_DEFAULT_FAILURE_MESSAGE
#define _NO_DEFAULT_CONCENTRATE_MESSAGE

#define HIM(x)        ((x)->query_objective())
#define HIS(x)  (x)->query_possessive()

#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

#define BASE_COMBAT_AID     140.0
#define NO_DEFENCE_CAID      80.0
#define NO_MORTIRIO_CAID     20.0
#define SPELL_CAID          (BASE_COMBAT_AID + NO_DEFENCE_CAID + NO_MORTIRIO_CAID)

#define DEFENSIVE_SPELL_EFFECTS \
    ({ MORGUL_SPELL_OBJ_DIR + "ringurth", \
       MORGUL_SPELL_OBJ_DIR + "turniawath" })

#define MORTIRIO_SPELL_EFFECTS \
    ({ MORGUL_SPELL_OBJ_DIR + "mortirio" })

#define THUNAUR_LOG ("/d/Gondor/guilds/morgulmage/spells/thunaur_log")

public void
config_harm_spell()
{
    ::config_harm_spell();

    set_spell_name("thunaur");
    set_spell_desc("Channel the molten flames of Sammath Naur");

    // Arman (AoB) - must require at least a vocal or visual requirement.    
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(SPELL_CAID);

    set_spell_form(SS_FORM_CONJURATION, 50);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    
    set_spell_task(TASK_HARD);

    // First granted at Grand Sorcerer
    set_morgul_rank(11);

    // Cast speed isn't influenced by rank.
    set_spell_time_factor(&adjust_time_by_rank(2.5));
}


/*
 * Function:    query_harm_ingredients
 * Description: This function defines what components are required for
 *              this harm spell.
 */
public string *
query_harm_ingredients(object caster)
{
    return ({ "_nennaur_charge", "leftover" });
}

string
query_spell_fail() 
{
    return "A lack of concentration results in failing to summon " +
        "the Fire Breath.\n";
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
    float total_combat_aid = BASE_COMBAT_AID;
    float caid_mod;
    string player_name = this_player()->query_real_name();
    
    if (!caster_is_maintaining_defensive_effects(this_player())) 
    {
        total_combat_aid += NO_DEFENCE_CAID;
    }
    
    if (!caster_is_maintaining_mortirio_effects(this_player())) 
    {
        total_combat_aid += NO_MORTIRIO_CAID;
    }

    // Modify combat aid depending on rank of mage
    // Max caid for this spell granted at Lord Wraith
    caid_mod = (40.0 + min(60.0, 
        (itof(this_player()->query_morgul_level()) * 3.0))) / 100.0;

    total_combat_aid = (total_combat_aid / SPELL_CAID) * caid_mod * 100.0;
        
    return total_combat_aid;

}

void
concentrate_msg(object caster, object *targets, string args)
{
    caster->catch_tell(one_of_list( ({
        "With the power the Dark Lord has bestowed upon you, you summon " +
        "the Fire Breath!\n",
        "With the power of the Dark Lord flowing through you, you call " +
        "the Fire Breath!\n",
        "The power of the Black Master courses through you as you summon " +
        "the flames of Sammath Naur!\n",
        }) ) );

    can_see_caster(caster)->catch_msg("The foul smell of sulfur fills " +
        "the air as " +QTNAME(caster) + " rasps fell words of conjury.\n");
}

public void
desc_harm_cast(object caster, object *targets)
{
}

public void
desc_harm_damage(object caster, object target, mixed *result)
{
    
    string caster_message, target_message, watcher_message;
    object corpse_sh;

    int phit = result[0];
    string flame, how;
    how = "lick";

    if (phit > 0)
    {
        how = "lick";
    }
    if (phit > 10)
    {
        how = "scorch";
    }
    if (phit > 20)
    {
        how = "burn";
    }
    if (phit > 30)
    {
        how = "wither";
    }
    if (phit > 50)
    {
        how = "shrivel";
    }
    if (phit > 90)
    {
        how = "consume";
    }

    if (result[3] >= 600)
    {
        flame = "fierce white-hot flames";
    }
    else
    {
        flame = "fierce flames";
    }

    caster->catch_tell("You inhale deeply and then spout forth "+
        flame+ " from your mouth. The flames "+ how+ " "+
        target->query_the_name(caster)+ ".\n");
    target->catch_tell(caster->query_The_name(target)+ " inhales "+
        "deeply and then spouts forth "+ flame+ " from "+ HIS(caster)+
        " mouth. The flames "+ how+ " you.\n");
    target->tell_watcher(QCTNAME(caster)+ " inhales deeply and then "+
        "spouts forth "+ flame+ " from "+ HIS(caster)+ " mouth. The "+
        "flames "+ how+ " "+ QTNAME(target)+ ".\n", ({ caster, target }));

    if (objectp( target ) && target->query_hp() <= 0)
    {
        if (random(100) < 50)
        {
            target->catch_tell("You become a living torch!\n");
            tell_room(environment(target), QCTNAME(target) +
                " becomes a living torch!\n", target,
                    this_object());
            target->command("$scream");
            target->run_away();
        }

        corpse_sh = clone_object( MORGUL_DEATH_SHADOW );
        corpse_sh->shadow_me( target );
        corpse_sh->set_death_cause( THUNAUR_CS );
        corpse_sh->set_death_variant( random( THUNAUR_VR ) );
        target->do_die(caster); 
        corpse_sh->remove_shadow();
    }

    // result is in array of:
    //  ({ proc_hurt, hitloc desc, phit, dam, hitloc id })
    int dam = result[3];
    string player_name = caster->query_real_name();
    int caid_mod = ftoi(query_spell_combat_aid_modifier());
    int time_mod = ftoi((100.0 * query_spell_time_factor()));

    send_debug_message("thunaur", capitalize(player_name)
        + " (lvl " +caster->query_morgul_level()+ 
        ") thunaur damage: " +dam+ ", caid mod: " +
        caid_mod + ", % time mod: " +time_mod+ ".", THUNAUR_LOG);
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
