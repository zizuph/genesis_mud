/*
 * special/smash.c
 *
 * Port of the AA Smash to the shared combat library
 *
 * Created by Novo, May 2008
 *
 * Modified 6/26/2008 Novo added seteuid prior to pulp
 * Modified 7/12/2008 Novo fixed typo in "got good swing"
 * Modified 3/12/2008 Balance removed query_hitloc_factor mask
 * Modified 10/4/2009  Balance added set_tohit(85) as it was missing.
 * Modified 06/8/2019  Arman (AoB) revised caid from 70/35 to 75/40
 *                     and increased set_tohit to 95.
 * Modified 15/11/2019 Arman updated the special messages.
 */

#pragma strict_types

#include "../guild.h"

inherit AA_SPECIAL;

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <cmdparse.h>

#include "/std/combat/combat.h"
#include "/d/Genesis/specials/debugger/debugger_tell.h"


#define VALIDATE        "validate"

#define AA_ACTIVITY_MAPPINGS  (AA_DIR+"obj/captain_activity_mappings")
#define ACTIVITY_POINT_CHANGE  10


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
    setuid();
    seteuid(getuid());
    
    ::config_ability();
    set_combat_aid(75);

    // 10/2/2008 - Replaced Guild Stat with Dex because it takes
    //             dexterity to target someone's head
    set_stats(({ SKILL_AVG, TS_STR, TS_DEX, SKILL_END }) );    
    set_skills(({ SS_SMASH }) );
    // Can smash once every 15 seconds
    set_ability_prep_time(7);
    set_ability_cooldown_time(8);
    set_dt(W_BLUDGEON);
    set_ability_name("smash");
    set_ability_target(target_smash_head);
    
    // 10/4/2009 - Added set_tohit(85) to match guild docs, Petros
    // 06/8/2019 - Revised tohit to 95
    set_tohit(95);
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
}

public int
query_guild_stat_type(object player)
{
    if (IS_LAYMAN(player))
    {
        return SS_LAYMAN;
    }
    else
    {
        return SS_OCCUP;
    }
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

    object who = this_player();
    string weapon_short;
    string *attack_message;

    if(!hdesc)
        hdesc = "weak spot";
    
    weapon_short = items[0]->short();

    if (phurt>=0)
    {
        if (enemy->query_hp() <= 0)
        {
                attack_message = ({
                    "You smash " +enemy->query_the_name(who)+
                    " with your " +weapon_short+ " to a pulp!\n",
                    who->query_The_name(enemy)+ " smashes you " +
                    "with " +who->query_possessive()+ " " +
                    weapon_short+ " to a pulp!\n",
                    who->query_The_name(enemy)+ " smashes " +
                    enemy->query_the_name(who)+ " with " +
                    who->query_possessive()+ " " +weapon_short+ 
                    " to a pulp!\n" });
        }
        else 
        {
            switch (phurt)
            {
            case 0:
                attack_message = ({
                    "You only scared " +enemy->query_the_name(who)+
                    " with your " +weapon_short+ ", barely hitting " +
                    enemy->query_possessive()+ " " + hdesc + ".\n",
                    who->query_The_name(enemy)+ " only scared you " +
                    "with " +who->query_possessive()+ " " +
                    weapon_short+ ", barely hitting your " +hdesc+ ".\n",
                    who->query_The_name(enemy)+ " only scared " +
                    enemy->query_the_name(who)+ " with " +
                    who->query_possessive()+ " " +weapon_short+ 
                    ", barely hitting " +enemy->query_the_possessive_name(who)+
                    " " +hdesc+ ".\n" });
                break;
            case 1..3:
                attack_message = ({
                    "You bonk " +enemy->query_the_name(who)+
                    " with your " +weapon_short+ " on " +
                    enemy->query_possessive()+ " " + hdesc + ".\n",
                    who->query_The_name(enemy)+ " bonks you " +
                    "with " +who->query_possessive()+ " " +
                    weapon_short+ " on your " +hdesc+ ".\n",
                    who->query_The_name(enemy)+ " bonks " +
                    enemy->query_the_name(who)+ " with " +
                    who->query_possessive()+ " " +weapon_short+ 
                    " on " +enemy->query_the_possessive_name(who)+
                    " " +hdesc+ ".\n" });
                break;
            case 4..10:
                attack_message = ({
                    "You got a good swing at the " +hdesc+ " of " +
                    enemy->query_the_name(who)+ " with your " +
                    weapon_short+ ", BOING!!!\n",
                    who->query_The_name(enemy)+ " got a good swing " +
                    "at your "+ hdesc + " with " +
                    who->query_possessive()+ " " +weapon_short+ 
                    ", BOING!!!\n",
                    who->query_The_name(enemy)+ " got a good swing at " +
                    enemy->query_the_name(who)+ " with " +
                    who->query_possessive()+ " " +weapon_short+ 
                    ", BOING!!!\n" });
                break;
            case 11..25:
                attack_message = ({
                    "You skillfully hit the " +hdesc+ " of " +
                    enemy->query_the_name(who)+ " with your " +
                    weapon_short+ " with great damage.\n",
                    who->query_The_name(enemy)+ " skillfully hits " +
                    "your "+ hdesc + " with " +who->query_possessive()+ 
                    " " +weapon_short+ " with great damage.\n",
                    who->query_The_name(enemy)+ " skillfully hits " +
                    enemy->query_the_name(who)+ " with " +
                    who->query_possessive()+ " " +weapon_short+ 
                    " with great damage.\n" });
                break;
            case 26..50:
                attack_message = ({
                    "You smash the " +hdesc+ " of " +
                    enemy->query_the_name(who)+ " with a " +
                    "powerful swing of your " +weapon_short+ ".\n",
                    who->query_The_name(enemy)+ " smashes your " +
                    hdesc + " with a powerful swing of " +
                    who->query_possessive()+ " " +weapon_short+ ".\n",
                    who->query_The_name(enemy)+ " smashes " +
                    enemy->query_the_possessive_name(who)+ " " +hdesc+
                    " with a powerful swing of " +who->query_possessive()+ 
                    " " +weapon_short+ ".\n" });
                break;
            default:
                attack_message = ({
                    "You smash the " +hdesc+ " of " +
                    enemy->query_the_name(who)+ " with your " +
                    weapon_short+ ", nearly turning " +
                    enemy->query_objective()+ " into a pulp.\n",
                    who->query_The_name(enemy)+ " smashes your " +
                    hdesc + " with " +who->query_possessive()+ 
                    " " +weapon_short+ ", nearly turning you into a " +
                    "pulp.\n",
                    who->query_The_name(enemy)+ " smashes " +
                    enemy->query_the_possessive_name(who)+ " " +hdesc+
                    " with " +who->query_possessive()+ " " +
                    weapon_short+ ", nearly turning " +
                    enemy->query_objective()+ " into a pulp.\n" });
                break;
            }
        }
        
        // ACTIVITY CODE - 19 nov 2019
        if (random(100) < ACTIVITY_POINT_CHANGE)
        {
            if (AA_COUNCIL_OBJ->is_captain(this_player()->query_name()))
            {
                int captain_activity;
                
                captain_activity = AA_ACTIVITY_MAPPINGS->query_captain_activity_gauge(this_player()->query_name());
            
                captain_activity = captain_activity +1;
                
                if (captain_activity > 1000)
                {
                    captain_activity = 1000;
                }
                
                AA_ACTIVITY_MAPPINGS->set_captain_activity_gauge(this_player()->query_name(), captain_activity);
            }
        }

        who->catch_tell(attack_message[0]);
        enemy->catch_tell(attack_message[1]);
        who->tell_watcher(attack_message[2], enemy);

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
        write("You are about to smash your enemy, but some "+
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
    string * hitloc_descs = map(hitloc_ids, &operator([])(, HIT_DESC) @ &co->query_hitloc());
    int pos=member_array(location,hitloc_descs);

    if (pos<0)
    {
        return -1;
    }

    return hitloc_ids[pos];   
}

private mixed *
process_unspecified_targeting(object actor, object enemy)
{
    if (!objectp(enemy))
    {
        actor->catch_tell("Whom do you wish to smash?\n");
        return ({ });
    }
    
    switch (AA_OPTIONS_OBJ->query_option("smash", actor->query_real_name()))
    {
    case 1:
        return ({ enemy });
    
    case 0:
    default:
        int hitloc_id = get_hitloc_id(enemy, "head");            
        if (hitloc_id == -1)
        {
            // Can't find a head location. Just return.
            return ({ enemy });
        }
        return ({ ({ enemy, hitloc_id }) });            
    }    
}

public mixed *
target_smash_head(object actor, string arg)
{
    string method;
    object enemy;
    object * results;
    
    if (!strlen(arg)
        || sizeof(results = PARSE_THIS(arg, "[at] / [on] [the] %l")))
    {
        // We get here when they don't specify an argument, or the player
        // specifies only the target. In this case, we base their
        // actions on the options set.
        if (!strlen(arg))
        {
            enemy = actor->query_attack();
        }
        else
        {
            enemy = results[0];
        }
    
        return process_unspecified_targeting(actor, enemy);
    }    

    actor->catch_tell("Whom do you wish to smash?\n");
    return ({ });
}

public void hook_attack_object(object ob)
{
    ::hook_attack_object(ob);    
}


