/* /d/Faerun/guilds/vampires/specials/bloodletter.c
 *
 * Combat special for the vampires.
 *
 * Nerull 2020
 *
 */

#pragma strict_types
inherit "/d/Genesis/specials/std/damage";

#include "../guild.h"



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

#include "/std/combat/combat.h"

#define POSSESSIVE(x) x->query_possessive()
#define OBJECTIVE(x)  x->query_objective()
#define PRONOUN(x)    x->query_pronoun()
#define HIS(x)        x->query_possessive()
#define HIM(x)        x->query_objective()
#define HE(x)         x->query_pronoun()

#define TEST_LOG(x,y)  write_file(VAMPIRES_LOG_DIR + x, extract(ctime(time()), \
                       4, 15) +" "+ y )


public void config_ability()
{
    ::config_ability();
    set_combat_aid(100);
    set_tohit(95);  // 84% chance of hitting

    set_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX, 
    SKILL_WEIGHT, 20, TS_WIS }) );

    set_skills(({ SS_ANATOMY }) );

    set_guild_stat_modifier(SS_OCCUP, 20, 100);

    set_ability_prep_time(5);
    set_ability_cooldown_time(5);
    set_dt(W_SLASH | W_IMPALE);
    set_ability_name("bloodletter");
    
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/ethereal.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/trucidate.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/execute.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/mesmerize.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/strangulate.c");
    add_ability_restriction(VAMPIRES_GUILD_DIR + "specials/vampfly.c");
}


public object
query_wielded_weapon(object actor)
{
    object * weapons;
    
    weapons = filter(actor->query_weapon(-1), 
                     &operator(&)(W_SLASH | W_IMPALE) @ &->query_dt());

    if (!sizeof(weapons))
    {
        // Not wielding a slashing weapon
        return 0;
    }
    
    return weapons[random(sizeof(weapons))];
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
    object weapon;

    weapon = query_wielded_weapon(actor);
    if (!weapon)
    {
        return 0;
    }
    
    return ({ weapon });
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
    
    if (!objectp(query_wielded_weapon(player)))
    {
        player->catch_tell("You are not wielding an appropriate weapon.\n");
        
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
    
    if (!::check_valid_action(player, targets, arg, execute))
    {
        return 0;
    }
    
    if (VAMPIRES_MAPPINGS->query_vampire_main_special(this_player()->query_name()) != 1)
    {
        player->catch_tell("What?\n");
        
        return 0;
    }
       
    if (!validate_requirements(player))
    {
        return 0;
    }
    
    if (present("_strangulate_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent strangulation of the "
        +"target, bloodletter is not yet ready to be used! Patience!\n");

        return 0;
    }
    
    if (present("_mesmerize_cooldwn_obj", player))
    {
        player->catch_tell("Due to your recent mesmerize of the "
        +"target, bloodletter is not yet ready to be used! Patience!\n");

        return 0;
    }
    
    if (STRANGULATE_ABILITY->query_ability_active(player))
    {
        player->catch_msg("You are currently preparing to strangulate!\n");
        return 0;
    }
    
    if (MESMERIZE_ABILITY->query_ability_active(player))
    {
        player->catch_msg("You are currently preparing to mesmerize!\n");
        return 0;
    }
    
    if (EXECUTE_ABILITY->query_ability_active(player))
    {
        player->catch_msg("You are currently preparing to execute!\n");
        return 0;
    }
    
    if (BLOODLETTER_ABILITY->query_ability_active(player))
    {
        player->catch_msg("You are currently preparing to bloodletter!\n");
        return 0;
    }
    
    if (TRUCIDATE_ABILITY->query_ability_active(player))
    {
        player->catch_msg("You are currently preparing to trudicate!\n");
        return 0;
    }
    
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
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    if (!objectp(this_player()))
        return;
    
    write("You are ready to perform bloodletter again.\n");    
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
    string weapon = items[0]->short();
    int weapon_type = items[0]->query_wt();
        
    object room = environment(this_player());   
    mixed * time_info = GENESIS_TIMEKEEPER->query_time(this_player());    
    string domain = lower_case(room->query_domain());   
    int hour = time_info[0];
        
    if (GENESIS_TIMEKEEPER->domain_hour_has_sunlight(domain, hour))
    {        
        this_player()->catch_tell("The presence of daystar weakens and distracts you.\n");
    }
    else
    {
        this_player()->catch_tell("Being a true master of the night, your movements feel enhanced.\n");
    }
        
    int thirstvalueocc = VAMPIRES_MAPPINGS->query_thirst_gauge(this_player()->query_name());
    int agevalueocc = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
    int thirstvalueaddocc = 0;
    
    int blood_dice;
    

    thirstvalueaddocc = thirstvalueocc + 1;

    int thirstvaluecapocc;
    
    switch(agevalueocc)
    {
        case 0..24:
        thirstvaluecapocc = 24;
        break;
        
        case 25..48:
        thirstvaluecapocc = 48;
        break;
        
        case 49..72:
        thirstvaluecapocc = 72;
        break;
        
        case 73..100:
        thirstvaluecapocc = 100;
        break;
        
        case 101..250:
        thirstvaluecapocc = 150;
        break;

        case 251..500:
        thirstvaluecapocc = 200;
        break;
        
        case 501..1000:
        thirstvaluecapocc = 250;
        break;
        
        case 1001..1440:
        thirstvaluecapocc = 300;
        break;
 
        case 1441..1450:
        thirstvaluecapocc = 350;
        break;
        
        case 1451..2000:
        thirstvaluecapocc = 400;
        break;
        
        case 2001..3000:
        thirstvaluecapocc = 450;
        break;
        
        case 3001..5000:
        thirstvaluecapocc = 500;
        break;
        
        case 5001..7000:
        thirstvaluecapocc = 550;
        break;
        
        case 7001..9000:
        thirstvaluecapocc = 600;
        break;
        
        case 9001..11000:
        thirstvaluecapocc = 700;
        break;
        
        case 11001..13000:
        thirstvaluecapocc = 800;
        break;
        
        case 13001..15000:
        thirstvaluecapocc = 900;
        break;
        
        case 15001..17529:
        thirstvaluecapocc = 1000;
        break;
        
        case 17530..999999:
        thirstvaluecapocc = 1200;
        break;
    }
    
    if (phurt >= 0)
    {
        switch(phurt)
        {
        case 0:
            if (target->query_prop(LIVE_I_UNDEAD))
            {
                 attack_message = ({
                  capitalize(target->query_the_name(tp))+ " nearly escapes the swing of your " 
                  +weapon+ " but it manages to scratch " +HIS(target)
                  + " " +hitloc+ ".\n",
                  
                 "You nearly escape the edge of " +target->query_the_name(tp)+ "'s " 
                 +weapon+ ", but it manages to scratch your " +hitloc
                 + ".\n",
        
                 QCTNAME(target)+ " nearly escapes the bite of " 
                 +QTNAME(tp)+ "'s " +weapon+ ", but it manages to scratch " 
                 +HIS(target)+ " " +hitloc+ ".\n"
                });
            }
            else
            {
                attack_message = ({
                  capitalize(target->query_the_name(tp))+ " nearly escapes the swing of your " 
                  +weapon+ " but it manages to scratch " +HIS(target)
                  + " " +hitloc+ ", leaving behind a red line.\n",
                  
                 "You nearly escape the edge of " +target->query_the_name(tp)+ "'s " 
                 +weapon+ ", but it manages to scratch your " +hitloc
                 + ", leaving behind a red line.\n",
        
                 QCTNAME(target)+ " nearly escapes the bite of " 
                 +QTNAME(tp)+ "'s " +weapon+ ", but it manages to scratch " 
                 +HIS(target)+ " " +hitloc+ ", leaving behind a red line.\n"
                });
            }
            
            
 
            // Only the living rewards blood.
            if (!target->query_prop(LIVE_I_UNDEAD))
            {
                blood_dice = random(20);
                
                if (blood_dice == 1)
                {
                    if (thirstvaluecapocc > thirstvalueocc)
                    {
                        VAMPIRES_MAPPINGS->set_thirst_gauge(tp->query_name(), thirstvalueaddocc);
                        
                        tp->catch_tell("You ravenously lick "
                        +"fresh blood that has pooled at the tip of your blade.\n");
                                       
                        tp->tell_watcher(QCTNAME(tp)+ " ravenously lick fresh blood "
                        +"that has pooled at the tip of "+HIS(tp)+ " " +weapon+ ".\n", target);
                        
                        BLOOD_LOG("blood_log",
                        "The Vampire " +this_player()->query_name() 
                        +" gained 1 bloodpoint. (lick).\n");
                    }
                }
            }
                               
            break;
        case 1..10:
            if (target->query_prop(LIVE_I_UNDEAD))
            {
                attack_message = ({
                  "With a flurry of slashes from your " +weapon
                  + " you manage to nick " + target->query_the_name(tp)
                  + " 's " +hitloc+ " in several places.\n",  
                  
                  "With a flury of slashes, " +tp->query_the_name(target)
                  + " nicks your " +hitloc+ " with in several places with " 
                  +HIS(tp)+ " " +weapon+ ".\n",
        
                  "With a flurry of slashes from " +HIS(tp)+ " " +weapon
                  + ", " +QTNAME(tp)+ " nicks " +QTNAME(target)+ " 's " 
                  +hitloc+ " in several places.\n"
                });
            }
            else
            {
                attack_message = ({
                  "With a flurry of slashes from your " +weapon
                  + " you manage to nick " + target->query_the_name(tp)
                  + "'s " +hitloc+ " in several places, causing a trickle of blood.\n",  
                  
                  "With a flurry of slashes, " +tp->query_the_name(target)
                  + " nicks your " +hitloc+ " with in several places with " 
                  +HIS(tp)+ " " +weapon+ ", causing a trickle of blood.\n",
        
                  "With a flurry of slashes from " +HIS(tp)+ " " +weapon
                  + ", " +QTNAME(tp)+ " nicks " +QTNAME(target)+ "'s " 
                  +hitloc+ " in several places, causing a trickle of blood.\n"
                });
            }
                       
            // Only the living rewards blood.
            if (!target->query_prop(LIVE_I_UNDEAD))
            {
                blood_dice = random(SPECIAL_BLOODGAIN_FACTOR);
                
                if (blood_dice == 1)
                {
                    if (thirstvaluecapocc > thirstvalueocc)
                    {
                        VAMPIRES_MAPPINGS->set_thirst_gauge(tp->query_name(), thirstvalueaddocc);
                        
                        tp->catch_tell("You ravenously lick "
                        +"fresh blood that has pooled at the tip of your blade.\n");
                                       
                        tp->tell_watcher(QCTNAME(tp)+ " ravenously lick fresh blood "
                        +"that has pooled at the tip of "+HIS(tp)+ " " +weapon+ ".\n", target);
                        
                        BLOOD_LOG("blood_log",
                        "The Vampire " +this_player()->query_name() 
                        +" gained 1 bloodpoint. (lick).\n");
                    }
                }
            }
            
            break;
        
        case 11..30:
            attack_message = ({
              "An impressive stroke of your " +weapon+ " leaves a gruesome "
              +"wound across " + target->query_the_name(tp)+ "'s " +hitloc+ ".\n",
    
              "A precise stroke from " +tp->query_the_name(target)+ "'s " 
              +weapon+ " leaves a gruesome wound across your " +hitloc+ ".\n",
    
              "The " +hitloc+ " of " +QTNAME(target)+ " is left with a gruesome "
              +"wound from a precise stroke of " +QTNAME(tp)+ "'s " +weapon+ ".\n"
            });
            
            // Only the living rewards blood.
            if (!target->query_prop(LIVE_I_UNDEAD))
            {
                blood_dice = random(SPECIAL_BLOODGAIN_FACTOR);
                
                if (blood_dice == 1)
                {
                    if (thirstvaluecapocc > thirstvalueocc)
                    {
                        VAMPIRES_MAPPINGS->set_thirst_gauge(tp->query_name(), thirstvalueaddocc);
                        
                        tp->catch_tell("You ravenously lick "
                        +"fresh blood that has pooled at the tip of your blade.\n");
                                       
                        tp->tell_watcher(QCTNAME(tp)+ " ravenously lick fresh blood "
                        +"that has pooled at the tip of "+HIS(tp)+ " " +weapon+ ".\n", target);
                        
                        BLOOD_LOG("blood_log",
                        "The Vampire " +this_player()->query_name() 
                        +" gained 1 bloodpoint. (lick).\n");
                    }
                }
            }
            
            break;
        case 31..60:
            if (target->query_prop(LIVE_I_UNDEAD))
            {
                attack_message = ({
                  "Whirling and spinning your " +weapon+ ", masterfully, you "
                  +"deeply rend " + target->query_the_name(tp)
                  + " in multiple locations.\n",
                  
                  "Pain wracks your body in multiple locations, deeply "
                  +"rent by a whirling attack from " 
                  +tp->query_the_name(target)+ "'s " +weapon+ ".\n",
        
                  "Whirling and spinning in a vicious dance, " 
                  +QTNAME(tp)+ " deeply rends " +QTNAME(target)
                  + " in multiple locations with " +HIS(tp)+ " " +weapon+ ".\n"
                });
            }
            else
            {
                attack_message = ({
                  "Whirling and spinning your " +weapon+ ", masterfully, you "
                  +"deeply rend " + target->query_the_name(tp)
                  + " in multiple locations, leaving the areas slick with blood.\n",
                  
                  "Pain wracks your body in multiple locations, now slick "
                  +"with blood, deeply rent by a whirling attack from " 
                  +tp->query_the_name(target)+ "'s " +weapon+ ".\n",
        
                  "Whirling and spinning in a vicious dance, " 
                  +QTNAME(tp)+ " deeply rends " +QTNAME(target)
                  + " in multiple locations with " +HIS(tp)+ " " +weapon+ ".\n"
                });
            }

            // Only the living rewards blood.
            if (!target->query_prop(LIVE_I_UNDEAD))
            {
                blood_dice = random(SPECIAL_BLOODGAIN_FACTOR);
                
                if (blood_dice == 1)
                {
                    if (thirstvaluecapocc > thirstvalueocc)
                    {
                        VAMPIRES_MAPPINGS->set_thirst_gauge(tp->query_name(), thirstvalueaddocc);
                        
                        tp->catch_tell("You ravenously lick "
                        +"fresh blood that has pooled at the tip of your blade.\n");
                                       
                        tp->tell_watcher(QCTNAME(tp)+ " ravenously lick fresh blood "
                        +"that has pooled at the tip of "+HIS(tp)+ " " +weapon+ ".\n", target);
                        
                        BLOOD_LOG("blood_log",
                        "The Vampire " +this_player()->query_name() 
                        +" gained 1 bloodpoint. (lick).\n");
                    }
                }
            }
            
            break;
        case 61..80:
            attack_message = ({
              "You penetrate " + target->query_the_name(tp)+ "'s defenses and "
              +"severely stab " +HIS(target)+ " " +hitloc
              + " in a rapid succession of thrusts.\n",
    
              "Effortlessly, " +tp->query_the_name(target)+ " penetrates your "
              +"defenses and severely stabs your " +hitloc
              +" with a rapid succession of thrusts.\n",
    
              "With seemingly little effort, " +QTNAME(tp)+ " penetrates " 
              +QTNAME(target)+ "'s defenses, severely stabbing " 
              +HIS(target)+ " " +hitloc+ " with a rapid succession of thrusts.\n" 
            });
            
            // Only the living rewards blood.
            if (!target->query_prop(LIVE_I_UNDEAD))
            {
                blood_dice = random(SPECIAL_BLOODGAIN_FACTOR);
                
                if (blood_dice == 1)
                {
                    if (thirstvaluecapocc > thirstvalueocc)
                    {
                        VAMPIRES_MAPPINGS->set_thirst_gauge(tp->query_name(), thirstvalueaddocc);
                        
                        tp->catch_tell("You ravenously lick "
                        +"fresh blood that has pooled at the tip of your blade.\n");
                                       
                        tp->tell_watcher(QCTNAME(tp)+ " ravenously lick fresh blood "
                        +"that has pooled at the tip of "+HIS(tp)+ " " +weapon+ ".\n", target);
                        
                        BLOOD_LOG("blood_log",
                        "The Vampire " +this_player()->query_name() 
                        +" gained 1 bloodpoint. (lick).\n");
                    }
                }
            }
            
            break;
        case 81..99:
             if (target->query_prop(LIVE_I_UNDEAD))
             {
                 attack_message = ({
                  "With the brutality of a wild animal, you repeatedly hack at " 
                  + target->query_the_name(tp)+ "'s " +hitloc+ " with your " 
                  +weapon+ ", causing massive damage.\n",
        
                  "With an animalistic brutality, " + target->query_the_name(tp)
                  + " repeatedly hacks your " +hitloc
                  + ", causing massive damage.\n",
        
                  "With an animalistic brutality, " +QTNAME(tp)
                  + " repeatedly hacks " +QTNAME(target)+ "'s " +hitloc+ " with " 
                  +HIS(tp)+ " " +weapon+ ", causing massive damage.\n"
                });
             }
             else
             {
                 attack_message = ({
                  "With the brutality of a wild animal, you repeatedly hack at " 
                  + target->query_the_name(tp)+ "'s " +hitloc+ " with your " 
                  +weapon+ ", causing massive damage and copious bleeding.\n",
        
                  "With an animalistic brutality, " + target->query_the_name(tp)
                  + " repeatedly hacks your " +hitloc
                  + ", causing massive damage and copious bleeding.\n",
        
                  "With an animalistic brutality, " +QTNAME(tp)
                  + " repeatedly hacks " +QTNAME(target)+ "'s " +hitloc+ " with " 
                  +HIS(tp)+ " " +weapon+ ", causing massive damage and copious bleeding.\n"
                });
             }
            // Only the living rewards blood.
            if (!target->query_prop(LIVE_I_UNDEAD))
            {
                blood_dice = random(SPECIAL_BLOODGAIN_FACTOR);
                
                if (blood_dice == 1)
                {
                    if (thirstvaluecapocc > thirstvalueocc)
                    {
                        VAMPIRES_MAPPINGS->set_thirst_gauge(tp->query_name(), thirstvalueaddocc);
                        
                        tp->catch_tell("You ravenously lick "
                        +"fresh blood that has pooled at the tip of your blade.\n");
                                       
                        tp->tell_watcher(QCTNAME(tp)+ " ravenously lick fresh blood "
                        +"that has pooled at the tip of "+HIS(tp)+ " " +weapon+ ".\n", target);
                        
                        BLOOD_LOG("blood_log",
                        "The Vampire " +this_player()->query_name() 
                        +" gained 1 bloodpoint. (lick).\n");
                    }
                }
            }
                       
            break;
        default:
               
              if (target->query_prop(LIVE_I_UNDEAD))
              {  
                  attack_message = ({
                  "With unnatural speed, you move and grip " 
                  +target->query_the_name(tp)+ " by the throat and sever "
                  +target->query_possessive()+" spine!\n",
                              
                  tp->query_The_name(target)+ " suddenly appears before you and grabs "
                  +"you by the throat! Before you have a time to react, you feel your spine "
                  +"is brutally severed!\n",
                  
                  QCTNAME(tp)+ " suddenly blinks before " +QTNAME(target)+ " and "
                  +"grabs "+target->query_objective()+" by the throat! Within "
                  +"a split second,  "+QTNAME(tp)+" sever the spine of " 
                  +QTNAME(target)+ "!\n"       
                  });                  
              }
              else
              {
                  attack_message = ({
                  "With unnatural speed, you move and grip " 
                  +target->query_the_name(tp)+ " by the throat sinking your "
                  +"fangs into "+target->query_possessive()+" neck! Greedily, "
                  +"you drain every last drop of warm blood from "
                  +target->query_the_name(tp)+ " before the heart stops!\nYou toss the "
                  +"lifeless corpse aside!\n\n",
                              
                  tp->query_The_name(target)+ " suddenly appears before you and grabs "
                  +"you by the throat! You feel a pair of fangs sink deep into your neck, and "
                  +"have the strange sensation of the last of your blood being drained from your "
                  +"body! The world fades to black as your heart beats for "
                  +"the very last time.\n\n",
                  
                  QCTNAME(tp)+ " suddenly blinks before " +QTNAME(target)+ " and "
                  +"grabs "+target->query_objective()+" by the throat before sinking a pair of "
                  +"white fangs into the neck! Blood spills from the mouth of "
                  +QTNAME(tp)+" when the lifeless corpse of " +QTNAME(target)+ " is released "
                  +"from the rigid grasp and tossed at the ground!\n"
                  });
              }
        
            
             // Only the living rewards blood.
            if (!target->query_prop(LIVE_I_UNDEAD))
            {  
                if (thirstvaluecapocc > thirstvalueocc)
                {         
                    thirstvalueaddocc = thirstvalueaddocc + 1;
                    
                    VAMPIRES_MAPPINGS->set_thirst_gauge(tp->query_name(), thirstvalueaddocc);
                                
                    BLOOD_LOG("blood_log",
                    "The Vampire " +this_player()->query_name() 
                    +" gained 2 bloodpoint. (drain)\n");
                }
            }                      
        }
        
        if (!target->query_prop(LIVE_I_UNDEAD))
        {  
        
            if (!target->query_bleeding())
            {
                setuid();
                seteuid(getuid());
                
                object shadow=clone_object(BLOOD_SHADOW);
                catch (shadow->shadow_me(target));
            }                    

            target->bleed_location(hid);
        }
            
        tp->catch_tell(attack_message[0]);
        target->catch_tell(attack_message[1]);
        tp->tell_watcher(attack_message[2], target);
        
        // A successful attack generates panic
        tp->add_panic(-3 - phurt / 5);      
    }
    else
    {
        tp->catch_tell("You slash errantly at " 
        +target->query_the_name(tp)
        + ", with your " +weapon+ ".\n");
          
        target->catch_tell("You can feel the breeze of a wide "
        +"swing from " +tp->query_the_name(target)+ " 's " +weapon+ ".\n");
            
        tp->tell_watcher_miss(QCTNAME(target)+ " steps back subtly as " 
        +QTNAME(tp)+ " swings " +HIS(tp)+ " " +weapon+ " wide.\n", target);
        
        // A miss emboldens enemies
        tp->add_panic(1);
    }
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(tp);
    }
}


/*
 * Function name:   query_combat_aid_modifier
 * Description:     Calculates the percentage of the maximum combat aid that
 *                  applies to the current situation
 * Arguments:       None
 * Returns:         (int) number between 1 and 100
 */
public int
query_combat_aid_modifier()
{
    int     day = 1, modifier = 100;
    object  room = environment(this_player());
    mixed   hour = GENESIS_TIMEKEEPER->query_time();
    
    if (pointerp(hour))
    {
        string domain = lower_case(room->query_domain());
        day = GENESIS_TIMEKEEPER->domain_hour_has_sunlight(domain, hour[0]);
    }
    
    // Vampires according to documentation has 60 caid. (Awaiting AoB Approval)
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
        modifier -= 40;
    
    if (day)
    {
        // Remove 40 caid for daylight (In accordance with documentation)
        modifier -= 40;
    }
    
    return modifier;
} /* query_combat_aid_modifier */



