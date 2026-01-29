/*
 * Implementation of a general damage special.  
 *
 * Inherit this and reconfigure it for your particular special.
 * 
 * Example:
 * 
 * inherit ABILITY_DIR+"damage";
 * 
 * #include <ss_types.h>
 * #include <wa_types.h>
 * #include <tasks.h> 
 *
 * public varargs int
 * config_ability()
 * {  
 *     ::config_ability();
 * 
 *     set_ability_time(25);
 *     set_tohit(65);
 *     set_combat_aid(80);
 *     set_dt(SLASH_DT);
 *     set_skills(({ SKILL_AVG, SS_SWORD, SS_MYSPECIAL, SKILL_END }) );
 *     set_stats(({ SKILL_AVG, TS_STR, TS_DEX, SKILL_END }) );
 *
 *     return 0;
 * }
 * public varargs void special_did_hit(int aid, string hdesc, int hid, 
 *               int phurt, object enemy, int dt,int phit, int dam,
 *               mixed * items, int result)
 *
 * {
 *    switch(phurt)
 *      case 1..4: 
 * }
 *
 * static mixed * check_required_items(object actor,mixed * targets,
 *                   string arg,int pretest)
 * {
 *    object * weapons=this_player()->query_tool(-1) -
 *             this_player()->query_armour(-1);
 *     
 *    foreach (object weapon : weapons)
 *    {
 *       if (weapon->query_wt()==WT_SWORD)
 *       {
 *            //Found our required weapon - this will be used in our
 *            //damage calculation.  If I wanted to use a certain
 *            //attack_id, I could specify that.
 *            return ({ weapon });
 *       }
 *    }
 *    return 0;  //Needed a wielded sword
 *
 * Modified 2019-06-11 by Carnak:
 *  - The function query_success() has been altered to allow modification of
 *    query_tohit based on items hit value. The argument items has been added.
 * Modified 2020-06-14 by Carnak:
 *  - Added armour penetration calculations for specials using MAGIC_DT in
 *    function resolve_ability.
 * Modified 2021-02-05 by Carnak:
 *  - Added a calc_base_hit function which handles the modification of the
 *    ability hit value based on the items utilized by the special.
 * Modified 2021-02-20 by Carnak:
 *  - Added set_ability_armour_penetration to be able to properly define
 *    which function to use for armour modification.
 *  - Updated the calc_hitme_modifier function with proper hit values.
 * Modified 2021-03-16 by Carnak:
 *  - Added a cap to the calc_stat_modifier, so as to avoid stealth increases
 *    or bugs.
 */
#pragma strict_types

#include "defs.h"
inherit COMBAT_ABILITY_LIB;

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <math.h>
#include <wa_types.h>
#include <formulas.h>
#include "/std/combat/combat.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"


static function Ability_armour_pen;    /* The armour penetration function */

// Defines
#define DAMAGE_LOGS "/d/Genesis/specials/std/damage_logs/"


/************************************************************************
 *                           Relic Functions                            *
 ************************************************************************/
public void set_tohit(int i) { set_ability_hit(i); }
public int query_tohit() { return query_ability_hit(); }
public void set_dt(int i) { set_ability_damage_type(i); }
public int query_dt(object *items) { return query_ability_damage_type(items); }
public void set_combat_aid(int aid) { set_ability_combat_aid(aid); }
public int query_combat_aid() { return query_ability_combat_aid(); }
public int query_combat_aid_modifier() { return query_ability_combat_aid_modifier(); }
public void set_skills(mixed skills) { set_ability_skills(skills); }
public mixed query_skills() { return query_ability_skills(); }
public void set_stats(mixed stats) { set_ability_stats(stats); }
public mixed query_stats() { return query_ability_stats(); }

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
    set_combat_aid(100);
    set_tohit(75);
    set_ability_time(15);
    set_ability_offensive(1);
    set_ability_visual(0);
    set_ability_allow_hunting(1);
    set_dt(W_BLUDGEON);
    set_ability_dual_wield(1);
    set_skills(({ SS_UNARM_COMBAT }));
    set_stats(TS_STR);
    set_ability_target(target_one_other_present_living_or_enemy);
    set_ability_target_verify(verify_change_enemy);
    
    // Set the scaling functions for the ability. by default, we
    // don't know what guild stat will be used
    set_guild_stat_modifier(0, 20, 100);
}


/*
 * Function name: special_did_hit
 * Description  : Mask this function to process when the special
 *                scores. Descriptions seen by everyone are set
 *                here.
 * Arguments    : aid   - attack id
 *                hdesc - hit description
 *                hid   - 
 *                phurt - extent of damage
 *                enemy - person being hit by special
 *                dt    - damage type
 *                phit  - 
 *                dam   - damage amount
 *                result - result of cb_tohit
 * Returns      : nothing
 */
public varargs void 
special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt,int phit, 
                int dam, mixed * items, int result)
{
    //Messages for the hit here
}

/*
 * Function name: report_resolve_ability
 * Description:   Function called when the ability executes to allow
 *                masking and reporting and logging. By default, it
 *                simply sends the info via send_debug_message
 * Arguments:     pen    - the pen of the hit
 *                dt     - the damage type of the hit
 *                damage - the amount of damage dealt
 */
public void
report_resolve_ability(int pen, int dt, int damage)
{
    string name;
    
    if (interactive(this_player()))
    {
        name = capitalize(this_player()->query_real_name());
    }
    else
    {
        name = MASTER_OB(this_player());
    }

    send_debug_message(short(), name + " hits with Pen of " 
        + pen + ", " + "Damage of " + damage);  
}

public void
log_hitloc_difference(object target, int dt, int pen, int random_hitloc, int hitloc)
{
    mixed ac;
    int targeted_ac, targeted_damage;
    int random_ac, random_damage;
    mixed target_hitinfo, random_hitinfo;
    string logfile;
    object cobj;
    
    if (!objectp(target))
    {
        return;
    }
    
    if (interactive(this_player())
        && random_hitloc != -1 && random_hitloc != hitloc 
        && dt != MAGIC_DT)
    {
        cobj = target->query_combat_object();
        target_hitinfo = cobj->query_hitloc(hitloc);
        random_hitinfo = cobj->query_hitloc(random_hitloc);
        int ac_index = MATH_FILE->quick_find_exp(dt);
        if (!pointerp(target_hitinfo) || sizeof(target_hitinfo) < 4
            || !pointerp(random_hitinfo) || sizeof(random_hitinfo) < 4)
        {
            return;
        }
        targeted_ac = ftoi(target_hitinfo[3][ac_index]);
        random_ac = ftoi(random_hitinfo[3][ac_index]);
        // We log how much of a benefit having a targeted hitloc was
        // based on the F_NEW_DAMAGE formula
        logfile = FILE_PATH(MASTER_OB(this_object()));
        logfile += short() + "_hitloc_log";
        logfile = implode(explode(logfile, " "), "");
        targeted_damage = F_NEW_DAMAGE(pen, 1000, targeted_ac);
        random_damage = F_NEW_DAMAGE(pen, 1000, random_ac);
        send_debug_message("damage_log", capitalize(this_player()->query_name())
            + " dealt " + targeted_damage + " damage at targeted hitloc \""
            + target_hitinfo[2] + "\" with an AC of " + targeted_ac
            + " while damage at the random hitloc \"" + random_hitinfo[2]
            + "\" would be " + random_damage + " with an AC of " 
            + random_ac + ".", logfile);
    }    
}

/*
 * Function name: resolve_ability
 * Description:   This function is responsible for performing the routines
 *                necessary to produce the special effect(s).  All specials that
 *                manifest any effect whatsoever need to redefine this and
 *                implement those.
 *                NB: _live_i_attack_delay is treated as a partial stun, 
 *                and does not block these specials
 *
 * Arguments:     1. (object)   The player
 *                2. (object *) The targets
 *                3. (int *)    Resistance values corresponding to each target
 *                4. (int)      The attempt result as returned by
 *                              query_casting_success()
 */
public void
resolve_combat_special(object actor, object target, int hitloc,
    int random_hitloc, int pen, int damage_type, mixed * items,
    int resist, int result)
{
    mixed *hitresult = target->hit_me(pen, damage_type, actor, -1, hitloc);
            
    string target_name, logfile;
    if (interactive(target))
    {
        target_name = target->query_real_name();
    }
    else if (objectp(target))
    {
        target_name = MASTER_OB(target);
    }

    if (!pointerp(hitresult))
    {
        logfile = implode(explode(MASTER_OB(this_object()), "/")[..-2], "/") + "/";
        logfile += short() + "_errors";
        logfile = implode(explode(logfile, " "), "");
        
        send_debug_message(Ability_name, "An error in the hitresult has "
        + "occurred while targeting " + target_name + ".", logfile);
        return;
    }
    else if (sizeof(hitresult) != 5)
    {
        logfile = implode(explode(MASTER_OB(this_object()), "/")[..-2], "/") + "/";
        logfile += short() + "_errors";
        logfile = implode(explode(logfile, " "), "");
        
        send_debug_message(Ability_name, "An error in the hitresult has "
        + "occurred while targeting " + target_name + ".", logfile);
        
        // We populate the results with empty values at the end
        int size_difference = 5 - sizeof(hitresult);
        for (int index = 0; index < size_difference; ++index)
        {
            hitresult += ({ 0 });
        }
    }
    
    report_resolve_ability(pen, damage_type, hitresult[3]);
    log_hitloc_difference(target, damage_type, pen, random_hitloc, hitloc);
    
    special_did_hit(-1, hitresult[1], hitresult[4], hitresult[0], target,
        damage_type, hitresult[2], hitresult[3], items, result);
}

public void
hook_concentration_fail(object ability)
{
    write("You are too busy casting a spell.\n");
}


/*
 * Function name: check_valid_action
 * Description:   Perform ability-specific checks
 * Arguments:     1. (object) The actor
 *                2. (mixed *) The targets
 *                3. (string) Arguments passed to the command
 *                4. (int) Actual spell execution
 * Returns:       (int) 1 if we can continue, 0 if failure
 */
static int check_valid_action(object actor,mixed * targets,string arg,int 
                                execute = 0)
{
#ifdef NO_SPECIALS_WHILE_CASTING
    if (actor->query_prop(LIVE_I_CONCENTRATE))
    {
        hook_concentration_fail(this_object());
        return 0;
    }
#endif
    return 1;
}

/*
 * Function name: query_best_wielded_weapon
 * Description  : Compares the wielded weapons according to the appraise and
 *                weapon skill of the wielder. Returns the better of the
 *                weapons (if there is one wielded). Compare code taken from
 *                /cmd/live/state.c in the compare_weapon method
 * Arguments    : object player - person wielding the weapons
 */
public object
query_best_wielded_weapon(object player)
{
    object * weapons;
    object weapon1, weapon2;
    int stat1, stat2, skill, seed;
        
    weapons = player->query_weapon(-1);
    if (!sizeof(weapons))
    {
        return 0;
    }
    else if (sizeof(weapons) == 1)
    {
        return weapons[0];
    }
    
    // Have more than one weapon.
    if (OB_NUM(weapons[0]) > OB_NUM(weapons[1]))
    {
        weapon1 = weapons[1];
        weapon2 = weapons[0];
    }
    else
    {        
        weapon1 = weapons[0];
        weapon2 = weapons[1];
    }
    
    stat1 = query_ability_base_pen(player, ({ weapon1 }));
    stat2 = query_ability_base_pen(player, ({ weapon2 }));
    
    stat1 += query_ability_base_hit(player, ({ weapon1 }));
    stat2 += query_ability_base_hit(player, ({ weapon2 }));
    
    skill = (2000 / (1 + player->query_skill(SS_APPR_OBJ) +
        player->query_skill(SS_WEP_FIRST + weapon1->query_wt()) +
        player->query_skill(SS_WEP_FIRST + weapon2->query_wt())
        ));
    seed = atoi(OB_NUM(weapon1)) + atoi(OB_NUM(weapon2));

    /* Compare the penetration values. */
    stat1 += random(skill, seed);
    stat2 += random(skill, seed + 27);
    send_debug_message("damage_compare", weapon1->short() + " stat1: " + stat1 + " " + weapon2->short() + " stat2: " + stat2 + " skill: " + skill + " seed: " + seed);

    if (stat1 > stat2)
    {
        return weapon1;
    }
    
    return weapon2;    
} /* query_best_wielded_weapon */
