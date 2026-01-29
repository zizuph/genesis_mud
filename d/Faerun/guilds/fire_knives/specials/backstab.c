/*
 * Backstab
 *
 * Custom backstab which is modified for the Fire Knives Assassin guild.
 * It is the same as the std backstab, except messages and caid set 
 * Altered custom messages - Nerull 2018 - 12 -13
 *
 * 2019-06-12 - Carnak:
 *      Made some changes to the main backstab ability which required a fix in
 *      this version. You no longer use special_did_hit, but backstab_did_hit
 *      instead, removed some of the balance aspects in the special_did_hit from
 *      this version as they were obsolete.
 *
 * 2020-06-15 - Carnak:
 *      The original backstab ability was updated to ignore shields, this
 *      ability was cleaned to remove some code that was preventing it from
 *      mimicing the original ability. Primarily set_dt in the config_ability.
 *
 * 2021-04-01 - Carnak:
 *      Due to increases in overall special damage, one-shot abilities like
 *      backstab needs to be under harsher regulations. I am therefore reducing
 *      the effect of the ability to match that of the original backstab. This
 *      is done by reducing the cooldown of the ability from 27 to 15 seconds.
 *      Changes will occur to all abilities which have ambushing capabilities,
 *      before weeks end.
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/backstab.c";

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
#include <stdproperties.h>
#include <cmdparse.h>

#include "/std/combat/combat.h"
#include "/d/Faerun/guilds/fire_knives/guild.h"

// Defines
// Disabled, Log files should use log_file() 
// #define BACKSTAB_LOG(x,y)  write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \ 4, 15) +" "+ y )
#define BACKSTAB_DEBUG_LOG(x,y)   write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
                            4, 15) +" "+ y )
                       
#define BACKSTAB_LOG(x, y)  
//#define BACKSTAB_DEBUG_LOG(x, y) 

#define ACTIVITY_POINT_CHANGE  5


/*
 * Function name:   hook_special_in_cooldown
 * Description:     This hook prints a message if the ability is in cooldown.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_in_cooldown()
{
    this_player()->catch_msg("You're not ready to backstab again.\n");
} /* hook_special_in_cooldown */


/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void
hook_special_complete()
{
    this_player()->catch_msg("You feel ready to execute backstab or any "
    +"other primary ability again.\n");
} /* hook_special_complete */


/*
 * Function name: config_ability
 * Description  : Main fuction that configures what the special
 *                should look like. Set basic things like combat
 *                aid and the skills to be used for calculating
 *                damage and of course, the name.
 * Arguments    : None
 * Returns      : Nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_combat_aid(153);
    set_ability_cooldown_time(17);
    set_stats( ({ SKILL_WEIGHT, 40, TS_DEX, SKILL_WEIGHT, 40, TS_STR, 
                  SKILL_WEIGHT, 20, TS_WIS }) );
} /* config_ability */

/*
 * Function name:   backstab_did_hit
 * Description:     Mask this function to process when the special scores.
 *                  Descriptions seen by everyone are set here.
 * Arguments:       1. (int) aid   - attack id
 *                  2. (string) hdesc - hit description
 *                  3. (int) hid   - 
 *                  4. (int) phurt - extent of damage
 *                  5. (object) enemy - person being hit by special
 *                  6. (int) dt    - damage type
 *                  7. (int) phit  - 
 *                  8. (int) dam   - damage amount
 *                  9. (mixed *) items - 
 *                  10. (int) result - result of cb_tohit
 * Returns:         Nothing
 */
public varargs void
backstab_did_hit(int aid, string hdesc, int hid, int phurt, object enemy,
                int dt, int phit, int dam, mixed *items, int result)
{
    object knife;
    string stab_desc;
    
    /*
     * Pick the best weapon in the array, or first knife in array if the 
     * best wielded weapon isnt a knife.
     */
    if (!objectp(knife = query_best_wielded_weapon(this_player())) ||
        !IN_ARRAY(knife, items))
        knife = items[0];
        
    /*knife = this_player()->query_weapon(W_LEFT);
    
    this_player()->catch_msg("You try to use the "+knife->short()
    +" you wield in your left hand for the backstab!\n\n");
    
    if (knife == 0)
    {
        knife = this_player()->query_weapon(W_RIGHT);
        
        this_player()->catch_msg("Lacking a blade in the right hand, you try to use "
        +"the "+knife->short()+" you wield in your right hand for the backstab!\n");
    }*/
    
    if (knife == 0)
    {
        this_player()->catch_msg("Your backstab fails as you wield no dagger in either "
        +"hand!\n");
        
        return;
    }
    
    int max_dmg, prc_dmg, wep_dmg, wep_pen, wep_lev;
    
    max_dmg = calculate_damage(this_player(), enemy, items, 0, result);
     
    prc_dmg = dam * 100 / max_dmg;
    wep_pen = calc_base_pen(items);
    wep_lev = this_player()->query_skill(SS_WEP_KNIFE);
    wep_dmg = F_PENMOD(wep_pen, wep_lev) * prc_dmg / 100;
    
    BACKSTAB_DEBUG_LOG("backstab_debug_log", "FK " +this_player()->query_name() +"'s BS data: Maxdmg: "+max_dmg+", prc_dmg: "+prc_dmg+", wep_pen: "+wep_pen+", wep_lev: "+wep_lev+", wep_dmg: "+wep_dmg+", DAM: "+dam+".\n");
    
    /* Miss the attack */
    if (dam < 1)
    {
        /*this_player()->catch_msg("You twirl your "+ knife->short()
        +"in a reverse grip, sneaking up behind " + QTNAME(enemy) 
        +" aiming for "+enemy->query_possessive()+" back, but "
        +enemy->query_pronoun()+" turns around just in time, "
        +"leaping backwards and revealing your intent!\n");

        this_player()->tell_watcher(QCTNAME(this_player()) 
        +" sneaks up behind " + QTNAME(enemy) + " with "
        +this_player()->query_possessive()+" "
        +knife->short()+" raised in "+this_player()->query_possessive()
        +" hand, but " 
        + QTNAME(enemy) + " leaps backwards just in time to "
        +"dodge "+this_player()->query_possessive()
        +" deadly attack!\n", enemy); 

        enemy->catch_msg("Your hairs stand on end as you suddenly "
        +"become aware of "+QCTNAME(this_player()) + "'s presence "
        +"coming up behind you. You turn around and quickly jump "
        +"backwards to dodge "+this_player()->query_possessive()
        +" deadly attack!\n");*/
        
   
        this_player()->catch_msg("You twirl your "+ knife->short()
        +" in a reverse grip, sneaking up behind " + QTNAME(enemy) 
        +" aiming for "+enemy->query_possessive()
        +" back and stabs forcefully, but the "+ knife->short()+" fails to penetrate the armor!\n");
        
        
        this_player()->tell_watcher(QCTNAME(this_player()) 
        +" sneaks up behind " + QTNAME(enemy) + " with "
        +this_player()->query_possessive()+" "
        +knife->short()+" raised in "+this_player()->query_possessive()
        +" hand and stabs forcefully, but the "+ knife->short()+" fails to penetrate the armor!\n", enemy); 

        enemy->catch_msg("Your hairs stand on end as you suddenly "
        +"become aware of "+QCTNAME(this_player()) + "'s presence "
        +"coming up behind you. You feel a powerful stab in the back, "
        +"but your armor seems to stop the blow!\n");
        
        return;
    }

    switch(phurt)
    {
        case 0..5:
           stab_desc = " weakly";
           break;
        case 6..49:
           stab_desc = "";
           break;
        case 50..75:
           stab_desc = " forcefully";
           break;
        case 76..99:
           stab_desc = " deeply";
           break;
        default:
           stab_desc = " fatally";
    }
        
    this_player()->catch_msg("You twirl your "+knife->short()+" in a reverse "
    +"grip, and silently sneak up behind "+QTNAME(enemy)+", catching "
    +enemy->query_objective()+" unaware and plunge your "+knife->short()
    +stab_desc+" into "+enemy->query_possessive()
    +" back! " + capitalize(enemy->query_possessive()) + " body tenses "
    +"up as you pull your "+knife->short()+" back out and blood starts "
    +"pouring from the open wound!\n");

    this_player()->tell_watcher(QCTNAME(this_player())+" rises from the "
    +"shadows behind "+QTNAME(enemy)+", "+LANG_ADDART(knife->short())
    +" in hand and plunges it"+stab_desc+" into "+QTNAME(enemy)+"'s back! " 
    +QCTNAME(enemy)+"'s body freezes from the "
    +"shock as blood starts pouring from the wound!\n", enemy); 

    enemy->catch_msg("You feel your whole body tense and freeze as a "
    +"sting from "+QTPNAME(this_player())+" "+LANG_ADDART(knife->short())
    +" plunges"+stab_desc+" into your back! You gasp in fear as a "
    +"liquid warmth "
    +"starts covering your back!\n");

    if(hidden_modifier[this_player()])
    this_player()->catch_msg(QCTNAME(enemy) + " could not see you coming "
    +"and is rendered defenseless against your deadly ambush!\n");
    
    BACKSTAB_LOG("backstab_dmg_log",
    "The Assassin " +this_player()->query_name() 
    +" performed backstab at "
    +enemy->query_name()+" for Dam:"+dam+"/Phit:"+phit+".\n");
    
        if (random(100) < ACTIVITY_POINT_CHANGE)
    {
        if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()))
	    {
            int fist_activity;
            fist_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(this_player()->query_name());
        
	        fist_activity = fist_activity +1;
            
            if (fist_activity > 1000)
            {
                fist_activity = 1000;
            }
            
	        FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(this_player()->query_name(), fist_activity);
            
            ACTIVITY_LOG("activity_point_log",
            "The Fist " +this_player()->query_name() +" gained a point(backstab).\n");
        }
        
        if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()))
	    {
            int mentor_activity;
            mentor_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(this_player()->query_name());
        
	        mentor_activity = mentor_activity +1;
            
            if (mentor_activity > 1000)
            {
                mentor_activity = 1000;
            }
            
	        FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(this_player()->query_name(), mentor_activity);
            
            ACTIVITY_LOG("activity_point_log",
            "The Inquisitor " +this_player()->query_name() +" gained a point(backstab).\n");
        }
        
        if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()))
	    {
            int boss_activity;
            boss_activity = FIREKNIVES_MAPPINGS->query_assassin_council_activity_gauge(this_player()->query_name());
        
	        boss_activity = boss_activity +1;
            
            if (boss_activity > 1000)
            {
                boss_activity = 1000;
            }
            
	        FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(this_player()->query_name(), boss_activity);
            
            ACTIVITY_LOG("activity_point_log",
            "The Elder " +this_player()->query_name() +" gained a point(backstab).\n");
        }
    }
           
    /* If the target dies, we trigger an original message instead of did_hit */
    if(enemy->query_hp() <= 0)
    {        
        if(enemy->query_prop(LIVE_I_UNDEAD))
        {
            enemy->tell_watcher("The " + knife->short() 
            +" sinks deeply into " + QTPNAME(enemy) + " back "
            +"tearing through the layers of its rotting carcass which "
            +"crumbles into dust under your blade, "
            +"leaving a gaping hole that destabilizes its physical "
            +"structure, turning " 
            +enemy->query_objective() + " into nothingness.\n");
            
            enemy->catch_msg("The " + knife->short() 
            + " sinks deeply into your back, tearing through the layers "
            + "of your undead body which turns to dust and "
            +"dissolves you into nothingness.\n");
        }
        else if (enemy->query_humanoid())
        {
            enemy->tell_watcher("The " + knife->short()
            +" sinks deeply into " + QTPNAME(enemy) + " back, is twisted "
            +"and pulled back out, shredding flesh and bone on its "
            +"way out. The wound left behind is so grievous "
            +"that " + enemy->query_pronoun() 
            +" collapses into the ground, dying instantly.\n");

            enemy->catch_msg("The " + knife->short() 
            +" sinks deeply into your back. You feel it twisting inside your "
            +"body and coming back out, driving your organs "
            +"outwards and leaving you strengthless. You collapse on "
            +"your knees and fall face flat onto the ground, dead.\n");
        }
        else
        {
            enemy->tell_watcher("The " + knife->short() +" sinks deeply into " 
            + QTPNAME(enemy) + " back, is twisted "
            +"and pulled back out, shredding flesh and bone on its "
            +"way out. The wound left behind is so grievous "
            +"that " + enemy->query_pronoun() 
            +" collapses into the ground, dying instantly.\n");

            enemy->catch_msg("The " + knife->short()
            +" sinks deeply into your back. You feel it twisting inside your "
            +"body and coming back out, driving your organs outwards "
            +"and leaving you strengthless. You collapse on "
            +"your knees and fall face flat onto the ground, dead.\n");         
        }
    }
} /* backstab_did_hit */

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
    
    object blind_token;
    object silence_token;
    
   // object *obb;
    
    enemy = targets[0];

    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }

    if (!player->query_skill(SS_ART))
    {
        player->catch_tell("You are not skilled the arts of Assassination!\n");

        return 0;
    }
    
    if (STUN_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing your stun your opponent!\n");
        return 0;
    }
    
    if (EVADE_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing to evade your opponent!\n");
        return 0;
    }
    
    if (BLIND_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing to blind your opponent!\n");
        return 0;
    }
    
    if (EVISCERATE_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing to eviscerate!\n");
        return 0;
    }
    
    if (BACKSTAB_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing to backstab!\n");
        return 0;
    }
    
    if (GAROTTE_ABILITY->query_ability_preparing(player))
    {
        player->catch_msg("You are preparing to garotte your opponent!\n");
        return 0;
    }
    
    if (present("_blind_cooldwn_obj", player))
    {
        player->catch_tell("Your target is either blinded already or "
        +"is still recovering from the effect and is therefore "
        +"not eligible for backstab yet!\n");

        return 0;
    }
    
    if (present("_silence_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent garotte of the "
        +"target, backstab is not yet ready to be used! Patience!\n");

        return 0;
    }
	
	if (present("_stun_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent stun of the "
        +"target, backstab is not yet ready to be used! Patience!\n");

        return 0;
    }
    
    
    if (STUN_ABILITY->query_ability_in_cooldown(player)
        || BLIND_ABILITY->query_ability_in_cooldown(player)
        || GAROTTE_ABILITY->query_ability_in_cooldown(player)
        || BACKSTAB_ABILITY->query_ability_in_cooldown(player)
        || EVADE_ABILITY->query_ability_in_cooldown(player)
        || EVISCERATE_ABILITY->query_ability_in_cooldown(player))
    {
        player->catch_msg("You are not yet ready to do that!\n");
        return 0;
    }

    // If it passes everything, return success
    return 1;
} /* check_valid_action */
