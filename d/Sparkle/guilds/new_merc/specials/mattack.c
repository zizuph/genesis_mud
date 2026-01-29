/*
 *  /d/Sparkle/guilds/new_merc/specials/mattack.c
 *
 *  This is the melee damage special for the Free Mercenary guild
 *  in Sparkle. It has been based somewhat on the gore special of
 *  the Minotaur guild.
 *
 *  Created March 2009, by Cooper Sherry (Gorboth)
 *    special thanks to Petros for doing most of the structural work
 * 
 *  Changes: 
 *  2017-10-29 - Cotillion
 *  - Fixed query_dt to only return one damage type
 */
#pragma strict_types

#include "../merc_defs.h"
#include "defs.h"
inherit DAMAGE_LIB;

#include <macros.h>
#include <options.h>
#include <formulas.h>
#include <files.h>
#include <adverbs.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <time.h>
#include <wa_types.h>
#include <filter_funs.h>

#include DEBUGGER_LIB

#define FATIGUE_COST     2
#define HEALTH_COST      5
#define CRITICAL_CHANCE  1000
#define LOG_FILE         ("criticals")

/* Prototypes */
public void             config_ability();
public void             special_did_hit(int aid, string hdesc, int hid, 
                                        int phurt, object enemy, int dt, 
                                        int phit, int dam, mixed * items,
                                        int result);
static int              check_valid_action(object player, mixed * targets, 
                                           string arg, int execute);
public void             apply_costs_to_player(object player);

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

    set_combat_aid(68);
    set_tohit(100);       /* 78% chance of hitting */

    set_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX,
                  SKILL_WEIGHT, 20, TS_WIS }) );
    set_skills( ({ SS_MERC_TACTICS_SKILL }) );
    set_ability_name("mattack");

    set_guild_stat_modifier(SS_OCCUP, 20, 100);        
} /* config_ability */


/*
 * Function:    query_ability_prep_time
 * Description: Adjusts the prep time based on guild special skill
 */ 
public int
query_ability_prep_time()
{
    int special_skill;
    
    special_skill = this_player()->query_skill(SS_MERC_TACTICS_SKILL);
    return 8 - (special_skill / 25); // 4-8 seconds
} /* query_ability_prep_time */


/*
 * Function:    query_ability_cooldown_time
 * Description: Adjusts the prep time based on guild special skill
 */ 
public int
query_ability_cooldown_time()
{
    int special_skill;
    
    special_skill = this_player()->query_skill(SS_MERC_TACTICS_SKILL);
    return 8 - (special_skill / 25); // 4-8 seconds
} /* query_ability_cooldown_time */


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
    /* Percentage of combat aid rises from 50% to 100% as skill
     * increases. This is done because the ability time also changes
     * as skill changes. In order to keep the damage the same, we
     * adjust these two factors.
     */
    int special_skill, add_time, aid;
    
    special_skill = this_player()->query_skill(SS_MERC_TACTICS_SKILL);    
    add_time = 4 - (special_skill / 25);
    aid = 400 / (4 + add_time);
    
    return aid;
} /* query_combat_aid_modifier */


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
 * Function:    check_required_items
 * Description: Checks to make sure that the person has a proper weapon
 *              Used to pass the "items" mixed array
 */
static mixed * 
check_required_items(object actor, mixed * targets,
                     string arg, int pretest)
{
    int best_pen =  0;
    int best_aid = -1;
    object weapon;
    
    weapon = query_best_wielded_weapon(actor);

    if (objectp(weapon))
    {
        if (weapon->query_wt() == W_MISSILE)
        {
            actor->catch_msg("Mercenary tactics do not include"
              + " knowledge of archery!\n");
            return 0;
        }

        return ({ weapon });
    }
    
    /* If we get here, player must be unarmed. In that case, we try and
     * find the best pen among their unarmed locations.
     */
    foreach (int aid : actor->query_combat_object()->query_attack_id())
    {
        mixed results = actor->query_combat_object()->query_attack(aid);
        if (results[1][0] > best_pen)
        {
            best_pen = results[1][0];
            best_aid = aid;
        }
    }
    
    if (best_aid < 0)
    {
        actor->catch_msg("You have nothing you can attack with!\n");
        return 0;
    }
    
    return ({ best_aid });
} /* check_required_items */


/*
 * Function name:        nonlethal_descs
 * Description  :        Provide descriptions for crit attacks that do
 *                       near-lethal damage, but do not kill
 * Arguments    :        object attacker - the one performing the attack
 *                       object victim   - the one being attacked
 *                       object wep      - the weapon we are using
 */
public void
nonlethal_descs(object attacker, object victim, object wep)
{
    string  cattacker  = QCTNAME(attacker);
    string  tattacker  = QTNAME(attacker);
    string  cattacker2 = attacker->query_The_name(victim);
    string  tattacker2 = attacker->query_the_name(victim);
    string  cvictim    = QCTNAME(victim);
    string  tvictim    = QTNAME(victim);
    string  cvictim2   = victim->query_The_name(attacker);
    string  tvictim2   = victim->query_the_name(attacker);
    string  his        = attacker->query_possessive();
    string  he         = attacker->query_pronoun();
    string  him        = attacker->query_objective();
    string  vhis       = victim->query_possessive();
    string  vhe        = victim->query_pronoun();
    string  vhim       = victim->query_objective();
    string  weapon;
    int     onehander = 0;
    int     wep_type;

    if (!objectp(wep))
    {
        /* This will be our designation for unarmed combat */
        wep_type = 999;
    }
    else
    {
        wep_type  = wep->query_wt();
        weapon    = wep->short();
        onehander = wep->query_hands() != W_BOTH;
    }

    /* Curse those non-bladed polearms!! */
    if (wep_type == W_POLEARM && wep->query_dt() == W_BLUDGEON)
    {
            tell_room(environment(attacker),
                cvictim + " advances on " + tattacker + " in a sudden"
              + " rush. Countering the offensive, " + tattacker 
              + " spins, holding the " + weapon + " outward for momentum"
              + " and balance. With terrible impact, " + tvictim 
              + " charges with full force into the business-end of the"
              + " swinging " + weapon + ", which sends " + vhim 
              + " flying off " + vhis + " feet to land in a crumpled"
              + " heap a few yards back! " + cvictim + " staggers back"
              + " into the fray, dazed by the collision.\n",
               ({ attacker, victim }) );
            attacker->catch_tell(cvictim2 + " barrels blindly toward you"
              + " in a sudden rush. Anticipating the maneuver, you"
              + " sidestep and spin round with your " + weapon + " using"
              + " its centrifugal force for balance and power. "
              + cvictim2 + " collides headlong with the business-end of your"
              + " weapon, and is lifted off " + vhis + " feet by the force"
              + " of the impact, which sends " + vhim + " sailing"
              + " backwards to land painfully on " + vhis + " back a"
              + " few yards away! Staggering back up, " + vhe + " slowly"
              + " readvances into combat, dazed by the incident.\n");
            victim->catch_tell("With a sudden vigor, you rush confidently"
              + " towards " + tattacker2 + ", who sidesteps your attack,"
              + " and spins " + his + " " + weapon + " round. To your"
              + " dismay, and with unbelievable impact, you collide"
              + " headlong with the business-end of the " + weapon + ", the"
              + " force of which lifts you off your feet and sends you"
              + " flying backward to land painfully on the ground a few"
              + " yards back! Angry and flustered, you jump up and"
              + " advance warily to face your opponent again.\n");
        return;
    }

    switch (wep_type)
    {
    case W_AXE:
        if (onehander)
        {
            tell_room(environment(attacker),
                cattacker + " spins with a sudden deft maneuver, sinking"
              + " the blade of " + his + " " + weapon + " savagely into "
              + tvictim + "'s unguarded shoulder blade!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Spinning in a sudden deft maneuver,"
              + " you sink your " + weapon + " savagely into "
              + tvictim2 + "'s shoulder blade!\n");
            victim->catch_tell("Spinning in a sudden deft maneuver, "
              + tattacker2 + " sinks " + his + " " + weapon + " savagely"
              + " into your shoulder blade. Incredible pain surges"
              + " through your body!\n");
        }
        else
        {
            tell_room(environment(attacker),
                "Heaving mightily, " + tattacker + " brings the blade of "
              + his + " " + weapon + " crashing down through "
              + tvictim + "'s defenses, burying the blade deep into "
              + tvictim + "'s exposed chest!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("You heave mightily, bringing the"
              + " blade of your " + weapon + " crashing down through "
              + tvictim2 + "'s defenses to bury the blade deep into "
              + vhis + " exposed chest!\n");
            victim->catch_tell(cattacker2 + " heaves mightily, bringing"
              + " the blade of " + his + " " + weapon + " crashing"
              + " down through your unprepared defenses to sink with"
              + " horrifying pain into your exposed chest!\n");
        }
        break;
    case W_SWORD:
        if (onehander)
        {
            tell_room(environment(attacker),
                "Offering a quick feint, " + tattacker + " springs"
              + " deftly forward slicing a nasty gash in " + tvictim
              + "'s exposed belly with " + his + " " + weapon + "!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Seeing an opening in " + tvictim2
              + "'s defences, you feint left and then spring quickly"
              + " forward slicing a nasty gash in " + tvictim2 + "'s"
              + " exposed belly with your " + weapon + "!\n");
            victim->catch_tell(cattacker2 + " feints to the right, and"
              + " then following the opening in your defenses as you"
              + " react, leapes forward, slicing a gash with " + his
              + " " + weapon + " in your exposed belly! Dreadful pain"
              + " washes over your entire body.\n");
        }
        else
        {
            tell_room(environment(attacker),
                "With sudden might and speed, " + tattacker + " lunges"
              + " forward with " + his + " " + weapon + ", penetrating "
              + tvictim + "'s defenses and plunging the point of the"
              + " blade deep into the flesh of " + vhis + " left"
              + " breast! " + cvictim + " staggers back, clutching"
              + " painfully at the wound.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Gripping your " + weapon + " tightly,"
              + " you lunge forward with all of your mustered strength,"
              + " penetrating " + tvictim2 + "'s defenses, and plunging"
              + " the point of the blade deep into the flesh of "
              + vhis + " left breast! " + cvictim2 + " staggers back,"
              + " clutching painfully at the wound and staring at you"
              + " with surprise and anger.\n");
            victim->catch_tell("With surprising speed and force, "
              + tattacker2 + " lunges at you with the point of " + his
              + " " + weapon + ", plunging the blade into the flesh of"
              + " your left breast! Reeling in pain and anger, you "
              + "stagger back, clutching at the wound.\n");
        }
        break;
    case W_CLUB:
        if (onehander)
        {
            tell_room(environment(attacker),
                "Brandishing " + his + " " + weapon + " with a terrible"
              + " burst of speed, " + tattacker + " springs behind "
              + tvictim + ", smashing the weapon into " + vhis
              + " exposed back with tremendous force! " + cvictim
              + " sprawles upon the ground, and struggles painfully back"
              + " to " + vhis + " feet.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Seizing on the opportunity of the"
              + " moment, you fling yourself around and behind "
              + tvictim2 + ", using the momentum of your movement to add"
              + " weight to your weapon hand. With a staggering blow,"
              + " you deliver the " + weapon + " directly to the small"
              + " of " + tvictim2 + "'s back, sending " + vhim
              + " sprawling in pain to the ground! Thrashing violently, "
              + vhe + " struggles back to " + vhis + " feet.\n");
            victim->catch_tell("In a surprising maneuver, "
              + tattacker2 + " flings " + him + "self around and behind"
              + " you to bring " + his + " " + weapon + " crashing into"
              + " the small of your back with hideous force! Your senses"
              + " explode with pain, and you find yourself sprawled on"
              + " the ground, clutching in every direction for support."
              + " You drag yourself back to your feet as quickly as you"
              + " are able.\n");
        }
        else
        {
            tell_room(environment(attacker),
                cvictim + " advances on " + tattacker + " in a sudden"
              + " rush. Countering the offensive, " + tattacker 
              + " spins, holding the " + weapon + " outward for momentum"
              + " and balance. With terrible impact, " + tvictim 
              + " charges with full force into the business-end of the"
              + " swinging " + weapon + ", which sends " + vhim 
              + " flying off " + vhis + " feet to land in a crumpled"
              + " heap a few yards back! " + cvictim + " staggers back"
              + " into the fray, dazed by the collision.\n",
               ({ attacker, victim }) );
            attacker->catch_tell(cvictim2 + " barrels blindly toward you"
              + " in a sudden rush. Anticipating the maneuver, you"
              + " sidestep and spin round with your " + weapon + " using"
              + " its centrifugal force for balance and power. "
              + cvictim2 + " collides headlong with the business-end of your"
              + " weapon, and is lifted off " + vhis + " feet by the force"
              + " of the impact, which sends " + vhim + " sailing"
              + " backwards to land painfully on " + vhis + " back a"
              + " few yards away! Staggering back up, " + vhe + " slowly"
              + " readvances into combat, dazed by the incident.\n");
            victim->catch_tell("With a sudden vigor, you rush confidently"
              + " towards " + tattacker2 + ", who sidesteps your attack,"
              + " and spins " + his + " " + weapon + " round. To your"
              + " dismay, and with unbelievable impact, you collide"
              + " headlong with the business-end of the " + weapon + ", the"
              + " force of which lifts you off your feet and sends you"
              + " flying backward to land painfully on the ground a few"
              + " yards back! Angry and flustered, you jump up and"
              + " advance warily to face your opponent again.\n");
        }
        break;
    case W_KNIFE:
        tell_room(environment(attacker),
            "With cat-like speed, " + tattacker + " leaps past " 
          + tvictim + "'s defenses, and plunges " + his + " " + weapon
          + " deep into the meat of " + vhis + " underarm! Flinching"
          + " backwards, " + tvictim + " cradles the wound, glaring at " 
          + tattacker + " in surprise and pain.\n",
               ({ attacker, victim }) );
        attacker->catch_tell("Seeing an opening in " + tvictim2 + "'s"
          + " defences, you stab forward with all of your might,"
          + " plunging your " + weapon + " deep into the meat of "
          + vhis + " underarm! Flinching in pain, " + tvictim2
          + " staggers backward, cradling the wound, and glaring at"
          + " you in surprise and anger.\n");
        victim->catch_tell("Judging a weakness in your stance, " 
          + tattacker2 + " stabs suddenly towards your heart. You"
          + " instinctively flinch, but only in time to save your very"
          + " life, as the " + weapon + " plunges deeply into the meat of"
          + " your underarm! Staggering backward in pain, you glare with"
          + " hatred at " + tattacker2 + " and nurse your painful wound.\n");
        break;
    case W_POLEARM:
        tell_room(environment(attacker),
            "Lunging forward with sudden speed and dexterity, "
          + tattacker + " forces " + his + " " + weapon + " through "
          + tvictim + "'s defences, plunging the weapon deeply into the"
          + " flesh of " + vhis + " shoulder! " + cvictim + " falls"
          + " backwards, and rolls to " + vhis + " feet, clutching at"
          + " the wound in pain.\n",
               ({ attacker, victim }) );
        attacker->catch_tell("Noticing a mistake in " + tvictim2 + "'s"
          + " stance, you lunge forward with all of your mustered speed"
          + " and strength, thrusting your " + weapon + " deeply into the"
          + " flesh of " + his + " shoulder! The force of the blow"
          + " knocks " + vhim + " backwards. Quickly rolling back to "
          + vhis + " feet, " + vhe + " winces in pain, clutching at the"
          + " wound.\n");
        victim->catch_tell(cattacker2 + " lunges suddenly toward you,"
          + " thrusting his " + weapon + " with alarming speed and"
          + " dexterity. Attempting to avoid the blade, the best you are"
          + " able to do is to twist your heart clear of the weapon,"
          + " which plunges painfully into your shoulder! Falling"
          + " backwards, you quickly roll to your feet, clutching at the"
          + " terrible pain in your cut flesh.\n");
        break;
    default: /* unarmed */
        tell_room(environment(attacker),
             cattacker + " grabs " + tvictim + " by the skull, dragging "
           + vhis + " head downward just in time to receive a swift and"
           + " devastating knee to the face! Dazzled by pain and"
           + " surprise, " + tvictim + " tumbles backward covering "
           + vhis + " wounded mouth with " + vhis + " arm.\n",
               ({ attacker, victim }) );
        attacker->catch_tell("Anger takes you suddenly, and you grab "
           + tvictim2 + "'s skull with both of your hands, dragging "
           + vhis + " head downward as you bring your leg up to deliver"
           + " a devastating knee into " + vhis + " face! Tumbling back"
           + " from you in pain and disbelief, " + tvictim2 + " covers "
           + vhis + " wounded mouth with " + vhis + " arm.\n");
        victim->catch_tell("To your complete surprise, " + tattacker2
           + " grabs you suddenly by the back of the skull, and drags"
           + " your head downward to deliver a devastating knee right to"
           + " your face! The world disappears for a moment, as you"
           + " tumble backward, blinded by pain and dazzling lights.\n");
        break;
    }
} /* nonlethal_descs */


/*
 * Function name:        lethal_descs
 * Description  :        Provide descriptions for crit attacks that do
 *                       killing damage to the victim
 * Arguments    :        object attacker - the one performing the attack
 *                       object victim   - the one being attacked
 *                       object wep      - the weapon we are using
 */
public void
lethal_descs(object attacker, object victim, object wep)
{
    string  cattacker  = QCTNAME(attacker);
    string  tattacker  = QTNAME(attacker);
    string  cattacker2 = attacker->query_The_name(victim);
    string  tattacker2 = attacker->query_the_name(victim);
    string  cvictim    = QCTNAME(victim);
    string  tvictim    = QTNAME(victim);
    string  cvictim2   = victim->query_The_name(attacker);
    string  tvictim2   = victim->query_the_name(attacker);
    string  his        = attacker->query_possessive();
    string  he         = attacker->query_pronoun();
    string  him        = attacker->query_objective();
    string  vhis       = victim->query_possessive();
    string  vhe        = victim->query_pronoun();
    string  vhim       = victim->query_objective();
    string  weapon;
    int     onehander = 0;
    int     wep_type;

    if (!objectp(wep))
    {
        /* This will be our designation for unarmed combat */
        wep_type = 999;
    }
    else
    {
        wep_type  = wep->query_wt();
        weapon    = wep->short();
        onehander = wep->query_hands() != W_BOTH;
    }

    /* Curse those non-bladed polearms!! */
    if (wep_type == W_POLEARM && wep->query_dt() == W_BLUDGEON)
    {
            tell_room(environment(attacker),
                "In a dazzling display of beastly strength, "
              + tattacker + " rears up, bringing " + his + " " + weapon
              + " down upon " + tvictim + " with the speed and power"
              + " of an avalanche. Unslowed in its descent, the weapon"
              + " drives downward, carrying flesh and bone with it,"
              + " breaking the body of " + tvictim + " like a dry barrel"
              + " upon the ground!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Brimming with sudden and terrible"
              + " wrath, you rear up, brandishing your " + weapon
              + " with beastial strength. With the speed and power of an"
              + " avalanche, you bring the weapon down upon " + tvictim2 
              + ". Unslowed in its descent, the " + weapon + " drives"
              + " downward, carrying flesh and bone with it, breaking"
              + " the body of " + tvictim2 + " like a dry barrel upon the"
              + " ground at your feet!\n");
            victim->catch_tell("To your horror, " + tattacker2 + " rears"
              + " up in a dazzling display of beastial strength,"
              + " brandishing " + his + " " + weapon + " with great"
              + " ferocity above you! As the weapon comes down, it is as"
              + " if you are caught beneath a mighty avalanche, your"
              + " flesh and bones being driven to the ground, breaking"
              + " as if made of brittle wood. Excruciating pain ravages"
              + " your ruined body, and then slowly fades as your life"
              + " slips away.\n");
        return;
    }

    switch (wep_type)
    {
    case W_AXE:
        if (onehander)
        {
            tell_room(environment(attacker),
                "Crouching low, " + tattacker + " springs up suddenly,"
              + " and with terrible speed sends the blade of " + his
              + " " + weapon + " slicing through " + tvictim + "'s"
              + " neck! Staggering backwards, " + tvictim + "'s"
              + " lifeless body falls limply to the ground, the head"
              + " coming apart from the shoulders as it lands.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("You crouch low, and then with great"
              + " exertion spring upwards, swinging your weapon hand with"
              + " all your mustered strength in a wide arcing motion"
              + " towards " + tvictim2 + "'s neck. Connecting true, the "
              + weapon + "'s blade passes cleanly through flesh and"
              + " bone, and " + tvictim2 + " staggers back, falling"
              + " headless to the ground at your feet!\n");
            victim->catch_tell(cattacker2 + " crouches suddenly low, and"
              + " then springs upward with horrible strength and speed,"
              + " swinging " + his + " " + weapon + " toward your neck"
              + " before you can prepare any defense! Pain dazzles your"
              + " senses for the briefest instant, and then, as if from"
              + " above, you see your headless body hit the ground.\n");
        }
        else
        {
            tell_room(environment(attacker),
                "With furious strength, " + tattacker + " raises " + his
              + " " + weapon + " high, bursting toward " + tvictim 
              + " with a shout of wrath. The weapon crashes down upon " 
              + tvictim + "'s brow with a sickening crack, driving the"
              + " cloven skull downward as the heavy weapon grinds to a"
              + " halt on the ground! " + cattacker + " pulls the"
              + " blade of the " + weapon + " from the twisted and"
              + " lifeless body.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Filled with a sudden wrath, you charge"
              + " at " + tvictim2 + " with your " + weapon + " held high"
              + " above your head. Your blind fury unleashes itself as"
              + " the weapon comes crashing down upon " + tvictim2 + "'s"
              + " head, cleaving the skull in two, and driving it to the"
              + " ground with the force of your blow! With a grunt of"
              + " satisfaction, you pull the blade from the now lifeless"
              + " body.\n");
            victim->catch_tell("With a sudden howl of wrath, "
              + tattacker2 + " rushes toward you, " + weapon + " held"
              + " high. Caught off guard, and staggering backward, you"
              + " bring your defenses up too late, as the deadly blade"
              + " comes crashing down toward your face! A splitting rush"
              + " of pain sends you spinning into darkness, and you"
              + " remember nothing more.\n");
        }
        break;
    case W_SWORD:
        if (onehander)
        {
            tell_room(environment(attacker),
                "Bursting through " + tvictim + "'s defences, " 
              + tattacker + " drives the point of " + his + " " 
              + weapon + " deep into " + tvictim + "'s belly, ramming"
              + " the blade clean through " + vhis + " torso to emerge"
              + " bloodied from from the other side! The two opponents"
              + " remain locked for a moment in a deadly embrace, and"
              + " then " + tvictim + "'s eyes glaze over, and " + vhe 
              + " slumps lifelessly to the ground, sliding off of " 
              + tattacker + "'s blade to fall upon " + vhis + " side.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Mustering all your skill and strength,"
              + " you burst through " + tvictim2 + "'s defenses and drive"
              + " the point of your " + weapon + " deep into " + vhis 
              + " belly, ramming the blade clean through " + vhis 
              + " torso to emerge bloodied from the other side! Locked"
              + " face to face with you, a look of rage, and then of"
              + " sorrow, and then of death passes through " + tvictim2
              + "'s eyes, who slides at last off of your blade to slump"
              + " lifeless to the ground at your feet.\n");
            victim->catch_tell(cattacker2 + " bursts suddenly through your"
              + " defenses, driving the point of " + his + " " + weapon
              + " deep into your belly! A sharp and freezing pain washes"
              + " over you as you feel the blade emerge from the flesh of"
              + " your back, having run clean through your torso. Locked"
              + " face to face with " + tattacker2 + " you glare defiantly"
              + " into " + his + " eyes, only to be overcome with memories"
              + " from your past as the world begins to fade. The last"
              + " thing you remember is pity in the eyes of your slayer"
              + " as " + he + " releases you from " + his + " grasp.\n");
        }
        else
        {
            tell_room(environment(attacker),
                "Moving with great breadth and power, " + tattacker 
              + " twirls " + his + " " + weapon + " above " + his 
              + " head, spinning with its momentum in a devastating arc"
              + " towards the neck of " + tvictim + ". Finding its mark,"
              + " the blade passes through sinew and bone, beheading "
              + tvictim + " where " + vhe + " stands!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Filled with a sudden inspiration of"
              + " prowess, you twirl your " + weapon + " above your head,"
              + " regripping it tightly as it fits once again into your"
              + " palms. Following its momentum, you spin with deft power"
              + " and balance aiming the blade at " + tvictim2 + "'s neck."
              + " Unable to react in time, " + tvictim2 + " stands like"
              + " a statue as the " + weapon + " severs sinew and bone,"
              + " behedding " + vhim + " where " + vhe + " stands!\n");
            victim->catch_tell("In a dazzling display of swordsmanship, "
              + tattacker2 + " twirls " + his + " " + weapon + " above "
              + his + " head, spinning with confusing motion to follow"
              + " the momentum of the blade as it travels around on your"
              + " left. Bewildered, you discover that the blade has"
              + " traveled fast, too fast, and now comes with all its"
              + " speed and power on your right aimed precisely at your"
              + " undefended neck! You stiffen as the " + weapon 
              + " connects, feeling only an instant of pain before all"
              + " goes black.\n");
        }
        break;
    case W_CLUB:
        if (onehander)
        {
            tell_room(environment(attacker),
                "With a cry of rage, " + tattacker + " spins with blinding"
              + " speed, throwing " + his + " weapon arm out in a flash"
              + " of deadly force which connects squarely with the side"
              + " of " + tvictim + "'s head! With a sickening crack, " 
              + tvictim + " topples to the ground, " + vhis + " neck bent"
              + " at an impossible angle, and lies dead at " + tattacker
              + "'s feet.\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Rage fills your throat, and with a"
              + " sudden burst of skill and power, you spin with blinding"
              + " speed, throwing your weapon arm out in a flash of"
              + " deadly force which connects squarely with the side of "
              + tvictim2 + "'s head! No match for your " + weapon + ", "
              + tvictim2 + "'s neck snaps sideways with a sickening crack,"
              + " bent at an impossible angle. Toppling, it is obvious"
              + " that " + vhe + " is dead before " + vhe + " hits the"
              + " ground.\n");
            victim->catch_tell(cattacker2 + " lets fly a sudden cry of"
              + " rage, and spins with blinding speed, sending " + his
              + " " + weapon + " hurtling toward your head with deadly"
              + " force! Sound and pain are cut off in an instant as"
              + " blackness covers your eyes.\n");
        }
        else
        {
            tell_room(environment(attacker),
                "In a dazzling display of beastly strength, "
              + tattacker + " rears up, bringing " + his + " " + weapon
              + " down upon " + tvictim + " with the speed and power"
              + " of an avalanche. Unslowed in its descent, the weapon"
              + " drives downward, carrying flesh and bone with it,"
              + " breaking the body of " + tvictim + " like a dry barrel"
              + " upon the ground!\n",
               ({ attacker, victim }) );
            attacker->catch_tell("Brimming with sudden and terrible"
              + " wrath, you rear up, brandishing your " + weapon
              + " with beastial strength. With the speed and power of an"
              + " avalanche, you bring the weapon down upon " + tvictim2 
              + ". Unslowed in its descent, the " + weapon + " drives"
              + " downward, carrying flesh and bone with it, breaking"
              + " the body of " + tvictim2 + " like a dry barrel upon the"
              + " ground at your feet!\n");
            victim->catch_tell("To your horror, " + tattacker2 + " rears"
              + " up in a dazzling display of beastial strength,"
              + " brandishing " + his + " " + weapon + " with great"
              + " ferocity above you! As the weapon comes down, it is as"
              + " if you are caught beneath a mighty avalanche, your"
              + " flesh and bones being driven to the ground, breaking"
              + " as if made of brittle wood. Excruciating pain ravages"
              + " your ruined body, and then slowly fades as your life"
              + " slips away.\n");
        }
        break;
    case W_KNIFE:
        tell_room(environment(attacker),
            "Twisting " + his + " way inside " + tvictim + "'s defences, "
          + tattacker + " rams " + his + " " + weapon + " up beneath "
          + tvictim + "'s chin, burying the weapon deeply in the flesh of"
          + " the throat! Clutching desperately at the wound, " + tvictim
          + " falls to the ground and soon ceases all movement.\n",
               ({ attacker, victim }) );
        attacker->catch_tell("With uncharacteristic skill and speed, you"
          + " thrust yourself inside " + tvictim2 + "'s defenses, and stab"
          + " immediately upward, burying your " + weapon + " into the"
          + " soft flesh of " + vhis + " throat! Clutching desperately at"
          + " the wound with spasms of pain, " + tvictim2 + " falls to the"
          + " ground, where " + vhe + " quickly falls still.\n");
        victim->catch_tell("To your amazement, you find that "
          + tattacker2 + " dashes within your defences, brandishing " 
          + his + " deadly " + weapon + ". Before you can react,"
          + " horrifying pain stabs into your mind as you feel the weapon"
          + " being stabbed deeply into the flesh of your throat! Choking"
          + " with terror and dismay, you collapse to the ground,"
          + " desperately attempting to remove the weapon. Slowly, the"
          + " world fades to black.\n");
        break;
    case W_POLEARM:
        tell_room(environment(attacker),
            "With ferocious strengh and terrifying speed, " + tattacker
          + " runs and leaps toward " + tvictim + ", sailing through the"
          + " air with " + his + " " + weapon + " pointed downward for"
          + " the kill. Unable to counter the move, " + tvictim
          + " gives out a yelp of dismay before the onslaught, and is"
          + " struck through the chest by the blade, which pins " + vhis
          + " dying body to the ground!\n",
               ({ attacker, victim }) );
        attacker->catch_tell("Feeling the lust of battle rise, you dash"
          + " forward, leaping high in the air above " + tvictim2 + " with"
          + " your " + weapon + " pointed directly at " + vhis + " heart."
          + " Sensing " + vhis + " doom, " + tvictim2 + " yelps in dismay"
          + " before being pinned to the ground by your blade, which runs "
          + vhim + " cleanly through the chest!\n");
            victim->catch_tell(cattacker2 + " runs at you suddenly, leaping"
          + " high in the air above your head and descending with " + his
          + " " + weapon + " pointed directly at your unguarded frame!"
          + " In terror and dismay, you yelp and attempt to flinch away"
          + " from the danger, but the blade comes too fast, piercing your"
          + " chest and forcing you to the ground where you are pinned."
          + " Pain overcomes you, and death follows quickly.\n");
        break;
    default:
        tell_room(environment(attacker),
            cattacker + " spins swiftly to the side of " + tvictim 
          + ", bringing " + his + " arm flailing sidelong for a"
          + " devastating chop directly to " + tvictim + "'s exposed"
          + " throat! Clutching wildly at " + vhis + " neck, " + tvictim
          + " drops immediately to " + vhis + " knees, choking and unable"
          + " to draw a breath. As " + vhe + " struggles more and more"
          + " desperately, the color of " + vhis + " face darkens,"
          + " finally flushing a deep red as " + he + " falls forward"
          + " onto " + vhis + " belly and lies still.\n",
               ({ attacker, victim }) );
        attacker->catch_tell("Judging your opponent carefully, you"
          + " spin swiftly to " + tvictim2 + "'s side, throwing your arm in"
          + " for a devastating chop to " + vhis + " exposed throat!"
          + " Clutching wildly at " + vhis + " neck, " + tvictim2 + " drops"
          + " immediately to " + vhis + " knees, choking and unable to"
          + " draw a breath. As " + vhe + " struggles more and more"
          + " desperately, the color of " + vhis + " face darkens, finally"
          + " flushing a deep red as " + vhe + " falls forward onto " 
          + vhis + " belly and lies still.\n");
        victim->catch_tell("Spinning swiftly to your side, " + tattacker2
          + " throws an arm outwards, bringing it towards you with"
          + " blinding speed for a devastating chop to your exposed"
          + " throat! You feel your larynx crushed by the blow, and drop"
          + " to your knees, overcome with pain and the need to draw a"
          + " breath! Unable to get any air, you struggle in vain for"
          + " life, which slips agonizingly away.\n");
        break;
    }
} /* lethal_descs */


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
    object  player;
    string *attack_message;
    int     hit_lvl;
    int     lethal_attack;
    int     pen;
    string *swing_descs;
    string  wep_desc;
    string  contact_desc = "striking";
    string *effect_desc;
    string *death_messages;
    string  kill_loc = one_of_list( ({ "chest", "neck", "groin" }) );
    mixed   hitresult;
    
    player = this_player();
    
    if (phurt >= 0) 
    {
    	/* remove some of the attacker's panic */
    	player->add_panic(-3 - phurt / 5);

        /* There is a one in one-thousand chance that a mercenary
         * attack will score a critical hit. In this case, damage
         * is x3 from normal. Actual critical hits for normal combat
         * are x5, but we don't want that kind of power for specials.
         */
        if (!random(CRITICAL_CHANCE))
        {
            write_file(LOG_DIR + LOG_FILE,
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
              + ctime(time())[11..18] + ") "
              + capitalize(player->query_real_name()) + " got a"
              + " crit! (this is for debugging only.)\n");

            pen = calculate_damage(player, enemy, items, 0, result);
            pen *= 4;
            hitresult = enemy->hit_me(pen, dt, player, -1, hid);

            write_file(LOG_DIR + LOG_FILE,
                TIME2FORMAT(time(), "mm/dd/yyyy") + " ("
              + ctime(time())[11..18] + ") "
              + capitalize(player->query_real_name()) + " got a"
              + " crit on " + capitalize(enemy->query_name())
              + " for +" + hitresult[3] + " damage.\n");

            /* The attack was lethal. */
            if (enemy->query_hp() <= 0)
    	    {
                lethal_descs(player, enemy, items[0]);
    	        enemy->do_die(player);

                if (interactive(enemy))
                {
                    write_file(LOG_DIR + LOG_FILE,
                        "------ " + capitalize(enemy->query_name())
                      + " was killed as a result!\n");
                }

                return;
    	    }

            nonlethal_descs(player, enemy, items[0]);
            return;
        }
    
        swing_descs = ({ "feeble",
                         "ineffective",
                         "rough",
                         "fairly steady",
                         "steady",
                         "skillful",
                         "deft",
                         "expert",
                         "masterful",
                         "terrifying",
                         "uncanny",
                       });

        if (intp(items[0]))
        {
            wep_desc = one_of_list( ({ "left foot",
                                       "right foot",
                                       "left elbow",
                                       "right elbow",
                                       "left fist",
                                       "right fist",
                                    }) );
            kill_loc = one_of_list( ({ "skull", "rib cage",
                                       "spine" }) );
            death_messages = ({
                "With a sickening crunch, the force of"
              + " your blow crushes "
              + enemy->query_possessive() + " "
              + kill_loc + "!",

                "A sickening crunch is the last thing you"
              + " hear as the force of the blow crushes"
              + " your " + kill_loc + " and all goes"
              + " black!",

                "With a sickening crunch, the force of"
              + " the blow crushes "
              + enemy->query_possessive() + " "
              + kill_loc + "!", });
        }
        else
        {
            wep_desc = items[0]->short();

            switch(items[0]->query_wt())
            {
                case W_SWORD:
                case W_AXE:
                case W_KNIFE:
                case W_POLEARM:
                    /* Curse those non-bladed polearms!! */
                    if (items[0]->query_dt() == W_BLUDGEON)
                    {
                        kill_loc = one_of_list( ({ "skull", "rib cage",
                                                   "spine" }) );
                        death_messages = ({
                            "With a sickening crunch, the force of"
                          + " your blow crushes "
                          + enemy->query_possessive() + " "
                          + kill_loc + "!",

                            "A sickening crunch is the last thing you"
                          + " hear as the force of the blow crushes"
                          + " your " + kill_loc + " and all goes"
                          + " black!",

                            "With a sickening crunch, the force of"
                          + " the blow crushes "
                          + enemy->query_possessive() + " "
                          + kill_loc + "!", });
                        break;
                    }

                    contact_desc = "slashing";
                    death_messages = ({
                        "Blood sprays outward in a wide arc as your"
                      + " blade tears a lethal gash in "
                      + enemy->query_possessive() + " "
                      + kill_loc + "!",

                        "You feel the blade catch and rip a lethal"
                      + " gash in your " + kill_loc + "! The last"
                      + " sight you see is your own blood spraying"
                      + " outward in a wide arc ... ",

                        "Blood sprays outward in a wide arc as "
                      + QTNAME(player) + "'s blade tears a lethal"
                      + " gash in " + enemy->query_possessive()
                      + " " + kill_loc + "!", });
                    break;
                default:
                    kill_loc = one_of_list( ({ "skull", "rib cage",
                                               "spine" }) );
                    death_messages = ({
                        "With a sickening crunch, the force of"
                      + " your blow crushes "
                      + enemy->query_possessive() + " "
                      + kill_loc + "!",

                        "A sickening crunch is the last thing you"
                      + " hear as the force of the blow crushes"
                      + " your " + kill_loc + " and all goes"
                      + " black!",

                        "With a sickening crunch, the force of"
                      + " the blow crushes "
                      + enemy->query_possessive() + " "
                      + kill_loc + "!", });
                    break;
            }
        }

        effect_desc = ({ "amused",
                         "mostly unphased",
                         "mildly annoyed",
                         "slightly alarmed",
                         "rather alarmed",
                         "hurt",
                         "badly damaged",
                         "quite badly damaged",
                         "terribly wounded",
                         "mortally wounded",
                         "ushered to the brink of death",
                       });

        switch (phurt)
        {
        case 0:
            hit_lvl = 0;
            break;
        case 1:
            hit_lvl = 1;
            break;
        case 2:
            hit_lvl = 2;
            break;
        case 3:
            hit_lvl = 3;
            break;
        case 4..5:
            hit_lvl = 4;
            break;
        case 6..8:
            hit_lvl = 5;
            break;
        case 9..10:
            hit_lvl = 6;
            break;
        case 11..20:
            hit_lvl = 7;
            break;
        case 21..33:
            hit_lvl = 8;
            break;
        case 34..99:
            hit_lvl = 9;
            break;
        default:
            hit_lvl = 10;
    	    break;
    	}

        lethal_attack = (enemy->query_hp() <= 0);

        /* message to the player */
        player->catch_tell("Sensing your opportunity, you lunge with "
          + swing_descs[hit_lvl] + " precision at "
          + enemy->query_the_name(player)
          + ", " + contact_desc + " " + enemy->query_objective()
          + " with your " + wep_desc + "! "
          + ( (lethal_attack) ? death_messages[0] :
            "\n" + enemy->query_The_name(player)
          + " appears " + effect_desc[hit_lvl] + " by your"
          + " attack.") + "\n");
    
        /* message to the enemy */
        enemy->catch_tell(player->query_The_name(enemy)
          + " lunges at you suddenly"
          + " with " + swing_descs[hit_lvl] + " precision, "
          + contact_desc + " you with " + player->query_possessive() 
          + " " + wep_desc + "! "
          + ( (lethal_attack) ? death_messages[1] :
            "The damage leaves you feeling "
          + effect_desc[hit_lvl] + ".") + "\n");
    
        /* message to onlookers */
        player->tell_watcher(QCTNAME(player) + " lunges suddenly"
          + " at " + QTNAME(enemy) + " with " + swing_descs[hit_lvl]
          + " precision, " + contact_desc + " "
          + enemy->query_objective() + " with "
          + player->query_possessive() + " " + wep_desc + "! "
          + ( (lethal_attack) ? death_messages[2] :
            "The latter appears " + effect_desc[hit_lvl] + " by the"
          + " attack.") + "\n", enemy);
    
        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(player);
        }
    }
    else
    {
        
        /* We get here if the attack missed */
    
        /* add some panic to the player */
        player->add_panic(1);
    
        /* message to player */
        player->catch_msg("You misjudge " + QTNAME(enemy) + " and"
          + " your attack goes astray.\n");
    
        /* message to enemy */
        enemy->catch_msg(QCTNAME(player) + " moves in for an attack,"
          + " which you deftly sidestep.\n");
    
        /* message to onlookers */
        player->tell_watcher(QCTNAME(player) + " moves in for an"
          + " attack on " + QTNAME(enemy)+ ", who deftly sidesteps"
          + " the maneuver.\n", enemy);
    }
    
    return;
} /* special_did_hit */


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
    
    /* Does attacker have the skill? */
    if (!(player->query_skill(SS_MERC_TACTICS_SKILL)))
    {
        player->catch_tell("You first must learn the Mercenary"
          + " Tactics skill!\n");
        return 0;
    }
    
    /* If it passes everything, return success. */
    return 1; 
} /* check_valid_action */


/*
 * Function name: apply_costs_to_player
 * Description  : By default, a small fatigue cost is applied
 *                for the special. Other costs can be applied
 *                as well by a masked function.
 * Arguments    : player - player executing the special
 * Returns      : nothing
 */
public void
apply_costs_to_player(object player)
{
    if (player->query_fatigue() > FATIGUE_COST)
    {
        player->add_fatigue(-FATIGUE_COST);
    }
    else
    {
        player->set_fatigue(0);
    	player->heal_hp(-HEALTH_COST);
    	player->catch_msg("The strain of the attack drains you.\n");        
    }
} /* apply_costs_to_player */


/* HOOKS BELOW */


/*
 * Function name: hook_stun_fail
 * Description:   Return the string that will be printed to the player when
 *                he or she is stunned
 * Returns:       The message to print.
 */
public void
hook_stun_fail(object ability)
{
    this_player()->catch_tell("You are too stunned to use your"
      + " Mercenary tactics!\n");
} /* hook_stun_fail */


/*
 * Function name: hook_special_complete
 * Description:   This gets called whenever the special is ready again.
 * Returns:       nothing
 */
public void hook_special_complete()
{
    write("You feel ready to use Mercenary tactics again!\n");
} /* hook_special_complete */


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
    write("The target of your attack seems to have slipped away.\n");    
} /* hook_targets_gone */


/*
 * Function name:        ability_msg
 * Description  :        Write the text that is displayed when the
 *                       prep time begins for the attack
 *
static void 
ability_msg(object actor,mixed * targets,string arg)
{
    object target;
    
    if (sizeof(targets) > 0)
    {
        target = targets[0];
        actor->catch_msg("You begin to size up " + QTNAME(target)
                       + ", looking for an opening.\n");
    }
} /* ability_msg */


/*
 * Function:    hook_attack_object
 * Description: This hook gets called when the special attacks someone.
 *              By checking query_attack, one can see if this is an
 *              initiating attack. Useful for setting up messages
 *              like "X raises his arms and charges in."
 */
public void
hook_attack_object(object ob)
{
    object player;
    
    player = this_player();
    if(!player->query_attack())
    {
        write("Sizing up your foe, you spring into battle!\n");
        ob->catch_tell(
            player->query_The_name(ob) + " springs forward in a"
          + " sudden attack against you!\n");
        tell_room(environment(player), 
            QCTNAME(player) + " springs forward in a sudden"
          + " attack against " + QTNAME(ob) + "!\n",
            ({ player, ob }) );
    }
    else
    {
        ::hook_attack_object(ob);
    }    
} /* hook_attack_object */
