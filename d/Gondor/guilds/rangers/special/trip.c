/*
 * Ranger Trip
 *
 * This ability emulates the old ranger trip, which stuns the opponent.
 * It uses the standard stun library.
 *
 * Written by Zizuph, Dec 2021.
 *
 */

#pragma strict_types

#include "/d/Genesis/specials/local.h"
#include "../rangers.h"
#include "/d/Gondor/defs.h"
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>

inherit COMBAT_ABILITY_LIB;
inherit "/d/Gondor/guilds/rangers/special/targetting";

public void
config_ability()
{
    ::config_ability();

    set_ability_name("trip");
    // Combat aid as defined by stub_obj_base
    set_ability_combat_aid(RANGER_MAJOR_CAID);
    set_ability_hit(BRAWL_TOHIT);
    set_ability_stats(BRAWL_STATS);
    set_ability_skills(BRAWL_SKILLS);

    set_ability_offensive(1);

    // Allow the brawl itself to start the fight.
    set_ability_attack_during_prep(0);
    set_ability_prep_time(BRAWL_PREP);
    set_ability_cooldown_time(BRAWL_COOLDOWN);
    set_ability_target(target_one_present_unbrawled_enemy);
    set_ability_target_verify(verify_present_or_enemy);
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
    
    set_ability_group(RANGER_MAJOR_GROUP);
}

void
ability_msg(object actor, mixed * targets, string arg)
{
    actor->catch_msg(
        "You try to get a chance to trip " +
        COMPOSITE_LIVE(targets) + ".\n"
    );
}

/*
 * Function:    attack_targets
 * Description: Called when using an offensive ability. Does the
 *              actual work of attacking each of the targets. Ensures
 *              that the fight actually begins.
 *              Override so that we don't switch targets for blind.
 *              Taken from Ckrik's work on plexus.
 */
public void
attack_targets(object actor, mixed * targets)
{
    attack_new_targets(actor, targets);
}

public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    if (caster->query_ranger_has_virtues())
    {
        switch (caster->query_ranger_major_virtue())
        {
            case RANGER_MAJOR_VIRTUE_HAND_OF_THE_KING:
            case RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_SHADOW:
            case RANGER_MAJOR_VIRTUE_SENTINEL_OF_IMLADRIS:
            case RANGER_MAJOR_VIRTUE_DAUNTLESS_GUARDIAN:
            case RANGER_MAJOR_VIRTUE_DEFENDER_OF_OSGILIATH:
                break;
            case RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_EAST:
            case RANGER_MAJOR_VIRTUE_OLD_HATRED:
            default:
                caster->catch_msg("This type of brawl is unavailable to you.\n");
                return 0;
        }
    }
    if (!sizeof(targets))
    {
        caster->catch_msg("Your target is no longer available.\n");
        return 0;
    }    
    foreach (object target : targets)
    {
       int caster_volume = caster->query_prop(OBJ_I_VOLUME);
       int target_volume = target->query_prop(OBJ_I_VOLUME);
       if (caster_volume > 0 && target_volume / caster_volume > 5)
       {
           caster->catch_msg("Your target is too large for you to trip.\n");
           return 0;
       }
       if (target_volume > 0 && caster_volume / target_volume > 5)
       {
           caster->catch_msg("Your target is too small for you to trip.\n");
           return 0;
       }
    }
    
    foreach(object effect : targets[0]->query_disable_attack_effects())
    {
        if (effect->query_effect_caster() == caster && execute)
        {
            caster->catch_msg("Your target is already disarmed by you.\n");
            return 0;
        }
    }
    foreach(object effect : targets[0]->query_blind_effects())
    {
        if (effect->query_effect_caster() == caster && execute)
        {
            caster->catch_msg("Your target is already blinded by you.\n");
            return 0;
        }
    }
    
    return 1;
}


void trip_message(int result, object actor, object target)
{
    if (result <= 0)
    {
        target->catch_msg(actor->query_The_name(target) + " tries " +
            "to trip you, but you manage to avoid it!\n");
        write("You try to trip " + target->query_the_name(actor) +
            ", but " + target->query_pronoun() + " manages to avoid it!\n");
    }    
    // This means we did hit normally.
    // Message is reported in trip_ob.c
}

public void
resolve_combat_special(object actor, object target, int hitloc,
    int random_hitloc, int pen, int damage_type, mixed * items,
    int resist, int result)
{
    object trip_ob;
    int combat_aid;

    trip_message(result, actor, target);

    if (result > 0)
    {
        trip_ob = clone_object(RANGERS_SPECIAL_OBJ + "trip_ob");
        trip_ob->set_blind_cycle_time(BRAWL_CYCLE_TIME);

        combat_aid = query_ability_combat_aid();

        if (!actor->query_npc())
        {
            // NPCs don't generally have guild stat, so we don't limit
            // their abilities by guildstat.
            combat_aid = query_guildstat_modifier(actor, combat_aid);
        }
        trip_ob->set_stun_tohit(query_ability_hit());
        trip_ob->set_effect_stats(BRAWL_STATS);
        trip_ob->set_effect_skills(BRAWL_SKILLS);
        trip_ob->set_stun_chance(100);
        trip_ob->set_stun_combat_aid(combat_aid);
        trip_ob->set_effect_caster(actor);
        trip_ob->set_effect_target(target);
        trip_ob->move(target, 1);
        trip_ob->start();
    }
}

public void
hook_special_complete()
{
    write("You once again feel ready to try a brawl.\n");
}

public void
hook_already_active(object ability)
{
    write("You were already preparing to " + 
        ability->query_ability_name() + ".\n");
}

public void
hook_special_in_cooldown()
{
    write("You do not feel ready to attempt another brawl yet.\n");
}
