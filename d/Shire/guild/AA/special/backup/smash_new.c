/*
 * special/smash.c
 *
 * Port of the AA Smash to the shared combat library
 *
 * Created by Novo, May 2008
 *
 * Modified 6/26/2008 Novo added seteuid prior to pulp
 * Modified 7/12/2008 Novo fixed typo in "got good swing"
 */

#pragma strict_types

#include "../guild.h"

inherit "/d/Shire/guild/AA/special/aa_special_new";
//inherit AA_SPECIAL;

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

#include "/std/combat/combat.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"


#define VALIDATE        "validate"


// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam,object * items);
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);
static mixed *          check_required_items(object actor, mixed * targets,
                                             string arg, int pretest);
public object *         target_smash_head(object actor, string arg);


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
    set_combat_aid(70);

    // 10/2/2008 - Replaced Guild Stat with Dex because it takes
    //             dexterity to target someone's head
    set_stats(({ SKILL_AVG, TS_STR, TS_DEX, SKILL_END }) );    
    set_skills(({ SS_SMASH }) );
    // Can smash once every 15 seconds
    set_ability_time(15);
    set_dt(W_BLUDGEON);
    set_ability_name("smash");
    set_ability_target(target_smash_head);
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
}

/*
 * Function name: calc_guildstat_modifier
 * Description  : This function by default takes the values that are
 *                set during set_guild_stat_modifier, and calculates
 *                a scaling mechanism for the special. It should
 *                return a value that modifies the input "res" down
 *                if the person does not have sufficient guild stat.
 * Arguments    : player - the player executing the special
 *                res    - the current damage value to be modified
 * Returns      : nothing
 */
static int
calc_guildstat_modifier(object player, int res)
{
    // Now we modify based on guild stat if it has been set
    int gstat_min_pct = query_guild_stat_minimum_percentage();
    int gstat_cap = query_guild_stat_cap();
    int gstat_type;

    if (IS_LAYMAN(player))
    {
        gstat_type = SS_LAYMAN;
    }
    else
    {
        gstat_type = SS_OCCUP;
    }

    return calc_guildstat_modifier_helper(player, res, gstat_type,
                                          gstat_min_pct, gstat_cap);
}

public int query_hitloc_factor()
{
    //Smash does not get to pick its hitloc, so we do not penalize it.
    return 100;
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
 * Returns      : nothing
 */
public void special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt,int phit, 
                int dam,object * items)
{

    object who=this_player();
    string text1,text2,weapon_short;
    
    weapon_short = items[0]->short();

    if (phurt>=0)
    {
        if (enemy->query_hp() <= 0)
        {
            text1 = " smashed ";
            text2 = " to a pulp!\n";
        }
        else 
        {
            switch (phurt)
            {
            case 0:
                text1 = " only scared ";
                text2 = ".\n";
                break;
            case 1..5:
                text1 = " bonked ";
                text2 = " on the "+hdesc+".\n";
                break;
            case 6..10:
                text1 = " got a good swing at ";
                text2 = ", BOING!!!\n";
                break;
            case 11..25:
                text1 = " skillfully hit ";
                text2 = " with great damage.\n";
                break;
            case 26..50:
                text1 = " smashed the "+hdesc+" of ";
                text2 = " with powerful swing.\n";
                break;
            default:
                text1 = " smashed ";
                text2 = " nearly to a pulp.\n";
                break;
            }
        }

        who->catch_tell("You"+text1+ enemy->query_the_name(who) +
            " with your " + weapon_short + text2);
        enemy->catch_tell(who->query_The_name(enemy) + text1 + 
            "you with " + HIS(who) + " " + weapon_short + text2);
        who->tell_watcher(QCTNAME(who)+text1+QTNAME(enemy)+" with "+
            HIS(who)+" "+weapon_short+text2, enemy);

        setuid();
        seteuid(getuid());
        if (enemy->query_hp() < 1) pulp_him(enemy, who);
    }
    else
    {
        who->add_panic(1);

        who->catch_tell("You try to smash "+enemy->query_the_name(who) + 
            " with your " + weapon_short+" but miss.\n");
        enemy->catch_tell(who->query_The_name(enemy) + " tries to hit you with "+
            HIS(who)+" "+ weapon_short+" but misses.\n");
        who->tell_watcher(QCTNAME(who)+" tries to hit "+QTNAME(enemy)+" with " +
            HIS(who)+ " "+weapon_short+" but misses.\n", enemy);
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
    
    /* 
     * If the player has no skill in smashing and is not practicing, 
     * s/he can't smash. 
     */ 
    if (!player->query_skill(SS_SMASH)) 
    { 
        player->catch_tell("You are not skilled in smashing!\n");
        send_debug_message(VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " is not skilled in smash.");
        return 0; 
    }

    // If it passes everything, return success
    return 1; 
}

static void ability_msg(object actor,mixed * targets,string arg)
{
    object target=targets[0];
    if (pointerp(target))
    {
        target=target[0];
    }    
    actor->catch_msg("You prepare to smash "+QTNAME(target)+".\n");
}


/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the Calian has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor, mixed * targets,
                     string arg, int pretest)
{
    object *clubs;
    
    if (!sizeof(clubs = filter(actor->query_weapon(-1), 
        &operator(==)(W_CLUB) @ &->query_wt())))
    {
        actor->catch_tell("Too late you realized that you have no club "+
            "to smash your enemy with.\n");
        return 0;
    }

    return ({ one_of_list(clubs) });
}

/*
 * Function name: hook_no_magic_attack_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC_ATTACK.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public void
hook_room_no_attack_fail(mixed reason, object room)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else
    {
        write("You are about to smash the head of your enemy, but some "+
            "magic presence stops you from crushing it.\n");
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

public object *
target_smash_head(object actor, string arg)
{
    object * results=
        target_one_other_present_living_or_enemy(actor,arg);
    
    if (!sizeof(results))
    {
        return ({ });
    }

    mixed * new_results=({ });    
    foreach (object target : results)
    {
        int hitloc_id=get_hitloc_id(target,"head");
        
	    if (hitloc_id==-1)
	    {
            new_results+=({ target });
	    }
	    else
	    {
	        new_results+=({ ({ target, hitloc_id }) });
	    }
	}
	return new_results;
}

public void hook_attack_object(object ob)
{
    ::hook_attack_object(ob);    
}


