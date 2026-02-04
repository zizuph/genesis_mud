/*
 * Changelog:
 *  November 2009 - Added hook_targets_gone function (Petros)
 */
#pragma strict_types

#include "../guild.h"

inherit CORELIB_DIR+"std/damage";

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>
#include "/std/combat/combat.h"


public mixed * target_flurry(object actor, string str);


public void config_ability()
{
    ::config_ability();
    set_combat_aid(ATTACK_COMBAT_AID);
    set_tohit(95);
    set_ability_time(10);
    // Removed Guild Stat from stat calculation - February 2009
    set_stats( ({ SKILL_AVG, TS_DEX, TS_STR, SKILL_END }) );
    set_skills( ({ VAMP_SKILL_FLURRY }) );
    set_ability_name("flurry");
    set_ability_vocal(0);
    set_ability_visual(0);
    set_ability_target(target_flurry);

    // Bite cannot be used at the same time as flurry
    add_ability_restriction(ABILITY_DIR + "bite");

    // Added call to set default guildstat parameters - February 2009
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
}

/*
 * Removed masked call as part of Balance Review, February 2009
 * Replaced with query_guild_stat_type mask.
 * Rationale:
 *  The use of guildstat will be modified to global standard, which
 *  is that guildstat may only be used to limit the power of a special,
 *  not to enhance it beyond what is paid in tax.
 *
 */
/*
public mixed query_stats()
{
    if (TP->query_bloodguard())
    {
        return ({ SKILL_AVG, TS_DEX, TS_STR, TS_LAYMAN, SKILL_END });
    }
    return ({ SKILL_AVG, TS_DEX, TS_STR, TS_OCC, SKILL_END });
}
*/


public int
query_guild_stat_type(object player)
{
    if (player->query_bloodguard())
    {
        return SS_LAYMAN;
    }
    else
    {
        return SS_OCCUP;
    }
}

/*
 * Function name: query_dt
 * Description  : Checks the weapons and returns the weapon type
 * Arguments    : items - array of required items. Typically only be one
 *                        weapon in the array
 * Returns      : the damage type
 */
public int query_dt(object * items)
{
    object cob=TP->query_combat_object();
    
    mixed * result=cob->query_attack(items[0]);

    int dt=result[ATT_DAMT];
    
    dt=one_of_list(({dt & W_IMPALE, dt & W_SLASH, dt & W_BLUDGEON,
                     dt & MAGIC_DT }) - ({0}));
    return dt;
}

/*
 * Masked function removed so Vampires pay for their hitloc targeting.
 * February 2009.
 * Rationale:
 *  Tax will be applied to the Vampires ability to target specific
 *  locations to their specials according to the standard ability
 *  system. Currently, Vampires pay no tax for this ability which 
 *  can give them the ability to do (quite commonly) twice as much
 *  damage to a heavily armoured opponent (simply by targetting the
 *  head, which will rarely have AC > 50.)
 
public int query_hitloc_factor()
{
    return 100;
}
 */
 
public void special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt,int phit, 
                int dam,mixed * items)
{

    string dam_desc_me,dam_desc_them;
    string injury_desc;
    
    switch (dt)
    {
        case W_SLASH:
            dam_desc_me="slash";
            dam_desc_them="slashes";
            injury_desc="cuts";
            break;
        case W_BLUDGEON:
            dam_desc_me="strike";
            dam_desc_them="strikes";
            injury_desc="bruises";
            break;
        case W_IMPALE:
        default:
            dam_desc_me="stab";
            dam_desc_them="stabs";
            injury_desc="holes";
            break;
    } 

    object cob=TP->query_combat_object();
    
    string wep=cob->cb_attack_desc(items[0]);

    string prefix;
    
    switch (random(5))
    {
        case 0:prefix="Lunging forward with unnatural speed, ";
        break;
        case 1:prefix="In the blink of an eye, ";
        break;
        case 2:prefix="In a sudden rush, ";
        break;
        case 3:prefix="In a burst of speed, ";
        break;
        case 4:prefix="With lightning pace, ";
        default:
        prefix="Suddenly, ";
    }
    
    string adv;
    
    switch (random(6))
    {
        case 0:adv="viciously ";
            break;
        case 1:adv="cruelly ";
            break;
        case 2:adv="fiercely ";
            break;
        case 3:adv="savagely ";
            break;
        case 4:adv="dangerously ";
            break;
        default:
            adv="";
    }
    
    string times;
    switch (random(4))
    {
        case 0:times=" four times ";
            break;
        case 1:times=" repeatedly ";
            break;
        case 2:times=" fourfold ";
            break;
        default:
            times=" with quadruple attacks ";
    }

    string actor_msg="you " + adv + dam_desc_me + times +
        "into the " +hdesc + " of " + QTNAME(enemy) + " with your "+
        wep + ",";
    
    string watcher_msg=QTNAME(TP)+ " " +adv + dam_desc_them + 
        times + "into the " + hdesc + " of " + QTNAME(enemy) + 
        " with " + POSS(TP) + " " + wep + ",";

    string enemy_msg=QTNAME(TP) + " " + adv + dam_desc_them + times +
        "into your " + hdesc + " with " + POSS(TP) + " " + wep +",";
    
    string kind_msg;
    
    switch (phurt)
    {
        case 0:
            kind_msg=" leaving no mark.\n";
            break;
        case 1..2:
            kind_msg=" leaving minor "+injury_desc+".\n";
            break;
        case 3..5:
            kind_msg=" leaving four small "+injury_desc+".\n";
            break;
        case 6..10:
            kind_msg=" leaving a set of "+injury_desc+".\n";
            break;
        case 11..20:
            kind_msg=" leaving a large set of "+injury_desc+".\n";
            break;
        case 21..40:
            kind_msg=" leaving massive "+injury_desc+".\n";
            break;
        case 41..80:
            kind_msg=" leaving a grevious series of "+injury_desc+".\n";
            break;
        default:
            kind_msg=" leaving a deadly series of "+injury_desc+".\n";
    }
        
    TP->catch_msg(prefix+actor_msg+kind_msg);

    TP->tell_watcher(prefix+watcher_msg+kind_msg, ({ enemy }));

    enemy->catch_msg(prefix+enemy_msg+kind_msg);
    
    if (enemy->query_hp()<=0)
    {
        enemy->do_die(TP);
    }
    
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

    if (!::check_valid_action(player,targets,arg,execute))
    {
        return 0;
    }

    // If it passes everything, return success
    return 1; 
}

public varargs string
query_restricted_ability_message(string ability, object player)
{
    string short_desc;
    
    short_desc = ability->short();
    if (!strlen(short_desc))
    {
        return "You are busy preparing your flurry of attacks.\n";
    }
    
    return "You are too busy preparing your flurry of attacks to "
        + short_desc + ".\n";
}

static mixed * check_required_items(object actor,mixed * targets,
                  string arg,int pretest)
{
    int best_pen=0;
    int best_aid=-1;
    
    foreach (int aid: actor->query_combat_object()->query_attack_id())
    {
        mixed results=actor->query_combat_object()->query_attack(aid);
        if (results[1][0]>best_pen)
        {
            best_pen=results[1][0];
            best_aid=aid;
        }
    }
    if (best_aid<0)
    {
        actor->catch_msg("You have no attacks to flurry with.\n");
        return 0;
    }
    return ({ best_aid });
}

public int get_hitloc_id(object target,string location)
{
    if (!objectp(target))
    {
        return -1;
    }
    
    object co = target->query_combat_object();
    int * hitloc_ids = co->query_hitloc_id();
    string * hitloc_descs = map(hitloc_ids, 
    &operator([])(, HIT_DESC) @ &co->query_hitloc());
	int pos=member_array(location,hitloc_descs);

    if (pos<0)
    {
        return -1;
    }

    return hitloc_ids[pos];   
}


public mixed *
target_flurry(object actor, string str)
{
    if (!strlen(str))
    {
        if (!actor->query_attack())
        {
            actor->catch_msg("Unleash a flurry of attacks at whom?\n");
            return ({ });
        }
        return ({ actor->query_attack() });
    }

    string target, location;
    
    int hitloc_id;
    
    object * found;
    if (!sscanf(str,"%s's %s",target,location) &&
    !parse_command(str,({ }),"[at] [the] %s 'of' [the] %s",
                location, target))
    {
        if (!parse_command(str,({ }),"[at] [the] %s",
                location))
        {
            actor->catch_msg("Unleash a flurry of attacks at whom?\n");
            return ({ });
        }
        hitloc_id=get_hitloc_id(actor->query_attack(),location);
        
        if (hitloc_id==-1)
        {
            target=location;
            location=0;
        }
        else
        {
            return ({ ({ actor->query_attack(), hitloc_id }) });
        }
    }

    found = PARSE_THIS(target, "[at] / [on] [the] %l");

    if (sizeof(found) > 1)
    {
        actor->catch_tell("You will have to be more specific!  You can only " +
            "select one target.\n");
        return ({});
    }

    if (!sizeof(found) && actor->query_attack())
    {
        found=({ actor->query_attack() });
        location=target;
    }
    
    if (!sizeof(found))
    {
        actor->catch_msg("Unleash a flurry of attacks at whom?\n");
        return ({ });
    }

    if (stringp(location))
    {
        hitloc_id=get_hitloc_id(found[0],location);
        
	    if (hitloc_id==-1)
	    {
            actor->catch_msg("You cannot hit " + QTNAME(found[0]) +
                " there.\n");
            return ({ });
	    }
	    
	    return
	    ({  ({ found[0], hitloc_id }) });

    }

    return ({ found[0] });    

}

public int
is_target_alive(mixed target)
{
    if (!target)
    {
        return 0;
    }
    
    if (pointerp(target))
    {
        // Vampire targets can be arrays. We look inside the array
        if (sizeof(target) && living(target[0]))
        {
            return 1;
        }
        return 0;
    }
    
    if (objectp(target))
    {
        return living(target);
    }
    
    return 0;
}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the actor when
 *                the targets has disappeared during the prepartion of the
 *                ability.
 * Returns:       The message to print
 */
public void
hook_targets_gone(object * targets)
{
    object * alive_targets = filter(targets, is_target_alive);
    if (!sizeof(alive_targets))
    {
        if (sizeof(targets) > 1)
        {
            write("You cannot attack your prey as they have all been "
                + "slain!\n");
        }
        else
        {
            write("You cannot attack your prey it has already been slain!\n");
        }
    }
    else
    {
        write("You cannot attack " + COMPOSITE_LIVE(alive_targets)
            + " as they have escaped!\n");
    }    
}
