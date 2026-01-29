/*
 * 2021-03-28 Modified by Carnak
 *  - Fixing some bugs with concentration, and targetting
 *    locations.
 *  - Issue rebalanced with the new white hit system.
 */

#pragma strict_types

inherit "/d/Genesis/specials/std/damage";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#include <files.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <tasks.h>
#include <formulas.h>

#include "/std/combat/combat.h"

#include "../guild.h"
#include "missile_functions.c"


// Prototypes
public mixed        *target_vulnerable_loc(object actor, string arg);
                                   
// Global Variables
static mapping      heightened_senses = ([]),
                    modified_attack = ([]),
                    concentration = ([]),
                    appraising = ([]),
                    loaded = ([]);

/*
 * Function name:   remove_concentration
 * Description:     Decreases the concentration level of the actor.
 * Arguments:       (object) actor - The actor of the ability
 * Returns:         Nothing
 */
public void
remove_concentration(object actor)
{
    /*
    int concentrate;
    
    if (concentration[actor] > 0)
    {
        concentration[actor]--;
        
        concentrate = actor->query_prop(LIVE_I_CONCENTRATE);
        if (intp(concentrate) && concentrate > 0)
            actor->add_prop(LIVE_I_CONCENTRATE, --concentrate);
    }
    
    if (objectp(loaded[actor]))
    {
        // Added to fix the unloading while tired during specials.
        loaded[actor]->unload();
        // This was added to remove the guru arrows..
        loaded[actor]->verify_location();
    }*/
    if (!mappingp(concentration[actor]))
        return;
    
    int value = actor->query_prop(LIVE_I_ATTACK_DELAY);
    value = min(concentration[actor]["delay"], value);
    
    if (value > 0)
        actor->dec_prop(LIVE_I_ATTACK_DELAY, value);
    
    concentration[actor]["delay"] = 0;
    remove_alarm(concentration[actor]["alarm"]);
} /* remove_concentration */

/*
 * Function name:   add_concentration
 * Description:     Increments the concentration of the actor.
 * Arguments:       (object) actor  - The actor of the ability
 * Returns:         Nothing
 */
public void
add_concentration(object actor)
{
    /*
    int concentrate;
    
    if (concentration[actor] < 1)
    {
        concentration[actor]++;
        
        concentrate = actor->query_prop(LIVE_I_CONCENTRATE);
        if (intp(concentrate))
            actor->add_prop(LIVE_I_CONCENTRATE, ++concentrate);
    }*/
} /* add_concentration */

/*
 * Function name:   config_ability
 * Description:     Main function that configures what the special should look
 *                  like. Set basic things like combat aid and the skills to be
 *                  used for calculating damage and of course, the name.
 * Arguments:       None
 * Returns:         Nothing
 */
public void 
config_ability()
{
    ::config_ability();
    set_combat_aid(147);
    set_tohit(110); // 90% hit chance
    set_dt(W_IMPALE);
    set_stats( ({ SKILL_WEIGHT, 60, TS_DEX, SKILL_WEIGHT, 25, TS_WIS, 
                  SKILL_WEIGHT, 15, TS_STR }) );
    set_skills(({ SS_WEP_MISSILE }));
    set_ability_prep_time(10);
    set_ability_cooldown_time(10);
    set_ability_name("snipe");
    set_ability_target(target_vulnerable_loc);
    
    /*
     * The ability does of course not attack during prep or reveal, as it would
     * interrupt the ability when ambushing.
     */
    set_ability_attack_during_prep(0);
    set_ability_no_reveal(1);
    
    set_guild_stat_modifier(SS_OCCUP, 50, 150);
    
    setuid();
    seteuid(getuid());
} /* config_ability */

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
    string name, logfile;
    
    if (interactive(this_player()))
    {
        name = capitalize(this_player()->query_real_name());
    }
    else
    {
        name = MASTER_OB(this_player());
    }
    
    logfile = FILE_PATH(MASTER_OB(this_object()));
    logfile += short() + "_damage";
    logfile = implode(explode(logfile, " "), "");
    
    send_debug_message(short(), name + " hits with Pen of "
        + pen + ", " + "Damage of " + damage, logfile);
} /* report_resolve_ability */

/*
 * Function name:   notify_heightened_senses
 * Description:     This function displays a message to the actor if the ability
 *                  is affected by heightened senses.
 * Arguments:       1. (object) actor  - The actor of the ability
 *                  2. (mixed) targets - The targets of the ability
 * Returns:         Nothing
 */
public void
notify_heightened_senses(object actor, mixed *targets)
{
    send_debug_message("archer_aimshot", "notify_heightened_senses triggered");
    object  bow = query_wielded_bow(actor);
    int     focus;
    
    if (!actor->query_attack())
        return;
    
    modified_attack[actor] = actor->query_attack();
    
    if (appraising[actor])
        return;
    
    string name = actor->query_real_name();
    int sniping = OPTIONS_MANAGER->query_option("SnipeSetting", name);
    if (!VISION_IMPAIRED(actor) && sniping)
        actor->catch_msg("With your " + bow->short() + " poised, you scan "
        + (objectp(targets[0]) ? targets[0]->query_the_name(actor) : "your foe")
        + " for vulnerabilities.\n");
} /* notify_heightened_senses */

/*
 * Function name:   update_live_attack_delay
 * Description:     
 * Arguments:       1. (object) actor  - The actor of the ability
 *                  2. (mixed) targets - The targets of the ability
 * Returns:         Nothing
 */
public void
update_live_attack_delay(object actor, mixed *targets)
{
    concentration[actor]["delay"]--;
    if (!actor->query_attack())
    {
        // The prop can be cleared if you dont have an enemy, set it up again
        // if the ability is loading so we (hopefully) dont load another arrow.
        int value = actor->query_prop(LIVE_I_ATTACK_DELAY);
        value = max(concentration[actor]["delay"], --value);
        actor->add_prop(LIVE_I_ATTACK_DELAY, value);
    }
    
    if (concentration[actor]["delay"] < 1)
        remove_alarm(concentration[actor]["alarm"]);
} /* update_live_attack_delay */

/*
 * Function name:   notify_prep_time
 * Description:     This is a hook that abilities can use to know how long the
 *                  prep time is before execution. A common usage of this may
 *                  be to provide interim messages for long delays.
 * Arguments:       1. (float) prep_time - the time before execution
 *                  2. (object) actor - the actor of the ability
 *                  3. (mixed *) targets - targets of the ability
 * Returns:         Nothing
 */
static void
notify_prep_time(float prep_time, object actor, mixed * targets)
{
    if (!mappingp(concentration[actor]))
        concentration[actor] = ([ "delay" : 0, "alarm" : 0 ]);
    concentration[actor]["delay"] = ftoi(prep_time + 5.0);
    actor->inc_prop(LIVE_I_ATTACK_DELAY, concentration[actor]["delay"]);
    concentration[actor]["alarm"] = set_alarm(1.0, 1.0, 
        &update_live_attack_delay(actor, targets));

    send_debug_message("archer_aimshot", "notify_prep_time triggered");
    heightened_senses[actor] = set_alarm(prep_time - 0.5, 0.0,
                               &notify_heightened_senses(actor, targets));
} /* notify_prep_time */

/*
 * Function name:   special_did_hit
 * Description:     Mask this function to process when the special scores.
 *                  Descriptions seen by everyone are set here.
 * Arguments:       1. (int) aid        - attack id
 *                  2. (string) hdesc   - hit description
 *                  3. (int) hid        - hitloc id
 *                  4. (int) phurt      - extent of damage
 *                  5. (object) enemy   - person being hit by special
 *                  6. (int) dt         - damage type
 *                  7. (int) phit       - percent hit success
 *                  8. (int) dam        - damage amount
 *                  9. (mixed *) items  - items used
 *                  10. (int) result    - result of cb_tohit
 * Returns:         Nothing
 */
public varargs void 
special_did_hit(int aid, string hdesc, int hid, int phurt, object enemy,
                int dt, int phit, int dam, mixed *items, int result)
{
    string *archer_msg, *enemy_msg, *others_msg,
           *hitdesc, shoot, dmg_msg;
    int     concentrate, dmg_num, rng;
    object  archer, arrow, bow;
    
    send_debug_message("archer_aimshot", "special_did_hit triggered");
    
    bow = items[0];
    archer = this_player();
    
    /* Manages arrow stacks */
    if (phurt < 6)
        arrow = reduce_and_miss(enemy, bow, items[1]);
    else
        arrow = reduce_and_hit(enemy, bow, items[1]);

    /* Makes the arrow retrievable */
    arrow->add_prop(OBJ_O_BELONGS_TO_ARCHER, archer);
    
    shoot = one_of_list(({ "shoot", "unleash", "loose", "release", "fire" }));
    
    hitdesc = ({
        ({ "leaving a minor scratch", "causing an insignificant wound", }),
        ({ "leaving a minor wound", "causing a shallow wound", }),
        ({ "puncturing it", "causing a bloody wound", }),
        ({ "painfully piercing it", "piercing it painfully", }),
        ({ "causing significant damage", "impaling it painfully", }),
        ({ "causing a ghastly wound", "gruesomely impaling it", }),
        ({ "causing a lethal wound", "fatally impaling it", }),
    });
    
    switch(phurt)
    {
        case -2..0:
        archer_msg = ({
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ", but it misses the target "
            + "badly",
            
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ". It flies past your target, "
            + "missing " + enemy->query_objective(),
            
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ", but it hisses past, missing "
            + enemy->query_objective(),
        });

        enemy_msg = ({
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, but it misses "
            + "you badly",
            
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, but it just "
            + "flies past, missing you",
            
            "You hear the hiss of an arrow flying through the air as "
            + archer->query_the_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you"
        });
        
        others_msg = ({
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short())
            + " at " + QTNAME(enemy) + ", but it misses "
            + enemy->query_objective() + " badly",
                             
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short())
            + " at " + QTNAME(enemy) + ", but it just flies past "
            + enemy->query_objective() + ", barely missing the target",
            
            "You hear the hiss of an arrow flying through the air as "
            + QTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short())
            + " at " + QTNAME(enemy)
        });
        
            break;
        case 1..5:
        dmg_msg = one_of_list(hitdesc[0]);
    
        archer_msg = ({
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy ->query_the_name(archer) + ", " + dmg_msg,
            
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ", it merely glances off "
            + dmg_msg,
            
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ", but it hisses past, "
            + dmg_msg,
        });

        enemy_msg = ({
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, " + dmg_msg,
            
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, " + dmg_msg,
            
            "You hear the hiss of an arrow flying through the air as "
            + archer->query_the_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, " + dmg_msg
        });
        
        others_msg = ({
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short())
            + " at " + QTNAME(enemy) + ", " + dmg_msg,
                             
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short())
            + " at " + QTNAME(enemy) + ", " + dmg_msg,
            
            "You hear the hiss of an arrow flying through the air as "
            + QTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short())
            + " at " + QTNAME(enemy) + ", " + dmg_msg
        });
        
            break;
        case 6..10:
        dmg_msg = one_of_list(hitdesc[1]);
        
        archer_msg = ({
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy ->query_the_name(archer) + ", hitting "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "Your aim stay true as you " + shoot + " the "
            + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ", it strikes "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "You accurately " + shoot + " the " + arrow->singular_short()
            + " at " + enemy->query_the_name(archer) + "'s " + hdesc + ", "
            + dmg_msg,
        });

        enemy_msg = ({
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, hitting your "
            + hdesc + ", " + dmg_msg,
            
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, " + dmg_msg
            + " as it strikes your " + hdesc,
            
            "With great accuracy, " + archer->query_the_name(enemy) + " "
            + LANG_PWORD(shoot) + " " + LANG_ADDART(arrow->singular_short())
            + " at your " + hdesc + ", " + dmg_msg
        });
        
        others_msg = ({
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", hitting " + enemy->query_possessive() + hdesc + ", " + dmg_msg,
            
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", " + dmg_msg + " as it strikes " + enemy->query_possessive()
            + " " + hdesc,
            
            "With great accuracy " + QTNAME(archer) + " " + LANG_PWORD(shoot)
            + " " + LANG_ADDART(arrow->singular_short()) + " at "
            + QTNAME(enemy) + "'s " + hdesc + ", " + dmg_msg
        });
            break;
        case 11..20:
        dmg_msg = one_of_list(hitdesc[2]);
        
        archer_msg = ({
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy ->query_the_name(archer) + ", hitting "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "Your aim stay true as you " + shoot + " the "
            + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ", it strikes "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "You accurately " + shoot + " the " + arrow->singular_short()
            + " at " + enemy->query_the_name(archer) + "'s " + hdesc + ", "
            + dmg_msg,
        });

        enemy_msg = ({
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, hitting your "
            + hdesc + ", " + dmg_msg,
            
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, " + dmg_msg
            + " as it strikes your " + hdesc,
            
            "With great accuracy, " + archer->query_the_name(enemy) + " "
            + LANG_PWORD(shoot) + " " + LANG_ADDART(arrow->singular_short())
            + " at your " + hdesc + ", " + dmg_msg
        });
        
        others_msg = ({
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", hitting " + enemy->query_possessive() + hdesc + ", " + dmg_msg,
            
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", " + dmg_msg + " as it strikes " + enemy->query_possessive()
            + " " + hdesc,
            
            "With great accuracy " + QTNAME(archer) + " " + LANG_PWORD(shoot)
            + " " + LANG_ADDART(arrow->singular_short()) + " at "
            + QTNAME(enemy) + "'s " + hdesc + ", " + dmg_msg
        });
            break;
        case 21..30:
        dmg_msg = one_of_list(hitdesc[3]);
        
        archer_msg = ({
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy ->query_the_name(archer) + ", hitting "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "Your aim stay true as you " + shoot + " the "
            + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ", it strikes "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "You accurately " + shoot + " the " + arrow->singular_short()
            + " at " + enemy->query_the_name(archer) + "'s " + hdesc + ", "
            + dmg_msg,
        });

        enemy_msg = ({
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, hitting your "
            + hdesc + ", " + dmg_msg,
            
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, " + dmg_msg
            + " as it strikes your " + hdesc,
            
            "With great accuracy, " + archer->query_the_name(enemy) + " "
            + LANG_PWORD(shoot) + " " + LANG_ADDART(arrow->singular_short())
            + " at your " + hdesc + ", " + dmg_msg
        });
        
        others_msg = ({
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", hitting " + enemy->query_possessive() + hdesc + ", " + dmg_msg,
            
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", " + dmg_msg + " as it strikes " + enemy->query_possessive()
            + " " + hdesc,
            
            "With great accuracy " + QTNAME(archer) + " " + LANG_PWORD(shoot)
            + " " + LANG_ADDART(arrow->singular_short()) + " at "
            + QTNAME(enemy) + "'s " + hdesc + ", " + dmg_msg
        });
            break;
        case 31..50:
        dmg_msg = one_of_list(hitdesc[4]);
        
        archer_msg = ({
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy ->query_the_name(archer) + ", hitting "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "Your aim stay true as you " + shoot + " the "
            + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ", it strikes "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "You accurately " + shoot + " the " + arrow->singular_short()
            + " at " + enemy->query_the_name(archer) + "'s " + hdesc + ", "
            + dmg_msg,
        });

        enemy_msg = ({
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, hitting your "
            + hdesc + ", " + dmg_msg,
            
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, " + dmg_msg
            + " as it strikes your " + hdesc,
            
            "With great accuracy, " + archer->query_the_name(enemy) + " "
            + LANG_PWORD(shoot) + " " + LANG_ADDART(arrow->singular_short())
            + " at your " + hdesc + ", " + dmg_msg
        });
        
        others_msg = ({
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", hitting " + enemy->query_possessive() + hdesc + ", " + dmg_msg,
            
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", " + dmg_msg + " as it strikes " + enemy->query_possessive()
            + " " + hdesc,
            
            "With great accuracy " + QTNAME(archer) + " " + LANG_PWORD(shoot)
            + " " + LANG_ADDART(arrow->singular_short()) + " at "
            + QTNAME(enemy) + "'s " + hdesc + ", " + dmg_msg
        });
            break;
        case 51..70:
        dmg_msg = one_of_list(hitdesc[5]);
        
        archer_msg = ({
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy ->query_the_name(archer) + ", hitting "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "Your aim stay true as you " + shoot + " the "
            + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ", it strikes "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "You accurately " + shoot + " the " + arrow->singular_short()
            + " at " + enemy->query_the_name(archer) + "'s " + hdesc + ", "
            + dmg_msg,
        });

        enemy_msg = ({
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, hitting your "
            + hdesc + ", " + dmg_msg,
            
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, " + dmg_msg
            + " as it strikes your " + hdesc,
            
            "With great accuracy, " + archer->query_the_name(enemy) + " "
            + LANG_PWORD(shoot) + " " + LANG_ADDART(arrow->singular_short())
            + " at your " + hdesc + ", " + dmg_msg
        });
        
        others_msg = ({
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", hitting " + enemy->query_possessive() + hdesc + ", " + dmg_msg,
            
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", " + dmg_msg + " as it strikes " + enemy->query_possessive()
            + " " + hdesc,
            
            "With great accuracy " + QTNAME(archer) + " " + LANG_PWORD(shoot)
            + " " + LANG_ADDART(arrow->singular_short()) + " at "
            + QTNAME(enemy) + "'s " + hdesc + ", " + dmg_msg
        });
            break;
        case 71..99:
        dmg_msg = one_of_list(hitdesc[6]);
        
        archer_msg = ({
            "You " + shoot + " the " + arrow->singular_short() + " at "
            + enemy ->query_the_name(archer) + ", hitting "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "Your aim stay true as you " + shoot + " the "
            + arrow->singular_short() + " at "
            + enemy->query_the_name(archer) + ", it strikes "
            + enemy->query_possessive() + " " + hdesc + ", " + dmg_msg,
            
            "You accurately " + shoot + " the " + arrow->singular_short()
            + " at " + enemy->query_the_name(archer) + "'s " + hdesc + ", "
            + dmg_msg,
        });

        enemy_msg = ({
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, hitting your "
            + hdesc + ", " + dmg_msg,
            
            archer->query_The_name(enemy) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at you, " + dmg_msg
            + " as it strikes your " + hdesc,
            
            "With great accuracy, " + archer->query_the_name(enemy) + " "
            + LANG_PWORD(shoot) + " " + LANG_ADDART(arrow->singular_short())
            + " at your " + hdesc + ", " + dmg_msg
        });
        
        others_msg = ({
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", hitting " + enemy->query_possessive() + hdesc + ", " + dmg_msg,
            
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " "
            + LANG_ADDART(arrow->singular_short()) + " at " + QTNAME(enemy)
            + ", " + dmg_msg + " as it strikes " + enemy->query_possessive()
            + " " + hdesc,
            
            "With great accuracy " + QTNAME(archer) + " " + LANG_PWORD(shoot)
            + " " + LANG_ADDART(arrow->singular_short()) + " at "
            + QTNAME(enemy) + "'s " + hdesc + ", " + dmg_msg
        });
            break;
        default:
        archer_msg = ({
            "You " + shoot + " at " + QTNAME(enemy) + " with devastating "
            + "precision. " + capitalize(enemy->query_pronoun()) + " falls to "
            + "the ground, with " + LANG_ADDART(arrow->singular_short())
            + " sticking from a mortal wound in " + enemy->query_possessive()
            + " " + hdesc,
                
            "You " + shoot + " at " + QTNAME(enemy) + " with devastating "
            + "precision. " + capitalize(enemy->query_pronoun()) + " falls to "
            + "the ground, with " + LANG_ADDART(arrow->singular_short())
            + " sticking from a mortal wound in " + enemy->query_possessive()
            + " " + hdesc
        });

        enemy_msg = ({
            archer->query_the_name(enemy) + " " + LANG_PWORD(shoot) + " at you "
            + "with devastating precision. You fall to the ground, with "
            + LANG_ADDART(arrow->singular_short()) + " sticking from a mortal "
            + "wound in your " + hdesc,
            
            archer->query_the_name(enemy) + " aims "
            + archer->query_possessive() + " " + bow->short() + " at you "
            + "and " + LANG_PWORD(shoot) + " you with devastating precision. "
            + "You fall to the ground, with "
            + LANG_ADDART(arrow->singular_short()) + " sticking from a mortal "
            + "wound in your " + hdesc
        });
                
        others_msg = ({
            QCTNAME(archer) + " " + LANG_PWORD(shoot) + " at " + QTNAME(enemy)
            + " with devastating precision. "
            + capitalize(enemy->query_pronoun()) + " falls to the ground, with "
            + LANG_ADDART(arrow->singular_short()) + " sticking from a mortal "
            + "wound in " + enemy->query_possessive() + " " + hdesc,
            
            QCTNAME(archer) + " aims " + archer->query_possessive() + " "
            + bow->short() + " at " + QTNAME(enemy) + " with devastating "
            + "precision. " + capitalize(enemy->query_pronoun())
            + " falls to the ground, with "
            + LANG_ADDART(arrow->singular_short()) + " sticking from a mortal "
            + "wound in " + enemy->query_possessive() + " " + hdesc
        });
            break;
    }
    
    rng = random(sizeof(archer_msg));
    
    archer->catch_msg(archer_msg[rng] + ".\n");
    enemy->catch_msg(enemy_msg[rng] + ".\n");
    archer->tell_watcher(others_msg[rng] + ".\n", enemy);
    
    remove_concentration(archer);
        
    /* Calls the hit in the arrow */
    if (dam > 0)
    {
        if (objectp(arrow))
        {
            int max_dmg, prc_dmg, wep_dmg, wep_pen, wep_lev;
        
            /*
             * This damage is calculated from the percentual success of the 
             * special and the F_PENMOD on weapons and bow skill. Keep in mind,
             * this does not add damage unless the arrow itself has a special
             * that is applied in such a way. 
             */
        
            max_dmg = calculate_damage(archer, enemy, items, 0, result);
            prc_dmg = dam * 100 / max_dmg;
            wep_pen = calc_base_pen(items);
            wep_lev = archer->query_skill(SS_WEP_MISSILE);
            wep_dmg = F_ATTACK_PEN_MOD(F_PENMOD(wep_pen, wep_lev)) * prc_dmg / 100;
        
            arrow->projectile_hit_target(archer, aid, hdesc, phurt, enemy, dt,
                                         phit, wep_dmg, hid);
        }
        
        if (enemy->query_hp() <= 0)
            enemy->do_die(archer);
    }
} /* special_did_hit */

/*
 * Function name:   check_required_items
 * Description:     Does some validation to make sure that the archer has arrows
 * Arguments:       1. (object) actor - The actor of the ability
 *                  2. (mixed *) targets - The targets of the ability
 *                  3. (string) arg - The arguments used
 *                  4. (int) - pretest
 * Returns:         (mixed *) items that are required.
 */
static mixed * 
check_required_items(object actor, mixed *targets, string arg, int pretest)
{
    mixed   arrow,
            bow;
    
    loaded[actor] = 0;
    send_debug_message("archer_aimshot", "check_required_items triggered");
    if (!objectp(bow = query_wielded_bow(actor)))
    {
        actor->catch_msg("You are not wielding a bow.\n");
        remove_concentration(actor);
        return 0;
    }
    
    if (objectp(arrow = bow->query_projectile()))
    {
        // Added to fix the unloading while tired during specials.
        string m_ob = MASTER_OB(arrow);
        arrow->remove_object();
        bow->unload_projectile();
        arrow = clone_object(m_ob);
        arrow->set_heap_size(1);
        arrow->move(actor, 1);
        arrow->load();
        loaded[actor] = arrow;
    }
    
    if (!objectp(arrow) && !objectp(arrow = find_arrows(actor, bow)))
    {
        actor->catch_msg("You do not possess an arrow to shoot.\n");
        remove_concentration(actor);
        return 0;
    }
    
    send_debug_message("archer_aimshot", "check_required_items success");
    
    return ({ bow, arrow });
} /* check_required_items */

/*
 * Function name:   check_valid_action
 * Description:     Perform ability-specific checks
 * Arguments:       1. (object) The player
 *                  2. (mixed *) The targets
 *                  3. (string) Arguments passed to the command
 *                  4. (int) Actual spell execution
 * Returns:         (int) 1 if we can continue, 0 if failure
 */
static int 
check_valid_action(object actor, mixed *targets, string arg, int execute)
{
    object *onslaught, tank;
    mixed   enemy;
    
    send_debug_message("archer_aimshot", "check_valid_action triggered");

    if (!::check_valid_action(actor, targets, arg, execute))
    {
        remove_concentration(actor);
        return 0;
    }
    
    if (actor->query_base_skill(SS_WEP_MISSILE) < 84)
    {
        actor->catch_msg("You must be a master in archery to accomplish such "
        + "a feat.\n");
        remove_concentration(actor);
        return 0;
    }
    
    if (QUICKSHOT->query_ability_active(actor))
    {
        actor->catch_msg("You have yet to recover from your recent "
        + "quickshot.\n");
        remove_concentration(actor);
        return 0;
    }
    
    onslaught = filter(all_inventory(environment(actor)),
                &operator(==)(, actor) @ &->query_attack());
    
    if (!pointerp(enemy = targets[0]) || objectp(enemy = enemy[0]))
        tank = enemy->query_attack();
    
    if (!objectp(tank) && (!actor->query_prop(OBJ_I_HIDE) &&
        actor->check_seen(enemy)))
    {
        actor->catch_msg("You must be hidden in order to ambush someone.\n");
        remove_concentration(actor);
        return 0;
    }
    
    /* 
     * Display a different message if the target is attacking you rather than
     * if you are under attack by other enemies.
     */
    if (objectp(tank) && tank == actor)
    {
        actor->catch_msg("You are unable to concentrate on sniping, having "
        + "garnered " + enemy->query_the_name(actor) + "'s undivided "
        + "attention.\n");
        remove_concentration(actor);
        return 0;
    }
    
    if (sizeof(onslaught))
    {
        actor->catch_msg(capitalize(COMPOSITE_LIVE(onslaught)) + " "
        + (sizeof(onslaught) > 1 ? "are" : "is") + " too focused on you "
        + "for you to be able to concentrate.\n");
        remove_concentration(actor);
        return 0;
    }
    
    send_debug_message("archer_aimshot", "check_valid_action success");
    // If it passes everything, return success
    return 1; 
} /* check_valid_action */

/*
 * Function name:   stop_ability
 * Description:     At any time during the preparation or cooldown period, one
 *                  can call this to remove the alarms.
 * Arguments:       (object) player - player for which to stop the ability and
 *                                    remove the alarms.
 * Returns:         (int) 0/1 - failure/success of stopping.
 */
public int
stop_ability(object player)
{
    int result;
    
    send_debug_message("archer_aimshot", "stop_ability initialized");
    if (result = ::stop_ability(player))
    {
        // This ability was successfully stopped. If so, we remove
        // the shadow and paralyze objects
        remove_concentration(player);
    }
    
    return result;
} /* stop_ability */

/*
 * Function name: hook_stopped_ability
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stopped_ability(object ability, object player)
{
    player->catch_msg("You cease your concentrated state and abandon the " 
    + "aimed shot.\n");
} /* hook_stopped_ability */

/*
 * Function name:   hook_special_in_cooldown
 * Description:     This function is called if the ability is in cooldown,
 *                  displaying a cooldown message.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_in_cooldown()
{
    write("You're not ready to prepare for another aimed shot.\n");
} /* hook_special_in_cooldown */

/*
 * Function name:   hook_special_complete
 * Description:     This gets called whenever the special is ready again.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_special_complete()
{
    write("You feel ready to execute an aimed shot again.\n");
} /* hook_special_complete */

/*
 * Function name:   hook_already_active
 * Description:     This gets called if the special is already active when the 
 *                  actor attempts to use it.
 * Arguments:       (object) ability - The ability being used.
 * Returns:         Nothing
 */
public void
hook_already_active(object ability)
{
    write("You are already preparing an aimed shot.\n");
} /* hook_already_active */

/*
 * Function name:   ability_msg
 * Description:     This function displays a message when the ability is being
 *                  activated.
 * Arguments:       None
 * Returns:         Nothing
 */
static void 
ability_msg(object actor, mixed *targets, string arg)
{
    int     concentrate;
    object  bow;
    
    send_debug_message("archer_aimshot", "ability_msg triggered");
    
    add_concentration(actor);
    
    if (objectp(bow = query_wielded_bow(actor)) && !loaded[actor])
    {
        actor->catch_msg("You nock an arrow and draw your " + bow->short()
        + ".\n");
        actor->tell_watcher(QCTNAME(actor) + " nocks an arrow and draws "
        + actor->query_possessive() + " " + bow->short() + ".\n");
    }
    
    actor->catch_msg("You fall into deep concentration as you carefully aim "
    + "your " + bow->short() + ".\n");
} /* ability_msg */

/*
 * Function name:   get_hitloc_id
 * Description:     Process the target combat object to get the hitloc id that
 *                  matches the specified location.
 * Arguments:       (object) actor - The one using the ability
 *                  (object) target - The target in which to check for a hitloc
 * Returns:         (int) - The hitloc id of the specified location
 */
public int
get_hitloc_id(object actor, object target)
{
    object  combat_ob;
    int    *hitloc_ids,
            newloc = -1,
            r_value;
    
    send_debug_message("archer_aimshot", "get_hitloc_id initialized");
    if (!objectp(target))
        return -1;
    
    r_value     = (1000 / (1 + actor->query_skill(SS_APPR_MON)));
    combat_ob   = target->query_combat_object();
    hitloc_ids  = combat_ob->query_hitloc_id();
    
    foreach(int hitloc: hitloc_ids)
    {
        // Dont get a loc without descs.
        if (!strlen(combat_ob->query_hitloc(hitloc)[HIT_DESC]))
            continue;
        
        // Dont get a loc that doesnt have a hit%
        if (!combat_ob->query_hitloc(hitloc)[HIT_PHIT])
            continue;
        
        if (newloc < 0)
        {
            newloc = hitloc;
            continue;
        }
        
        // Compare ACs and add a random factor based on appraise skill.
        if (combat_ob->query_hitloc(hitloc)[HIT_AC][0] + random(r_value) < 
            combat_ob->query_hitloc(newloc)[HIT_AC][0] + random(r_value))
            newloc = hitloc;
    }
    
    send_debug_message("archer_aimshot", "hitloc: " + newloc);
    return newloc;
} /* get_hitloc_id */

/*
 * Function name:   process_unspecified_targeting
 * Description:     Performs checks to verify that hitloc_id and enemy object
 *                  are both correct.
 * Arguments:       1. (object) actor - The actor of the ability
 *                  2. (object) enemy - The enemy of the ability
 * Returns:         (mixed *) An empty array or an array of arrays containing
 *                            the targets and desired hitloc
 */
private mixed *
process_unspecified_targeting(object actor, object enemy)
{
    send_debug_message("archer_aimshot", "process_unspecified_targeting triggered");
    if (!objectp(enemy))
        return ({ });
    
    send_debug_message("archer_aimshot", "process_unspecified_targeting enemy");
    int hitloc_id = get_hitloc_id(actor, enemy);
    
    if (hitloc_id == -1)
        return ({ enemy });
    
    send_debug_message("archer_aimshot", "process_unspecified_targeting hitloc");
    return ({ ({ enemy, hitloc_id }) });
} /* process_unspecified_targeting */

/*
 * Function name:   target_vulnerable_loc
 * Description:     This parses the attack arguments to set the desired hitloc.
 * Arguments:       1. (object) actor - the actor of the ability
 *                  2. (string) arg - the argument used
 * Returns:         (mixed *) An empty array or an array of arrays containing
 *                            the targets and desired hitloc
 */
public mixed *
target_vulnerable_loc(object actor, string arg)
{
    object *enemies;
    
    send_debug_message("archer_aimshot", "target_vulnerable_loc triggered");
    if (sizeof(enemies = target_one_other_present_living_or_enemy(actor, arg)))
    {
        if (random(80) > actor->query_skill(SS_APPR_MON))
        {
            appraising[actor] = 1;
            return enemies;
        }
        
        appraising[actor] = 0;
        
        string name = actor->query_real_name();
        int sniping = OPTIONS_MANAGER->query_option("SnipeSetting", name);
        /* Target the least armoured location if your vision is not impaired */
        if (!VISION_IMPAIRED(actor) && sniping)
            return process_unspecified_targeting(actor, enemies[0]);
        
        send_debug_message("archer_aimshot", "Vision impaired: "
        + VISION_IMPAIRED(actor));
        send_debug_message("archer_aimshot", "Not targeting vulnerable locs");
        return enemies;
    }
    
    send_debug_message("archer_aimshot", "target_vulnerable_loc failed");
    return ({});
} /* target_vulnerable_loc */

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
    int modifier = 100;
    
    if (objectp(modified_attack[this_player()]) &&
        modified_attack[this_player()] == this_player()->query_attack())
    {
        send_debug_message("archer_aimshot", "CAID Modifier at max");
        
        // There's a 20 caid cost to nightvision
        if (VISION_IMPAIRED(this_player()))
            modifier = 87;
        
        return modifier;
    }
    
    // There's a 20caid cost to nightvision
    if (VISION_IMPAIRED(this_player()))
        modifier = 78;
    
    // As we dont actually loose any "white hit" caid when ambushing, we need
    // lower the caid, unfortunately. Still a massive boost compared to the
    // quickshot
    send_debug_message("archer_aimshot", "CAID Modifier reduced");
    return modifier * 68 / 100;
} /* query_combat_aid_modifier */

/*
 * Function name:   query_hitloc_factor
 * Description:     This function applies the penalty for targeting a 
 *                  specific hitloc.
 * Arguments:       None
 * Returns:         (int) Percentage of damage for targeted attacks
 */
public int
query_hitloc_factor()
{
    // Set this to 100 when we have a good resource code to drain mana.
    return ::query_hitloc_factor();
} /* query_hitloc_factor */

/*
 * Function name:   do_ability
 * Description:     The main entry point for abilities
 * Arguments:       (string) arg - the argument passed in for targeting
 * Returns:         (int) 0/1 - failure/success of the action
 */
public int 
do_ability(string arg)
{
    if (!this_player()->query_wiz_level() &&
        this_player()->query_guild_name_occ() != GUILD_NAME)
        return 0;
    
    return ::do_ability(arg);
} /* do_ability */

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
    write("Your target is nowhere to be found.\n");
} /* hook_targets_gone */