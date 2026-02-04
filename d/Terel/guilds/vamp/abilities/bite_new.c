/*
 * Novo,  May - June 2008
 *
 * modified by: 
 *   Lilith, 23 Oct 2008
 *   -- removed the attack_delay per AoB
 *   Lilith, 16 Nov 2008
 *   -- updated query_combat_aid_modifier so BG do not get too much combat aid
 *      with the move of the former haste-drain caid to bite caid
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

#define BLOOD_SHADOW (OBJ_DIR+"blood_shadow")

#define BITE_LOG (LOG_DIR+"bite_log")

public mixed * target_bite(object actor, string str);


public void config_ability()
{
    ::config_ability();
    set_combat_aid(ATTACK_COMBAT_AID);
    set_tohit(95);
    set_ability_time(10);
    //set_dt(MAGIC_DT);
    set_dt(W_IMPALE);
    // Removed Guild Stat from stat calculation - February 2009
    set_stats( ({ SKILL_AVG, TS_DEX, TS_STR, SKILL_END }) );
    set_skills( ({ VAMP_SKILL_BITE }) );
    set_ability_name("savage");
    set_ability_target(target_bite);
    set_ability_vocal(1);
    set_ability_visual(0);
    // Bite cannot be used at the same time as flurry
    add_ability_restriction(ABILITY_DIR + "flurry");
    
    // Added call to set default guildstat parameters - February 2009
    set_guild_stat_modifier(SS_OCCUP, 20, 100);    
}

public int is_drainable(object target)
{
    if (target->query_vampire())
    {
        return 1;
    }
    if (target->query_race_name()=="vampire")
    {
        return 1;
    }
    if (target->query_prop(LIVE_I_UNDEAD))
    {
        return 0;
    }
    if (target->query_prop(LIVE_I_NO_BODY))
    {
        return 0;
    }
        
    return 1;
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
        return "You are busy preparing to savage your foe.\n";
    }
        
    return "You are too busy preparing to savage your foe to "
        + short_desc + ".\n";
}

/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier()
{
    int aid=100;
    /* Layman branch - half the occ aid */
    if (IS_BG(TP)) 
    {
        // 50% of Occ damage. Current OCC is 80% combat aid.
        // Bloodguards should get 40% combat aid
        aid = 50;
        
        //Further reduction if they have no Master
        if (!TP->query_master())
        {
            aid=35;
        }
    }    
    return aid;
}

public void special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt,int phit, 
                int dam,object * items)
{
            
    switch (hdesc)
    {
        case "head":
            hdesc="neck";
            break;
        case "left arm":
            hdesc="left wrist";
            break;
        case "right arm":
            hdesc="right wrist";
            break;
        case "legs":
            hdesc="thigh";
            break;
    }

    if (phurt<0)
    {

        TP->catch_msg
        ("You try to bite at the "+hdesc+" of "+QTNAME(enemy) +
        " but miss.\n");
        
        TP->tell_watcher(
        QCTNAME(TP)+" leaps to bite at the "+hdesc+" of "+
        QTNAME(enemy) + ", but "+PRO(enemy)+ " avoids the attack.\n",
        ({ enemy }) );
        
        enemy->catch_msg(QTNAME(TP)+" leaps to bite your "+
        hdesc+ ", but you avoid the attack.\n");
        return;
    }
    
    string prefix;
    
    switch (random(5))
    {
        case 0:prefix="Dancing with preternatural speed, ";
        break;
        case 1:prefix="Leaping with feral ferocity, ";
        break;
        case 2:prefix="Rushing at lightning pace, ";
        break;
        case 3:prefix="With unbridled strength, ";
        break;
        case 4:prefix="With cat-like reflexes, ";
        default:
        prefix="With savage power, ";
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
    
    string actor_msg="you bite " + adv + "into the " +hdesc + " of " +
           QTNAME(enemy);
    
    string watcher_msg=QTNAME(TP)+ " bites " + adv + "into the "+
           hdesc + " of " + QTNAME(enemy);

    string enemy_msg=QTNAME(TP) + " bites " + adv + "into your " +
           hdesc;
    
    string kind_msg;
    
    switch (phurt)
    {
        case 0:
            kind_msg=" leaving no mark.\n";
            break;
        case 1..2:
            kind_msg=" leaving a pair of scratches.\n";
            break;
        case 3..5:
            kind_msg=" leaving a small pair of puncture marks.\n";
            break;
        case 6..10:
            if (is_drainable(enemy))
            {
                kind_msg=" leaving two bleeding marks.\n";
            }
            else
            {
                kind_msg=" leaving two marks.\n";
            }
            break;
        case 11..15:
            if (is_drainable(enemy))
            {
                kind_msg=" leaving a thin trail of blood.\n";
            }
            else
            {
                kind_msg=" leaving a noticable wound.\n";
            }
            break;
        case 16..20:
            if (is_drainable(enemy))
            {
                kind_msg=" leaving a trail of blood.\n";
            }
            else
            {
                kind_msg=" leaving a large wound.\n";
            }
            break;
        case 21..40:
            if (is_drainable(enemy))
            {
                kind_msg=" leaving a thick trail of blood.\n";
            }
            else
            {
                kind_msg=" leaving a very large wound.\n";
            }
            break;
        case 41..60:
            if (is_drainable(enemy))
            {
                kind_msg=" leaving a gushing wound.\n";
            }
            else
            {
                kind_msg=" leaving a massive wound.\n";
            }
            break;
        case 61..80:
            kind_msg=" leaving a grevious wound.\n";
            break;
        default:
            kind_msg=" leaving a deathly wound.\n";
    }


    TP->catch_msg(prefix+actor_msg+kind_msg);

    TP->tell_watcher(prefix+watcher_msg+kind_msg, ({ enemy }));

    enemy->catch_msg(prefix+enemy_msg+kind_msg);

    if (is_drainable(enemy) && phurt > 0)
    {
        if (!enemy->query_bleeding())
        {
            setuid();
            seteuid(getuid());
            object shadow=clone_object(BLOOD_SHADOW);
            catch (shadow->shadow_me(enemy));
        }                    
        
        enemy->bite_location(hid);

        if (enemy->query_hitloc_bleeding(hid))
        {
            TP->drain_blood(enemy);
        }
    
    }
    
    
    if (enemy->query_hp()<=0 && is_drainable(enemy))
    {
        //Killing blow, with lots of blood
        TP->drain_blood(enemy);
        TP->drain_blood(enemy);
        TP->drain_blood(enemy);
        switch (random(3))
        {
            case 0:
            TP->catch_msg("Your fangs find their home in the limp body "+
            "of " + QTNAME(enemy) +" as "+POSS(enemy) +" life force "+
            "pours across your lips.  You hold "+OBJ(enemy)+ " tightly, "+
            "relishing the taste.\n");
            break;
            default:
            TP->catch_msg("You hold the "+QTNAME(enemy)+" tightly in "+
            "your arms, "+ POSS(enemy) + " last shred of resistance " +
            "broken. "+capitalize(POSS(enemy)) + " blood fills your " +
            "mouth, allowing you to revel in "+POSS(enemy)+ " taste.\n");
        }
    
        switch (random(3))
        {
            case 0:
            TP->tell_watcher(QCTNAME(TP) + " slows for a moment, eyes " +
            "intent on " + QTNAME(enemy) + ". "+capitalize(PRO(TP)) +
            " casually reaches out to " + QTNAME(enemy) + ", drawing " +
            OBJ(enemy) + " into a tight embrace as "+PRO(TP)+" drinks " +
            "the life from " + POSS(TP)+ " prey.\n", ({ enemy }) );
            break;
            default:
            TP->tell_watcher(QCTNAME(enemy) + " staggers from side to " +
            "side, barely able to stand. " + capitalize(PRO(enemy)) + 
            " looks helpless, weakened to the point of frailty. "+ 
            QCTNAME(TP) +" takes " + OBJ(enemy) + " into "+POSS(TP) + 
            " embrace, holding tightly as "+PRO(TP)+" draws the last " +
            "bit of life from "+QTNAME(enemy)+".\n", ({ enemy }) );
            
        }

        enemy->catch_msg(QCTNAME(TP)+ " drains the remaining "+
        "life from your body, defeating you utterly. You can feel "+
        "your heart slowing, and then beating one last time.\n");
        enemy->set_killed_by_bite(TP);
    }
    if (enemy->query_hp()<=0)
    {
        enemy->do_die(TP);
    }
    
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
target_bite(object actor, string str)
{
    if (!strlen(str))
    {
        if (!actor->query_attack())
        {
            actor->catch_msg("Bite whom?\n");
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
        	actor->catch_tell("Which prey do you wish to savage?\n");
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
    	actor->catch_tell("Which prey do you wish to savage?\n");
        return ({ });
    }

    if (stringp(location))
    {
        hitloc_id=get_hitloc_id(found[0],location);
        
	    if (hitloc_id==-1)
	    {
            actor->catch_msg("You cannot bite " + QTNAME(found[0]) +
                " there.\n");
            return ({ });
	    }
	    
	    return
	    ({  ({ found[0], hitloc_id }) });

    }

    return ({ found[0] });    

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

    setuid();
    seteuid(getuid());
    if (file_size(BITE_LOG)>100000)
    {
        rm(BITE_LOG);
    }
    send_debug_message("savage", 
                    name + " bites with Pen of " + pen + ", "
                    + "Damage of " + damage,
                       BITE_LOG);

    
}

