/*
 * special/smack.c
 *
 * Port of the AA Smack to the shared combat library
 *
 * Created by Novo, May 2008
 *
 * Modified 6/26/2008 Novo added seteuid prior to pulp
 * Modified 7/24/2008 Novo chose a random shield if two were worn
 *
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

    // 10/2/2008 - Replaced Guild Stat with Con because it should take
    //             great constitution to bash someone using a shield
    set_stats(({ SKILL_AVG, TS_STR, TS_CON, SKILL_END }) );    
    set_skills(({ SS_BASH }) );
    // Can smack once every 15 seconds
    set_ability_time(15);
    set_dt(W_BLUDGEON);
    set_ability_name("smack");
    
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
    string shield_short;
    
    shield_short = items[0]->short();

    if (phurt>=0)
    {
        if (enemy->query_hp() <= 0)
        {
            who->catch_tell("You run into "+enemy->query_the_name(who)+". Badly shaken "+
                HE(enemy)+" falls flat under your "+shield_short+
                ". You start to jump on it and after you finish"+
                " there is only bloody pulp left on the ground.\n");
            enemy->catch_tell(who->query_The_name(enemy)+" runs into you. Badly shaken"+
                " you fall flat under "+HIS(who)+" "+shield_short+
                ". Then you feel another hit, and another, and"+
                " yet another...\n");
            who->tell_watcher(QCTNAME(who)+" runs into "+QTNAME(enemy)+
                ". Badly shaken "+HE(enemy)+" falls flat under "+
                HIS(who)+" "+shield_short+". "+QCTNAME(who)+
                " starts to jump on it and after "+HE(who)+
                " finishes there is only bloody pulp left on the"+
                " ground.\n", enemy);
        }
        else
        {
            switch (phurt)
            {
            case 0:
                who->catch_tell("You push your "+shield_short+" into "+enemy->query_the_name(who)+
                    " but "+HE(enemy)+" pushes it back.\n");
                enemy->catch_tell(who->query_The_name(enemy)+" pushes "+HIS(who)+" "+shield_short+
                    " into you. You push it back.\n");
                who->tell_watcher(QCTNAME(who)+" pushes "+HIS(who)+" "+shield_short+
                    " into "+QTNAME(enemy)+" who pushes it back.\n", enemy);
                break;
            case 1..5:
                who->catch_tell("You sidestep "+enemy->query_the_name(who)+"'s attack and hit "+
                    HIM(enemy)+" flat with your "+shield_short+
                    " into the back.\n");
                enemy->catch_tell(who->query_The_name(enemy)+" sidesteps your attack and hits you"+
                    " flat with "+HIS(who)+" "+shield_short+
                    " into the back.\n");
                who->tell_watcher(QCTNAME(who)+" sidesteps "+QTNAME(enemy)+
                    "'s attack and hits "+HIM(enemy)+" flat with "+
                    HIS(who)+" "+shield_short+" into the back.\n", enemy);
                break;
            case 6..10:
                who->catch_tell("You whack "+enemy->query_the_name(who)+" over the head with your "+
                    shield_short+". It makes loud BOING!!!\n");
                enemy->catch_tell(who->query_The_name(enemy)+" whacks you over the head with "+
                    HIS(who)+" "+shield_short+". It makes loud BOING!!!\n");
                who->tell_watcher(QCTNAME(who)+" whacks "+QTNAME(enemy)+
                    " over the head with "+HIS(who)+" "+shield_short+
                    ". It makes loud BOING!!!\n", enemy);
                break;
            case 11..25: 
                who->catch_tell("With a sharp turn you drive the edge of your "+
                    shield_short+" into "+enemy->query_the_name(who)+"'s stomach. "+
                    CAP(HE(enemy))+" folds gulping in pain.\n");
                enemy->catch_tell("With a sharp turn "+who->query_the_name(enemy)+
                    " drives the edge of "+HIS(who)+" "+shield_short+
                    " into your stomach. You fold gulping in pain.\n");
                who->tell_watcher("With a sharp turn "+QTNAME(who)+" drives "+
                    HIS(who)+" "+shield_short+" into "+QTNAME(enemy)+
                    "'s stomach. "+CAP(HE(enemy))+
                    " folds gulping in pain.\n", enemy);
                break;
            case 26..50:
                who->catch_tell("Using both hands you drive the edge of your "+
                    shield_short+" into "+enemy->query_the_name(who)+"'s throat. "+
                    CAP(HE(enemy))+
                    " makes bubling sound spitting blood all around.\n");
                enemy->catch_tell("Using both hands "+who->query_the_name(enemy)+
                    " drives the edge of "+HIS(who)+" "+shield_short+
                    " into your throat. You let out bubling sound spitting"+
                    " blood all around.\n");
                who->tell_watcher("Using both hands "+QTNAME(who)+" drives "+
                    HIS(who)+" "+shield_short+" into "+QTNAME(enemy)+
                    "'s throat. "+CAP(HE(enemy))+
                    " makes bubling sound spitting blood all around.\n", enemy);
                break;
            default:
                who->catch_tell("You charge into "+enemy->query_the_name(who)+" with your "+
                    shield_short+" ahead. "+CAP(HE(enemy))+
                    " rolls away terribly hurt.\n");
                enemy->catch_tell(who->query_The_name(enemy)+" charges into you with "+
                    HIS(who)+" "+shield_short+
                    " ahead. You roll away terribly hurt.\n");
                who->tell_watcher(QCTNAME(who)+" charges into "+QTNAME(enemy)+
                    " with "+HIS(who)+" "+shield_short+" ahead. "+
                    CAP(HE(enemy))+" rolls away terribly hurt.\n", enemy);
            }   
        }

        if (enemy->query_hp() < 1) 
        {
            setuid();
            seteuid(getuid());            
            pulp_him(enemy, who);
        }
        return;
    }
    else
    {
        who->add_panic(1);

        who->catch_tell("You cover your head with "+shield_short+" and run past "+
            enemy->query_the_name(who)+".\n");
        enemy->catch_tell(who->query_The_name(enemy)+" covers "+HIS(who)+" head with "+
            shield_short+" and runs past you.\n");
        who->tell_watcher(QCTNAME(who)+" covers "+HIS(who)+" head with "+
            shield_short+" and runs past "+QTNAME(enemy)+".\n", enemy);
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
     * If the player has no skill in shielding and is not practicing, 
     * s/he can't smack. 
     */ 
    if (!player->query_skill(SS_BASH)) 
    { 
        player->catch_tell("You are not skilled in shield bashing!\n");
        send_debug_message(VALIDATE, 
                           capitalize(player->query_real_name()) 
                         + " is not skilled in shield bash.");
        return 0; 
    }

    // If it passes everything, return success
    return 1; 
}


/*
 * Function name: check_required_items
 * Description  : Does some validation to make sure the player has
 *                all the equipment they need to perform the special.
 * Returns      : items that are required.
 */
static mixed * 
check_required_items(object actor, mixed * targets,
                     string arg, int pretest)
{
    object * shields;
    
    if (!sizeof(shields = filter(actor->query_armour(-1), 
        &operator(==)(A_SHIELD) @ &->query_at())))
    {
        actor->catch_tell("You forgot to wear a shield!\n");
        return 0;
    }
    return (({ one_of_list(shields) }));
}


static void ability_msg(object actor,mixed * targets,string arg)
{
    actor->catch_msg("You prepare to smack "+QTNAME(targets[0])+".\n");
}

