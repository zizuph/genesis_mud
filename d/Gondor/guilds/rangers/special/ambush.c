/*
 * /d/Gondor/guilds/rangers/special/ambush
 *
 * This is a sneak attack
 *
 *
 *
 *
 */
#pragma no_clone
#pragma no_shadow
#pragma strict_types

#include "/d/Genesis/specials/new/defs.h"
#include "../rangers.h"
#include "../../../defs.h"
inherit DAMAGE_LIB;

#include "/d/Genesis/specials/new/melee/missile_functions.c";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>

/*
 * Function name: create_ability
 * Description  : Main fuction that configures the special.
 */
public void
create_ability(void)
{
    ::create_ability();

    setuid();
    seteuid(getuid());

    set_tohit(AMBUSH_TOHIT);

    // Per Ckrik - 125 CAID for missile attacks, reduced to 75
    // via the modifier for other weapon types.  This makes it
    // slightly better than normal aim/fire for this weapons.
    set_combat_aid(125);

    set_ability_prep_time(AMBUSH_PREP);
    set_ability_cooldown_time(AMBUSH_COOLDOWN);

    set_stats(AMBUSH_STATS);
    set_skills(AMBUSH_SKILLS);
    set_guild_stat_modifier(SS_OCCUP, 20, 100);

    set_ability_name("ambush");
    
    // The ranger will remain hidden until the actual attack.
    set_ability_no_reveal(1);
    set_ability_attack_during_prep(0);
    set_ability_group(RANGER_MAJOR_GROUP);
}

/*
 * Function name: query_dt
 * Description  : Checks the weapons and returns the weapon type
 * Arguments    : items - array of required items. Typically only be one
 *                        weapon in the array
 * Returns      : the damage type
 */
public int
query_dt(mixed * items)
{
    foreach (mixed weapon : items)
    {
        if (objectp(weapon))
        {
            /* This is a bit ugly as it does not deal correctly with
             * items with multiple dt. But it has to return the same dt
             * when called repeatedly in the same attack flow */
            int dt = weapon->query_dt();
            if (dt & W_IMPALE)
                return W_IMPALE;
            if (dt & W_SLASH)
                return W_SLASH;
            return W_BLUDGEON;
        }
    }
    
    /* Without a weapon, we are using either a shield or unarmed.
     * We'll just use bludgeoning damage.
     */
    return W_BLUDGEON;
} /* query_dt */

/*
 * Function name: check_required_items
 * Description  : Check for wielded weapons to determine which of
 *                the various special attacks we will perform.
 */
static mixed *
check_required_items(object actor, mixed *targets,
                     string arg, int pretest)
{
    object me = actor;
    foreach(mixed target : targets)
    {
        if (actor->check_seen(target) || target->query_is_enemy(actor))
        {
            me->catch_msg(QCTNAME(target) + " seems too aware of your " 
            + "presence for you to do an effective ambush.\n");
            return 0;
        }
    }
    object best = query_best_wielded_weapon(actor);
    if (best)
    {
        if (IS_LAUNCH_OBJECT(best))
        {
            object arrow;
            if (objectp(arrow = best->query_projectile()))
            {
                // Added to fix the unloading while tired during specials.
                string m_ob = MASTER_OB(arrow);
                arrow->remove_object();
                best->unload_projectile();
                arrow = clone_object(m_ob);
                arrow->set_heap_size(1);
                arrow->move(actor, 1);
                arrow->load();
            }
            if (!objectp(arrow) && !objectp(arrow = find_arrows(actor, best)))
            {
                me->catch_msg("You realize you have no arrows for your " +
                    best->short() + ".\n");
                return 0;
            }
            if (pretest)
            {
    	        me->catch_msg("You prepare to ambush " +
        	        targets[0]->query_the_name(actor) +
                    " with your " + best->short() + ".\n");
            }
            return ({ best, arrow });
        }
        if (pretest)
        {
	        me->catch_msg("You prepare to ambush " +
        	    targets[0]->query_the_name(actor) +
                " with your " + best->short() + ".\n");
        }
        return ({ best });
    }
    me->catch_msg("You need a weapon to do an effective ambush.\n");
    return 0;
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
        if (!caster->query_ranger_major_virtue())
        {
            caster->catch_msg("The art of the ambush is limited to full " 
                + "rangers.\n");
            return 0;
        }
    }
    return 1;
}

/*
 * Function name: hook_special_complete
 * Description  : Hook that gets called when a special completes
 *                Use this to display messages and to restart
 *                specials.
 */
#ifndef Genesis
public void
hook_special_complete(void)
{
    // Mimic npc's in doing auto-specials.
    if (!TP->query_npc() && TP->query_attack())
	restart_npc_special(0, "");
    else
	::hook_special_complete();
}
#endif

/*
 * Function name:   query_combat_aid_modifier
 * Description:     Calculates the percentage of the maximum combat aid that
 *                  applies to the current situation
 * Returns:         number between 1 and 100
 */
public int
query_combat_aid_modifier()
{
    
    // Only missile weapons get the full benefit here.
    // Others will get 60%, or the 75 CAID normally allocated to this
    // special.
    object best = query_best_wielded_weapon(this_player());
    if (best)
    {
        if (IS_LAUNCH_OBJECT(best))
            return 100;
    }
    return 60;
} /* query_combat_aid_modifier */


/*
 * Function name: ability_msg
 * Description  : Mask this function so that the prepare messages don't
 *                show up when this ability goes off.
 */
static void
ability_msg(object actor, mixed *targets, string arg)
{
    // Messages are printed in check_required_items().
}

public void arrow_missed(mixed* items, object target)
{
    //object weapon = items[0];  
    //if (!IS_LAUNCH_OBJECT(weapon))
        //return;
    //weapon->query_projectile()->unload();
    //weapon->move_projectile_to_env(environment(target), weapon->query_projectile());
}

public void arrow_hit(mixed* items, object target)
{
    //object weapon = items[0];        
    //if (!IS_LAUNCH_OBJECT(weapon))
//        return;
    //weapon->query_projectile()->unload();
    //weapon->move_projectile_to_target(target, weapon->query_projectile());
}

/*
 * Function name: special_did_hit
 * Description  : Mask this function to process when the special
 *                scores. Descriptions seen by everyone are set
 *                here.
 * Arguments    : aid   - attack id (always -1)
 *                hdesc - hitloc description
 *                hid   - hitloc id
 *                phurt - % hurt
 *                enemy - person hit
 *                dt    - damage type
 *                phit  - % hit
 *                dam   - damage amount
 *                items - result of check_required_items
 *                result - result from query_success on 'target'
 */
public void
special_did_hit(int aid, string hdesc, int hid,  int phurt,
    		object target, int dt, int phit, int dam,
		mixed *items,  int result)
{
       
    mixed tmp;
    object me = this_player();
    
    object weapon = items[0];    
    string wp = weapon->short();
    string qwp = QSHORT(weapon);
    
    string style;
    
    object arrow;
    
    if (IS_LAUNCH_OBJECT(weapon))
    {
        /* Manages arrow stacks */
        if (phurt < 6)
            arrow = reduce_and_miss(target, weapon, items[1]);
        else
            arrow = reduce_and_hit(target, weapon, items[1]);

        style = "fire";
    }
    else
    {
        switch (dt)
        {
            case W_IMPALE:
                style = "thrust";
                break;
            case W_SLASH:
            case W_BLUDGEON:
            default:
                style = "swing";
                break;
        }
    }
    
    /* Preparing to attack. */
    ME("Your muscles tense and your grip on your "+ wp +" tightens as you "+
        "get ready to ambush "+ QTNAME(target) +".");

    /* So the flavor-text will show where the attack lands */
    hdesc = (strlen(hdesc) ? hdesc : "body");
   
    /* We missed  */   
    if (result < 1)
    {
		// do a reveal_me?
        ME("Your timing is off, and you miss your opportunity to do an "+ 
        "ambush! Darn!");
        TWM(QCTNAME(TP) +" comes out of hiding looking flustered.");
        YOU(QCTNAME(TP) +" comes out of hiding looking flustered.");
        arrow_missed(items, target);
	    return;
    }

    /* We hit... */
    switch(phurt)
    {
		
	case -3: /* acrobatic dodge */
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +" but "+ 
        HE(target) +" deftly twists aside. Your ambush attempt failed.");
        TWM(QCTNAME(TP) +" tried to ambush "+ QTNAME(target) +" but "+
		"did not succeed.");
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        " and "+ style +"s "+ HIS(TP) +" "+ qwp +" at you but you deftly "+		
		"twist aside and "+ HE(TP) +" misses you completely.");
        arrow_missed(items, target);
        return;   
   
    case -2: /* ... but were parried! */
        tmp = (object)one_of_list(target->query_weapon(-1));  
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +" but "+ 
        HE(target) +" parries your attack with "+ HIS(target) +
	    " " + QSHORT(tmp) +".");
        TWM(QCTNAME(target) +" is ambushed by "+ QTNAME(TP) +" but "+
		"reacts quickly enough to parry the attack aside "+
	    " with "+ HIS(target) +" "+ QSHORT(tmp) +".");
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        " and "+ style +"s "+ HIS(TP) +" "+ qwp +" at you but you "+		
		"parry it aside with your "+ tmp->short() +".");
        arrow_missed(items, target);
        return;

    case -1: /* armour deflects? */
        tmp = (object *)target->query_armour(-1);

        if (sizeof(tmp))
        {
            object arm = one_of_list(tmp);
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +" but your "+ 
        "weapon is deflected by "+ HIS(target) +" "+ QSHORT(arm) +".");
        TWM(QCTNAME(TP) +" is ambushed by "+ QTNAME(target) +" but "+
		"appears unarmed.");		
		YOU(QCTNAME(TP) +" tried to ambush you but your "+ arm->short() +
		" protected you.");
        }
        else
        {
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +". You "+ 
        "strike "+ HIM(target) +" on the "+ hdesc +" but do no damage.");
        TWM(QCTNAME(target) +" is ambushed by "+ QTNAME(TP) +" but "+
		"appears unharmed.");		
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        " and "+ style +"s "+ HIS(TP) +" "+ qwp +" at you, striking "+		
		"you on the "+ hdesc +"! You feel unharmed though.");
        }
        arrow_missed(items, target);
        return;
        
    case 0..4:
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +". You "+ 
        "strike "+ HIM(target) +" on the "+ hdesc +" but do little damage.");
        TWM(QCTNAME(target) +" is ambushed by "+ QTNAME(TP) +" but "+ 
		HE(target) +" seems more surprised than anything.");		
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        "and ambushes you! "+ capitalize(HIS(TP)) +" "+ qwp +" strikes "+		
		"you on the "+ hdesc +", making it ache a bit.");
        arrow_hit(items, target);
        break;

    case 5..14:
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +". You "+ 
        "land a bruising strike on "+ HIS(target) +" "+ hdesc +".");
        TWM(QCTNAME(TP) +" ambushed "+ QTNAME(target) +", landing a "+ 
		"bruising strike on "+ HIS(target) +" "+ hdesc +"."); 		
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        "and ambushes you! "+ HE(TP) +" "+ style +"s "+ HIS(TP) +" "+ qwp +
		" at you and lands a bruising strike on your "+ hdesc +".");
        arrow_hit(items, target);
        break;

    case 15..29:
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +". You "+ 
        "land a painful strike on "+ HIS(target) +" "+ hdesc +".");
        TWM(QCTNAME(TP) +" ambushed "+ QTNAME(target) +", landing a "+ 
		"painful strike on "+ HIS(target) +" "+ hdesc +"."); 		
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        "and ambushes you! "+ HE(TP) +" "+ style +"s "+ HIS(TP) +" "+ qwp +
		" at you and lands a painful strike on your "+ hdesc +".");
        arrow_hit(items, target);
        break;

    case 30..44:
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +". You "+ 
        "strike "+ HIM(target) +" on the "+ hdesc +", opening a small "+
		"wound.");
        TWM(QCTNAME(TP) +" ambushed "+ QTNAME(target) +", striking "+ 
		HIM(target) +" on the "+ hdesc +" and opening a small wound."); 		
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        "and ambushes you! "+ HE(TP) +" "+ style +"s "+ HIS(TP) +" "+ qwp +
		" at you and strikes your "+ hdesc +", opening a small wound.");
        arrow_hit(items, target);
        break;

    case 45..59:
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +". You "+ 
        "strike "+ HIM(target) +" hard on the "+ hdesc +", causing a "+
		"serious injury.");
        TWM(QCTNAME(TP) +" ambushed "+ QTNAME(target) +", striking "+ 
		HIM(target) +" on the "+ hdesc +" and causing a serious injury."); 		
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        "and ambushes you! "+ HE(TP) +" "+ style +"s "+ HIS(TP) +" "+ qwp +
		" at you and strikes you hard on the  "+ hdesc +", causing a "+
        "serious injury.");
        arrow_hit(items, target);
        break;

    case 60..75:
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +". You "+ 
        "land a lucky strike on "+ HIS(target) +" "+ hdesc +", "+
        "causing "+ HIM(target) +" to reel backwards in terrible pain.");
        TWM(QCTNAME(TP) +" ambushed "+ QTNAME(target) +", landing a "+ 
		"lucky strike that leaves "+ QTNAME(target) +" reeling in pain."); 		
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        "and ambushes you! "+ HE(TP) +" "+ style +"s "+ HIS(TP) +" "+ qwp +
		" at you, landing a lucky strike on your "+ hdesc +" that causes "+
        "you to reel backwards in terrible pain.");
        arrow_hit(items, target);
        break;
		
    case 76..90:
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +". You "+ 
        "land a devastating strike on "+ HIS(target) +" "+ hdesc +", "+
        "causing "+ HIM(target) +" stagger back in debilitating pain.");
        TWM(QCTNAME(TP) +" ambushed "+ QTNAME(target) +", landing a "+ 
		"lucky strike that leaves "+ QTNAME(target) +" in debilitating pain."); 		
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        "and ambushes you! "+ HE(TP) +" "+ style +"s "+ HIS(TP) +" "+ qwp +
		" at you, landing a devastating strike on your "+ hdesc +" that "+
        "causes you to stagger back in debilitating pain.");
        arrow_hit(items, target);
        break;

    default:
        ME("In one smooth motion, you emerge from your concealed position "+ 
        "and "+ style +" your "+ wp +" at "+ QTNAME(target) +". You "+ 
        "land a perfect strike on "+ HIS(target) +" "+ hdesc +", "+
        "causing a mortal injury.");
        TWM(QCTNAME(TP) +" ambushed "+ QTNAME(target) +", landing a "+ 
		"mortal blow on "+ HIS(target) +" "+ hdesc +"."); 		
        YOU(QCTNAME(TP) +" suddenly emerges from a concealed position "+
        "and ambushes you! "+ HE(TP) +" "+ style +"s "+ HIS(TP) +" "+ qwp +
		" at you and lands mortal blow on your "+ hdesc +".");
        arrow_hit(items, target);
        break;
    }

}

