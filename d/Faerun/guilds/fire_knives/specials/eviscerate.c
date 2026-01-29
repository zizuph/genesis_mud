/*
 * Eviscerate combat special for the Fire Knives
 *
 * Nerull 2019, based on Slash special created 
 * by Petros(January 2009).
 */

#pragma strict_types

#include "../guild.h"

inherit "/d/Genesis/specials/std/damage";

//#include "/d/Genesis/specials/debugger/debugger_tell.h"

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

#include "/std/combat/combat.h"

//
// Disabled, should use log_file
//
//#define EVISCERATE_LOG(x,y)  write_file(FIREKNIVES_LOG_DIR + x, extract(ctime(time()), \
//                       4, 15) +" "+ y )
#define EVISCERATE_LOG(x, y)
                       
#define ACTIVITY_POINT_CHANGE  5
                                      

// Prototypes
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam, mixed * items,
                                        int result);
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);
public int              force_fail(object player, mixed * items, 
                                   object enemy, int resist, int result);

// Global Variables


/*
 * Function:    query_ability_in_cooldown
 * Description: This checks whether the ability is currently in the
 *              cooldown mode. It checks the alarm to see if it
 *              is still running.
 * Arguments:   player - player to check the ability on
 * Returns:     0/1 - is not cooling down/is cooling down
 */
public int
query_ability_in_cooldown(object player)
{
    if (!objectp(player))
    {
        return 0;
    }

    if (!IN_ARRAY(player, m_indices(cooldown_alarms)))
    {
        return 0;
    }
    
    if (get_alarm(cooldown_alarms[player]))
    {
        return 1;
    }
    
    return 0;    
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
    //set_combat_aid(70);
    set_combat_aid(55);
    set_tohit(95); // 84% chance of hitting
    set_dt(W_SLASH | W_IMPALE);
    set_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX, 
                  SKILL_WEIGHT, 20, TS_WIS }) );    
    set_skills(({ SS_ART }) );
    set_ability_prep_time(7);
    set_ability_cooldown_time(8);
    set_ability_name("eviscerate");
    
    set_guild_stat_modifier(SS_OCCUP, 20, 100);
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
 *                items - 
 *                result - result of cb_tohit
 * Returns      : nothing
 */
public varargs void 
special_did_hit(int aid, string hdesc, int hid, 
                int phurt, object enemy, int dt, int phit, 
                int dam, mixed * items, int result)
{
    string *attack_message;
    object tp = this_player();
    object target = enemy;
    string hitloc = hdesc;
    
    object weaponob;
    

    weaponob = tp->query_weapon(W_RIGHT);
    
    
    string weapon = weaponob->query_short();
    
    
    if (phurt >= 0)
    {
        switch(phurt)
        {
        case 0:
            attack_message = ({
              "You side step an attack from "+target->query_the_name(tp)
              +", and spin "
              +"around slashing your "+weapon 
              +" to meet " + target->query_possessive() + " flesh, but a "
              +"whistling slush alerts you of your move's miscalculation "
              +"before you come to a full stop and turn to face " 
              +target->query_objective()+".\n",

              tp->query_The_name(target)
              + " side steps to avoid your oncoming attack, "
              +"spinning around with "+tp->query_possessive()+" "+weapon+" "
              +"whistling towards you, but you stumble backwards a "
              +"few steps as they slash the air in front of you, avoiding "
              +"the attack.\n",

              QCTNAME(tp)+ " side steps to avoid "+QTNAME(target)
              +"'s incoming attack, spinning around with "
              +tp->query_possessive()
              +" "+weapon+" whistling towards "
              +target->query_objective()+", but just before the blades meet "
              +"flesh, "+target->query_pronoun()+" stumbles backwards a "
              +"few steps in panic and they slash only air.\n"              
            });
            break;
            
        case 1..2:
        
            attack_message = ({
                "Holding your " + weapon + " to its opposite hand's side " +
                "you leap backwards to avoid an incoming blow and slash " +
                "out towards " + target->query_the_name(tp) + " hitting " + 
                tp->query_possessive() + " "+hitloc + ". Blood oozes out " +
                "from the open wound as you land in a crouch.\n",

                "Avoiding a desperate attack of yours, " 
                +tp->query_the_name(target) +
                ", leaps backwards while slashing out with " 
                +tp->query_possessive() +
                "along the length of your " 
                + hitloc+ ". Blood oozes forward from " + 
                "the open wound, through which you see " 
                +tp->query_objective() + 
                "land in a crouch.\n",

                "Avoiding a desperate attack by " + QTNAME(target) + 
                ", " + QTNAME(tp) + " leaps backwards, slashing out with "
                + tp->query_possessive() +" "+weapon+" across " 
                + QTNAME(target) + "'s " + hitloc + ", causing blood to " +
                "ooze forth as "+tp->query_pronoun()+" lands in a crouch.\n"
            });
            break;
        
        case 3..25:
            attack_message = ({
                
            "Parrying an attack from "+target->query_the_name(tp)+" with "
            +"your "+weapon+", you quickly move to the side "
            +"and stab " +target->query_the_name(tp)+ "'s " 
            +hitloc+ " swiftly with the blade!\n",
              
            "You swing at "+tp->query_the_name(target)+" but "
            +tp->query_pronoun()
            +" parries your attack with "+tp->query_possessive()+" "
            +weapon+". Suddenly, "+tp->query_the_name(target)
            +" steps to your side and stabs your "+hitloc+" with the blade!\n",
            
            "As "+target->query_the_name(tp)+" takes a swing at "
            +QTNAME(tp)+", the blow is "
            +"parried by "+QTNAME(tp)+"'s "
            +weapon+"! "+QCTNAME(tp)+" swiftly steps aside and stabs "
            +target->query_the_name(tp)+" in the "+hitloc
            +" with the blade!\n"          
            });
            break;
        
        case 26..50:
            attack_message = ({
              
              "You place your right foot in front of your left and "
              +"throw your weight from your shoulder forward, rolling "
              +"and landing on your knee at "
              +target->query_the_name(tp)+"'s side. With your "
              +weapon+" in a "
              +"reverse grip, you stab backwards into "
              +target->query_possessive()
              +" "+hitloc
              +" with the blade with deadly accuracy, twisting it before "
              +"pulling it back out from a bleeding wound.\n",

              "You lose sight of "+tp->query_the_name(target)+" as "
              +tp->query_pronoun()+" rolls forward, "
              +"landing by your side and dives "+tp->query_possessive()
              +" "+weapon
              +" into your "+hitloc+" before you can stop "
              +tp->query_objective()
              +". A wave of excrutiating pain flows throw your whole "
              +"body as you feel the blade ripping and leaving "
              +"your flesh. Before you can "
              +"clutch your now pulsating wounds, you stumble to "
              +"the side and almost fall "
              +"from the pain.\n",

              QTNAME(tp)+" throws "+tp->query_possessive()+" weight on "
              +tp->query_possessive()
              +" right foot, "+tp->query_possessive()
              +" whole body following as "
              +tp->query_pronoun()+" rolls to the side of "
              +QTNAME(target)
              +" and lands on one knee with "+tp->query_possessive()
              +" "+weapon+" in a reverse grip facing forward from "
              +tp->query_the_name(target)
              +" and stabs backwards with deadly accuracy, sinking "
              +tp->query_possessive()+" blade into "
              +target->query_the_name(tp)+"'s "+hitloc+", twisting "
              +"and pulling it back out, leaving bleeding wounds.\n"  
            });
            break;
            
            
        case 51..75:
            attack_message = ({
                
              "You leap sideways to evade an incoming attack and dive in " 
              +"a flurry of lightening fast slashes with your "+weapon
              +" like a thousand scarlet kisses. " 
              +target->query_the_name(tp) 
              +" frantically tries to avoid each blow but only meets another " 
              +"with each one of " + tp->query_possessive() 
              +" movements. You " 
              +"take a step back to regain your stance as blood "
              +"starts flowing "  
              +"from " + tp->query_possessive() + " open wounds.\n",
 
              "You lose your balance and open your eyes in shock as you see " 
              +"that " + tp->query_the_name(target) 
              +" avalanches towards you " 
              +"in a flurry of lightening fast slashes on your " 
              +hitloc+ ". "  
              +"Trying to avoid the rain of blows only causes "
              +"each movement to " 
              +"be met with another. You gasp for breath as " 
              +tp->query_the_name(target) 
              +" takes a step back, a viscious smile on " 
              +tp->query_possessive()  
              +" face.\n",

              "You hear a surprised gasp as " + QTNAME(tp) 
              + " launches with " 
              +"amazing speed at "+target->query_the_name(tp)
              +" in a flurry of wild " 
              +"slashes focused on " + tp->query_possessive() 
              +" " +hitloc+ ". " 
              +"Heavy breathing is heard from "+target->query_the_name(tp)
              +" as if in " 
              +"a state of shock after " + QTNAME(tp) 
              + " takes a step back, " 
              +"leaving "+target->query_the_name(tp)
              +" exhasperatedly trying to regain " 
              +"strength as blood pours from " + tp->query_possessive() 
              + " open " 
              +"wounds.\n"
            });
            break;
            
            
        case 76..99:
            attack_message = ({

                "Crouching low to avoid a blow, you leap forward towards " 
                +target->query_the_name(tp)+
                " and plunge your " + weapon + " deep into " 
                +target->query_possessive() + " "+ hitloc 
                +" in a swift slide between " 
                +target->query_possessive() 
                +" legs, pulling it back out with the momentum force as "
                +"you rise from behind " + target->query_objective() 
                +" and kick " + target->query_objective() 
                +" from behind. " + target->query_the_name(tp) 
                +" stumbles forward holding " 
                +target->query_possessive() + " "+ hitloc
                +" in a clutch, blood pouring from the wound.\n",

                "You take a swing at " + QTNAME(tp) + " but miss as "
                +tp->query_pronoun()
                +" crouches low to avoid it and come at you with "
                +"incredible speed. Before "
                +"you can move, " +QTNAME(tp)+ " plunges " 
                +tp->query_possessive()  
                + weapon + " into your " + hitloc + ". The sharp " 
                +"pain turns into excrutiating agony as they once "
                +"again leave your body and blood starts pouring out "
                +"of the wound. You clutch your " 
                +hitloc + " and feel a strong force pushing you from "
                +"behind, making you stumble forward in confusion.\n",

                "Crouching low to avoid a blow by "
                +target->query_the_name(tp)+", you see " 
                +QTNAME(tp) + " dashes at "+target->query_the_name(tp)
                +" with lightening fast speed, plunging " 
                +tp->query_possessive() + weapon + " into "
                +target->query_the_name(tp)+"'s " + hitloc 
                +" while disappearing between " + tp->query_possessive() 
                +" legs after retrieving the blade. "+QTNAME(tp)
                +" suddenly appears behind " + target->query_the_name(tp)
                +" and sending " + tp->query_gender() + " stumbling " 
                +" forward clutching a blood gushing wound in " 
                +target->query_possessive() +" hands.\n"
            });
            break;
            
        default:
            attack_message = ({
                      
              "You quickly step in close and jab your "
              +weapon+" into the sternum of "
              +target->query_the_name(tp)+" with such force that "
              +target->query_possessive()+" eyes widen "
              +"and mouth open. Not giving pause you quickly pull out the "
              +weapon+" and "
              +"spin around your opponent for so plunging your "
              +weapon+" into "
              +target->query_possessive()
              +"'s lower back into the sweet spot, the abdominal "
              +"aorta. You twist your "+weapon
              +" and rapidly pull it out. Blood starts "
              +"gushing out the wound. "
              +target->query_The_name(tp)+" falls to "
              +target->query_possessive()+" knees and then forward as "
              +target->query_pronoun()
              +" goes unconciouss from the sudden blood loss.\n",
                             
              
              tp->query_The_name(target)+" steps in close and jabs "
              +tp->query_possessive()
              +" "+weapon+" into your sternum with such force that your eyes "
              +"widen and mouth open. Without giving pause, "
              +QTNAME(tp)
              +" quickly pulls out the "+weapon
              +" and spins around you, "
              +"plunging "+tp->query_possessive()+" "+weapon
              +" into your "
              +"lower back's sweet spot, the abdominal aorta. You feel a "
              +"wave of excrutiating pain as the blade is twisted inside "
              +"you before being pulled out, ripping your aorta open, "
              +"freeing the way for a gush of blood to spurt out of the "
              +"open wound. You fall to your knees first, then forward "
              +"face flat on the ground before everything turns to black.\n",

              QCTNAME(tp)+" steps in close and jabs "
              +tp->query_possessive()+" "+weapon+" into "
              +target->query_the_name(tp)+"'s sternum with such force that "
              +target->query_possessive()+" eyes widen and "
              +target->query_possessive()+" mouth opens. Without giving pause, "
              +QTNAME(tp)+" quickly pulls out the "+weapon
              +" and spins around "
              +target->query_the_name(tp)+", plunging his "
              +weapon+" into "
              +target->query_possessive()
              +" lower back's sweet spot, the abdominal "
              +"aorta. "+target->query_The_name(tp)
              +"'s face contorts in an expression of "
              +"pure horror as "+QTNAME(tp)+" twists "
              +tp->query_possessive()
              +" blade inside "+target->query_the_name(tp)
              +" before pulling it out "
              +"with a shredding sound of ruptured flesh, leaving "
              +"behind a gushing "
              +"wound. "+target->query_The_name(tp)
              +" falls first to "
              +target->query_possessive()
              +" knees, then face flat forward on a pool "
              +"of blood.\n" 
            });
        }
    
        tp->catch_tell(attack_message[0]);
        target->catch_tell(attack_message[1]);
        tp->tell_watcher(attack_message[2], target);
        
        // A successful attack generates panic
        tp->add_panic(-3 - phurt / 5);        
    }
    else
    {
        tp->catch_tell("You squint your eyes in anger at " 
        +target->query_the_name(tp)
        +" as you make an attempt to eviscerate your "
        +"target, but hesitate and miss your " 
        +"chance to close in and engage.\n");

        target->catch_tell(tp->query_The_name(target)
        + " makes a move towards you but " 
        +"quickly takes a step back and squints "
        +tp->query_possessive()+" eyes angrily at you, having missed an " 
        +"opportunity to close in on you for an attack.\n");

        tp->tell_watcher_miss(QCTNAME(tp)+ " makes a move towards " 
        +QTNAME(target)
        +", but quickly takes a step back and squints "
        +tp->query_possessive()+" eyes angrily at " 
        +target->query_objective()+", having missed an "
        +"opportunity to close in on an attack.\n");
        
        // A miss emboldens enemies
        tp->add_panic(1);
    }
    
    EVISCERATE_LOG("eviscerate_dmg_log",
    "The Assassin " +this_player()->query_name() 
    +" performed eviscerate at "
    +target->query_name()+" for Dam:"+dam+"/Phit:"+phit+".\n");
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(tp);
    }
    
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
            "The Fist " +this_player()->query_name() +" gained a point(eviscerate).\n");
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
            "The Inquisitor " +this_player()->query_name() +" gained a point(eviscerate).\n");
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
            "The Elder " +this_player()->query_name() +" gained a point(eviscerate).\n");
        }
    }
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
    object *blades;
    
    if (!sizeof(blades = filter(actor->query_weapon(-1), 
        &operator(==)(W_KNIFE) @ &->query_wt())))
    {
        actor->catch_tell("Eviscerate requires a dagger or a knife wielded "
        +"in the right hand!\n");
        return 0;
    }

    return ({ blades });
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
    
    object weaponob;
    
    weaponob = player->query_weapon(W_RIGHT);
    
    if(!objectp(weaponob))
    {
        player->catch_tell("You need a blade wielded in the right hand!\n");
        
        return 0;
    }
    
    if (weaponob->query_wt() != W_KNIFE)
    {
        player->catch_tell("Your weapon in your right hand is not a dagger "
        +"or a knife!\n");
        
        return 0;
    }
    
    
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(player->query_name()) < AB2)
    {
        player->catch_tell("You are not qualified to use this ability.\n");
        
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
    
    enemy = targets[0];
    
    object blind_token;
    object silence_token;
	object stun_token;
    object backstab_token;
    
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(player->query_name()) < AB2)
    {
        player->catch_tell("You are not qualified to use this ability.\n");
        
        return 0;
    }
    
    if (!validate_requirements(player))
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
        +"not eligible for eviscerate yet!\n");

        return 0;
    }
    
    if (present("_silence_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent garotte of the "
        +"target, eviscerate is not yet ready to be used! Patience!\n");

        return 0;
    }
	
	if (present("_stun_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent stun of the "
        +"target, eviscerate is not yet ready to be used! Patience!\n");

        return 0;
    }
    
    if (objectp(backstab_token = present("_backstab_cooldwn_obj", player)))
    {
        player->catch_tell("Due to your recent backstab of the "
        +"target, eviscerate is not yet ready to be used! Patience!\n");

            return 0;
    }
    
    if (BACKSTAB_ABILITY->query_ability_in_cooldown(player))
    {
        player->catch_msg("You are not yet ready to do that!\n");
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
}


/*
 * Function name: force_fail
 * Description:   This function allows the special to force a failure for
 *                whatever reason. Called right before execution at the end
 *                of the delay
 * Arguments:     1. (object)   The player
 *                2. (object) The targets
 *                3. (int *)    Resistance values corresponding to each target
 *                4. (int)      The attempt result as returned by
 *                              query_casting_success()
 * Returns:       1 for failure, 0 for not.
 */
public int 
force_fail(object player, mixed * items, object enemy, 
           int resist, int result)
{
    if (!validate_requirements(player))
    {
        return 1;
    }

    return 0;
}


/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stopped_ability(object ability,object player)
{
    // Don't display any messages
}


public void
hook_special_in_cooldown()
{   
    write("You are not yet ready to eviscerate your enemy!\n");     
}


/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    if (!objectp(this_player()))
        return;
    
    write("You feel ready to execute eviscerate or any other primary ability again.\n");    
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
    write("Your target is no longer present.\n");    
}


static void 
ability_msg(object actor,mixed * targets,string arg)
{
    write("You tighten the grip on your blade while focusing "
    +"on predicting the movement of your target.\n");    
}
