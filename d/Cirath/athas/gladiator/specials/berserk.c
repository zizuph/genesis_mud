/*
 * /d/Cirath/athas/gladiator/specials/berserk.c
 *
 * This is the berserk ability for Gladiators. This is a port of the
 * ability from the original concept to the new Genesis Specials
 * system.
 *
 * Created by Petros, October 2008
 *
 * Made berserk fatigue-cost neutral. The fatigue you lose at the
 * end of berserk you gain when you start berserking now.
 * Arman, June 2021
 */
 
#pragma strict_types

#include "../defs.h"

inherit "/d/Genesis/specials/timed_ability";
inherit "/d/Genesis/specials/calculations";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include <formulas.h>
#include "/std/combat/combat.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define BERSERK_STR_BONUS   "_berserk_strength_bonus"
#define BERSERK_CON_BONUS   "_berserk_constitution_bonus"
#define BERSERK_DIS_BONUS   "_berserk_discipline_bonus"

public void config_ability()
{
    ::config_ability();
    set_ability_name("berserk");
    set_ability_offensive(0);
    set_ability_no_stun(0); // even stunned, they should be able to berserk
                            // needs to be set, otherwise cannot come
                            // down from berserk.   
    set_ability_hasted(0); // no haste changes to berserk
    set_ability_visual(0);
    set_ability_target(target_actor);    
}

public int
query_ability_prep_time()
{
    int berserk_skill, time;
    
    berserk_skill = this_player()->query_skill(SS_BERSERK);
    
    time = 5; // prepare time of 5 seconds
    time = 25 + berserk_skill / 4;  // berserk of 25 to 50 seconds
    
    return time;
}

public int
query_ability_cooldown_time()
{
    int berserk_skill;
    
    berserk_skill = this_player()->query_skill(SS_BERSERK);
    return max(10, 25 - berserk_skill / 5);
}

static int
query_str_bonus(object player)
{
    return convert_caid_to_stat(player, 15, SS_STR);
}

static int
query_con_bonus(object player)
{
    return convert_caid_to_stat(player, 20, SS_CON);
}

static int
query_dis_bonus(object player)
{
    return convert_caid_to_stat(player, 15, SS_DIS);
}

static void
update_weapons(object player)
{
    map(player->query_weapon(-1), player->update_weapon);
}

public void
reset_berserk_stats(object ob)
{
    int str_bonus, con_bonus, dis_bonus;
    
    str_bonus = ob->query_prop(BERSERK_STR_BONUS);
    con_bonus = ob->query_prop(BERSERK_CON_BONUS);
    dis_bonus = ob->query_prop(BERSERK_DIS_BONUS);
    
    if (str_bonus != 0)
    {
        ob->remove_prop(BERSERK_STR_BONUS);
        ob->set_stat_extra(SS_STR,
             ob->query_stat_extra(SS_STR) - str_bonus);
    }
    if (con_bonus != 0)
    {
        ob->remove_prop(BERSERK_CON_BONUS);
        ob->set_stat_extra(SS_CON,
             ob->query_stat_extra(SS_CON) - con_bonus);
    }
    if (dis_bonus != 0)
    {
        ob->remove_prop(BERSERK_DIS_BONUS);
        ob->set_stat_extra(SS_DIS,
             ob->query_stat_extra(SS_DIS) - dis_bonus);
    }            

    update_weapons(ob);
}

static int
query_burnout_amount(object player)
{
    int skill, burnout;
    
    skill = player->query_skill(SS_BERSERK);
    burnout = (220 - skill) / 6; // from 20-37 fatigue depending on skill
    
    return burnout;
}

void
do_berserk(object ob)
{
    int hp_boost, str_bonus, con_bonus, dis_bonus;

    if (!objectp(ob))
    {
        return;
    }    
    
    // Calculate the hp boost based on the con difference
    hp_boost = F_MAX_HP(ob->query_stat(SS_CON) + query_con_bonus(ob))
                 - ob->query_max_hp();

    reset_berserk_stats(ob); // just in case it never got reset correctly
    str_bonus = query_str_bonus(ob);
    con_bonus = query_con_bonus(ob);
    dis_bonus = query_dis_bonus(ob);
    ob->add_prop(BERSERK_STR_BONUS, str_bonus);
    ob->add_prop(BERSERK_CON_BONUS, con_bonus);
    ob->add_prop(BERSERK_DIS_BONUS, dis_bonus);
    
    // Adjust stats so that the combat aid for charge increases by 6%
    ob->set_stat_extra(SS_STR,
         ob->query_stat_extra(SS_STR) + str_bonus);
    ob->set_stat_extra(SS_CON,
         ob->query_stat_extra(SS_CON) + con_bonus);
    ob->set_stat_extra(SS_DIS,
         ob->query_stat_extra(SS_DIS) + dis_bonus);
    update_weapons(ob);

    send_debug_message("berserk", "Boosting hit points for "
        + ob->query_real_name() + " by " + hp_boost + ".");
    ob->heal_hp(hp_boost); 

    // You gain fatigue at the start of berserk, and lose it
    // at expiration.
    ob->add_fatigue(query_burnout_amount(ob));

    ob->catch_tell("You start slavering at the mouth.\n");
    say(QCTNAME(ob) + " works "+ob->query_objective()+"self"+
      " into a wild battle rage.\n", ob);
}

static void 
ability_msg(object actor, mixed * targets, string arg)
{
    float prep_time = 2.5;
    actor->catch_tell("Your breathing becomes heavier.\n");
    prep_time += (rnd() * prep_time) + (rnd() * prep_time);

    set_alarm(prep_time, 0.0, &do_berserk(actor));
}

void
expire_berserk(object ob)
{
    int hp_boost;
    
    if (!objectp(ob)) 
    {
        return;
    }
    
    // Calculate the hp boost based on the con difference
    hp_boost = ob->query_max_hp() 
                 - F_MAX_HP(ob->query_stat(SS_CON) - query_con_bonus(ob));                 
    send_debug_message("berserk", "Reducing hit points for "
        + ob->query_real_name() + " by " + hp_boost + ".");
    ob->heal_hp(-hp_boost);

    reset_berserk_stats(ob); // reduces the extra stats
    
    // It takes fatigue to use berserk. Apply the costs here
    if (query_burnout_amount(ob) > ob->query_fatigue()) 
    {
        ob->set_fatigue(1);
    }
    else 
    {
        ob->add_fatigue(-query_burnout_amount(ob));
    }

    if (ob->query_hp() <= 0)
    {
        ob->catch_tell
             ("You begin to calm down and return to a normal frame "
            + "of mind and realize that your wounds have brought you "
            + "close to death.\n");
    }
    else
    {        
        ob->catch_tell("You begin to calm down and return to a normal "
                     + "frame of mind.\n");
    }
    say(QCTNAME(ob) + " seems to have returned to a normal frame of "+
      "mind.\n");
}

static void resolve_ability(object actor, mixed * items, 
            mixed * targets, int * resist, mixed * results)
{
    // When the ability executes, the cooldown starts.
    // We notify the player that it has ended.
    expire_berserk(actor);
}

public void
hook_special_complete()
{
    write("\nYou can now enter a berserked state again.\n\n");
}

public void
hook_already_active(object ability)
{
    write("You are foaming at the mouth as it is.\n");
}

public void
hook_special_in_cooldown()
{
    write("You are too exhausted to go berserk.\n");
}

/*
 * Function name: validate_requirements
 * Description  : Function to check all the prerequisites of charge
 *                These checks are used in both check_valid_action
 *                as well as force fail. (before start, and before
 *                execute)
 * Arguments    : player - person executing the special
 * Returns      : 0/1 - invalid/valid conditions
 */
public int
validate_requirements(object player)
{
    seteuid(getuid()); 
    int skill;
    
    skill = player->query_skill(SS_BERSERK);

    if(skill == 0)
    {
        player->catch_tell("Berserk is a skill, not just something you "
                         + "do.\n");
        return 0;
    }

    if (CHECK_PUNISHMENT(player, PUN_SPEC))
    {
        player->catch_tell("Kalak has cursed you with the inability to "
                         + "berserk!\nYou shall need to find another "
                         + "way to defeat your enemies.\n");
        return 0;
    }
    
    if (query_burnout_amount(player) > player->query_fatigue())
    {
        player->catch_tell("You are too exhausted to go berserk.\n");
        return 0;
    }
    
    return 1;
}

/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The player
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object player, mixed * targets, string arg, int execute)
{
    object enemy;
    object * enemies;
    
    if (!execute && !validate_requirements(player))
    {
        // Only need to validate requirements at the beginning, not at
        // the end.
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}

