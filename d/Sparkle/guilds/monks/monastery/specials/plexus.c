/*
 * Monk Plexus
 *  
 * Combat descriptions lifted from original Monk
 * special combat code by Arandir.
 *
 * Created by Ckrik, June 2016
 *
 * Ckrik Aug 2021 - fixed bug with stun length adjustment due to stun
 *      length not properly adjusting for the cb_tohit() odds.
 */

#pragma strict_types

#include "defs.h"

inherit COMBAT_SPECIAL_LIB;
inherit M_PLAYER_LIBS;
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <language.h>

#include "/std/combat/combat.h"

// Prototypes
public void config_ability();
void plexus_message(int iHitsuc, object oActor,
    object oTarget, object oArmour, int iArmourClass);
public void report_resolve_ability(int hitsuc,
    int combat_aid, int stun_pct);

// Defines
#define PLEXUS_OBJ  (MONK_SPECIALS + "plexus_obj")
#ifndef LIVE_I_NO_SPECIAL_PLEXUS
#define LIVE_I_NO_SPECIAL_PLEXUS "_live_i_no_special_plexus"
#endif

int filter_not_stunned(object victim)
{
    return !victim->query_is_stunned() && !victim->query_in_cooldown();
}

int filter_valid_target(object victim)
{
    int *hit_locs;
    mixed *hit_desc;
    if (victim->query_humanoid())
    {
        return 1;
    }

    // Not humanoid, so we look for a body
    hit_locs = victim->query_combat_object()->query_hitloc_id();
    foreach (int hit_loc : hit_locs)
    {
        hit_desc = victim->query_combat_object()->query_hitloc(hit_loc);
        if (hit_desc[2] == "body")
        {
            return 1;
        }
    }

    // No body, so no plexus
    return 0;
}

/*
 * Function:    attack_targets
 * Description: Called when using an offensive ability. Does the
 *              actual work of attacking each of the targets. Ensures
 *              that the fight actually begins.
 *              Override so that we don't switch targets for plexus
 */
public void
attack_targets(object actor, mixed * targets)
{
    object * target_objects = ({ });
    foreach (mixed target : targets)
    {
        object ob;
        if (objectp(target))
        {
            ob = target;
        }
        if (pointerp(target))
        {
            ob = target[0];
        }
        if (!objectp(ob))
        {
            continue;
        }
        
        target_objects += ({ ob });
    }
    
    if (!sizeof(target_objects))
    {
        return;
    }
    
    // We want to make sure we attack any new targets. Existing
    // targets in the room should not be re-attacked as it may
    // lead to strange behaviors for multi-target attacks
    object * current_enemies = actor->query_enemy(-1);
    object * current_enemies_in_room = ({ });
    foreach (object enemy : current_enemies)
    {
        if (environment(actor) == environment(enemy))
        {
            current_enemies_in_room += ({ enemy });
        }
    }
        
    foreach (object ob : target_objects)
    {    
        if (!IN_ARRAY(ob, current_enemies_in_room))
        {
            hook_attack_object(ob);
            actor->attack_object(ob);
        }

        if (!IN_ARRAY(actor, ob->query_enemy(-1)))
        {
            ob->attacked_by(actor);
        }            
    }    
}

public object *
target_one_other_present_living_or_one_random_not_stunned_enemy(object actor, string str)
{
    // Target single specific living
    if (strlen(str))
    {
        object *oblist = PARSE_THIS(str, "[at] / [on] [the] %l");

        if (!sizeof(oblist))
        {
            actor->catch_tell("Whom do you wish to target?\n");
            return ({});
        }

        if (sizeof(oblist) > 1)
        {
            actor->catch_tell("You will have to be more specific!  You can only " +
                "select one target.\n");
            return ({});
        }

        if (!filter_valid_target(oblist[0]))
        {
            actor->catch_tell("You cannot find a location on your target to " +
                "execute a plexus.\n");
            return ({});
        }

        return oblist;
    }

    // Check if primary enemy is eligible for plexus
    object currently_attacking = actor->query_attack();
    if (objectp(currently_attacking) && filter_not_stunned(currently_attacking) &&
        filter_valid_target(currently_attacking))
    {
        return ({ currently_attacking });
    }

    // Primary enemy not eligible, so pick another one.
    // Target 1 random not stunned present enemy.
    // If all present enemies are stunned, pick a random present enemy.
    object *enemies = (object *) actor->query_enemy(-1) &
        all_inventory(environment(actor));
    object *valid_enemies = filter(enemies, filter_valid_target);
    object *not_stunned = filter(valid_enemies, filter_not_stunned);
    if (sizeof(not_stunned) > 0)
    {
        int r = random(sizeof(not_stunned));
        object target = not_stunned[r];
        return ({ target });
    }
    else if (sizeof(valid_enemies) > 0)
    {
        int r = random(sizeof(enemies));
        object target = enemies[r];
        return ({ target });
    }

    // No valid target
    actor->catch_tell("Whom do you wish to target?\n");
    return ({});
}
/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : none
 * Returns      : nothing
 */
public void 
config_ability()
{
    ::config_ability();

    set_ability_name("mplexus");
    // Combat aid as defined by stub_obj_base
    set_combat_aid(M_PLEXUS_AID);
    set_tohit(M_PLEXUS_HIT);
    set_skills(({ M_SKILL_PLEXUS }) );

    set_ability_offensive(1);
    set_ability_visual(0);
    set_ability_allow_hunting(1);
    set_ability_prep_time(5);
    set_ability_cooldown_time(5);
    set_ability_target(target_one_other_present_living_or_one_random_not_stunned_enemy);
    set_ability_target_verify(verify_present_or_enemy);
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
}

/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
public void
apply_costs_to_player(object player)
{
    // We override the fatigue cost from 2 to 1 because
    // Monks have 2 fast acting specials.
    player->add_fatigue(-1);
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    if (targets[0]->query_humanoid())
    {
        actor->catch_msg(
            "You try to get a chance to hit " +
            QTNAME(targets[0]) +
            " in the solar plexus.\n"
        );
    }
    else
    {
        actor->catch_msg(
            "You try to get a chance to land " +
            "a plexus attack on " +
            QTNAME(targets[0]) +
            " in the body.\n"
        );   
    }
}

public void
resolve_combat_special(object actor, object target, int hitloc,
   int random_hitloc, int pen, int damage_type,
   mixed * items, int result)
{
    object oArmour, oWhom, oStun;
    int iArmourClass, iHitsuc, iStunPct,
        iCombatAid;

    oWhom = target;

    if (oWhom->query_humanoid())
    {
        oArmour = oWhom->query_armour(TS_TORSO);
        if (objectp(oArmour)) {
            iArmourClass = oArmour->query_ac();
        } else {
            iArmourClass = 0;
        }
    }
    else
    {
        iArmourClass = 0;
    }
    iHitsuc = result;
    iStunPct = 0;
    if (iHitsuc > 0)
    {
        oStun = clone_object(M_PATH_SPECIALS + "/plexus_obj");
        oStun->set_stun_cycle_time(M_PLEXUS_TIME);
        
        iCombatAid = query_combat_aid();
        
        if (!actor->query_npc())
        {
            // NPCs don't generally have guild stat, so we don't limit
            // their abilities by guildstat.
            iCombatAid = calc_guildstat_modifier(actor, iCombatAid);
        }
        oStun->set_stun_chance(100);
        oStun->set_stun_hit(query_tohit());
        oStun->set_stun_skills(query_skills());
        oStun->set_stun_combat_aid(iCombatAid);
        oStun->set_effect_caster(actor);
        oStun->set_effect_target(oWhom);
        oStun->move(oWhom, 1);
        oStun->start();

        iStunPct = oStun->query_stun_percentage(actor);
    }

    plexus_message(iHitsuc, actor, oWhom, oArmour, iArmourClass);

    report_resolve_ability(iHitsuc, iCombatAid, iStunPct);
}

public void
hook_special_complete()
{
    write("You feel ready to hit someone with a plexus attack again.\n");
}

public void
hook_already_active(object ability)
{
    write("You are already preparing a plexus attack!\n");
}

public void
hook_special_in_cooldown()
{
    write("You cannot hit someone with a plexus attack again so soon.\n");
}

void plexus_message(int iHitsuc, object oActor, object oTarget,
    object oArmour, int iArmourClass)
{
    if (iHitsuc < -5)
    {
        // This is a complete miss ...
        if (oTarget->query_humanoid())
        {
            oActor->catch_msg("You aim your open hand at " + QTNAME(oTarget) +
                ", but " + oTarget->query_pronoun() + " dodges aside.\n");
            oTarget->catch_msg(QCTNAME(oActor) +
                " aims for your solar plexus with " +
                oTarget->query_pronoun() + " open hand, but you dodge aside.\n");
            oTarget->tell_watcher(QCTNAME(oActor) +
                " aims for the solar plexus of " +
                QTNAME(oTarget) + ", but " + oTarget->query_pronoun() +
                " dodges aside.\n",
                oActor);
            return;
        }
        else
        {
            oActor->catch_msg("You aim your open hand at " + QTNAME(oTarget) +
                ", but " + oTarget->query_pronoun() + " dodges aside.\n");
            oTarget->catch_msg(QCTNAME(oActor) +
                " aims for your body with " +
                oTarget->query_pronoun() + " open hand, but you dodge aside.\n");
            oTarget->tell_watcher(QCTNAME(oActor) +
                " aims for the body of " +
                QTNAME(oTarget) + ", but " + oTarget->query_pronoun() +
                " dodges aside.\n",
                oActor);
            return;
        }
    }
    else if (iHitsuc < 0)
    {
        // This is a hit that had no effect ...
        if (iArmourClass > 5)
        {
            // Blame the failed hit on the body armour of the target.
            oActor->catch_msg("You drive your open hand into " +
                QTPNAME(oTarget) + " solar " +
                "plexus, but the force is absorbed by " +
                oTarget->query_possessive() + " " +
                oArmour->query_short() + ".\n");
            oTarget->catch_msg(QCTNAME(oActor) + " drives " +
                oActor->query_possessive() + " open hand into your " +
                "solar plexus, but the force of the blow is " +
                "absorbed by your " + oArmour->query_short() + ".\n");
            oTarget->tell_watcher(QCTNAME(oActor) + " drives " +
                oActor->query_possessive() + " open hand into " +
                QTPNAME(oTarget) + " solar plexus, " +
                "but the force of the " +
                "blow is absorbed by " + oTarget->query_possessive() +
                " " + oArmour->query_short() + ".\n",
                oActor);
            return;
        }
        else
        {
            // No body armour to blame the failed hit on.
            if (oTarget->query_humanoid())
            {
                oActor->catch_msg("You drive your open hand into " + 
                    QTPNAME(oTarget) + " solar " +
                    "plexus, but the blow seems to have no effect.");
                oTarget->catch_msg(QCTNAME(oActor) + " drives " +
                    oActor->query_possessive() + " open hand into " +
                    "your solar plexus, but the blow seems to have " +
                    "no effect.");
                oTarget->tell_watcher(QCTNAME(oActor) + " drives " +
                    oActor->query_possessive() + " open hand into " +
                    QTPNAME(oTarget) + " solar plexus, but the blow " +
                    "seems to have no effect.",
                    oActor);
                return;
            }
            else
            {
                oActor->catch_msg("You drive your open hand into " + 
                    QTPNAME(oTarget) + " body" +
                    ", but the blow seems to have no effect.");
                oTarget->catch_msg(QCTNAME(oActor) + " drives " +
                    oActor->query_possessive() + " open hand into " +
                    "your body, but the blow seems to have " +
                    "no effect.");
                oTarget->tell_watcher(QCTNAME(oActor) + " drives " +
                    oActor->query_possessive() + " open hand into " +
                    QTPNAME(oTarget) + " body, but the blow " +
                    "seems to have no effect.",
                    oActor);
                return;
            }
        }
    }
    // This means we did hit normally ...
    // Message is reported in plexus_obj.c
}

public void
report_resolve_ability(int hitsuc, int combat_aid, int stun_pct)
{
    string name, logfile;
    
    if (interactive(this_player()))
    {
        name = capitalize(this_player()->query_real_name());
    }
    else
    {
        name = MASTER_OB(this_player());
    }

    logfile = implode(explode(MASTER_OB(this_object()), "/")[..-2], "/") + "/";
    logfile += short() + "_stun";
    logfile = implode(explode(logfile, " "), "");
    
    setuid();
    seteuid(getuid());
    
    send_debug_message(short(), 
        name + " hits with hit success of " + hitsuc + ", " +
        "Combat aid of " + combat_aid + ", " +
        "Stun " + stun_pct + " pct out of " +
        M_PLEXUS_TIME + " seconds",
        logfile
    );  
}