#pragma strict_type

inherit "/d/Genesis/specials/std/evade_obj_base";

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

#include "../guild.h"

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{
    set_name("kender_dodge");
    add_name( ({"kender_evade_object" }) );
    set_short("hidden kender magic evade object");    
    set_long("This is the secret and extremely hidden kender evade object.\n");
    
    setuid();
    seteuid(getuid());
    set_evade_stats( ({ SKILL_WEIGHT, 65, TS_DEX, SKILL_WEIGHT, 25, TS_WIS,
                        SKILL_WEIGHT, 10, TS_CON }) );
    set_evade_skills( SS_CTACT_SPECIAL );
    set_evade_combat_aid(95);
}

public int
is_kender_dodge()
{
    return 1;
}

/*
 * Function     : query_evade_valid
 * Description  : Validation function to see whether this evade object is
 *                valid in the current situation
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : 0/1 - invalid/valid
 */
public int
query_evade_valid(object player, object attacker, int attack_id)
{
    object *onslaught;
    
    onslaught = filter(all_inventory(environment(player)),
                &operator(==)(,player) @ &->query_attack());
    
    if (!sizeof(onslaught))
        return 0;
    
    return 1;
}


/*
 * Function name: query_combat_aid_modifier
 * Description  : Calculates the percentage of the maximum
 *                combat aid that applies to the current situation
 * Arguments    : player - player executing special
 * Returns      : number between 1 and 100
 */
public int 
query_combat_aid_modifier(object player)
{
    // Combat aid is the maximum provided by a special
    // The modifier is used in situations where the player
    // should not get the maximum combat aid.
    // Value should be between 1 and 100
    
    object *shields, *hoopaks;
    int     arms, reduction = 100;
    
    shields = filter(player->query_armour(-1), &operator(==)(, A_SHIELD) @
              &->query_at());

    arms = sizeof(shields) * sizeof(shields);
    
    if (!player->find_hoopak())
        arms += 4;
    
    arms = arms * 5; // 5 cost for a single shield,
                     //20 cost for dual shields,
                     //20 cost for no hoopak,
	
    reduction -= arms;
	
    if (SLING_ABILITY->query_ability_active(player))
        reduction = reduction / 2; // 47,5 combat aid if no shield is worn
    
    return reduction;
}

/*
 * Function     : attack_blocked
 * Description  : Function to display messages that the attack was
 *                blocked.
 * Arguments    : player    - player who is being attacked
 *                attacker  - the person doing the attacking
 *                attack_id - attack id location
 * Returns      : nothing
 */
public void
attack_blocked(object player, object attacker, int attack_id)
{
    string  msg1, msg2,
            msg3;
    int     gBrief,
            hoopak;
            
    gBrief  = player->query_dodge_brief();
    hoopak  = player->find_hoopak();
    
    if (!SLING_ABILITY->query_ability_active(player) &&
        attacker->query_kender_rage()) // Increases taunt timer
    {
        attacker->catch_msg("Rage is now higher!...\n");
        if (!random(attacker->query_kender_rage()))
            attacker->add_kender_rage(3, player, 1);
    }
    
    if (gBrief)
    {
        switch(random(4))
        {
        case 0:
            msg1 = "You flip away from " +
                attacker->query_the_possessive_name(player) + " attack.\n";
            msg2 = player->query_The_name(attacker) + " flips away from " +
                "your attack.\n";
            msg3 = QCTNAME(player) + " flips away from " + QTPNAME(attacker) +
                " attack.\n";
            break;
        case 1:
            msg1 = "You spin out of the way as " +
                attacker->query_the_name(player) + " lunges.\n";
            msg2 = player->query_The_name(attacker) + " spins out of " +
                "the way as you lunge.\n";
            msg3 = QCTNAME(player) + " spins out of the way as " +
                QTNAME(attacker) + " lunges.\n";
            break;
        case 2:
            msg1 = "You leap high into the air to evade a low attack by " +
                attacker->query_the_name(player) + ".\n";
            msg2 = player->query_The_name(attacker) + " leaps high into " +
                "the air to evade your low attack.\n";
            msg3 = QCTNAME(player) + " leaps high into the air to evade " +
                "a low attack by " + QTNAME(attacker) + ".\n";
            break;
        case 3:
            msg1 = "You drop into a backwards roll to avoid an attack " +
                "by " + attacker->query_the_name(player) + ".\n";
            msg2 = player->query_The_name(attacker) + " drops into a " +
                "backwards roll to avoid your attack.\n";
            msg3 = QCTNAME(player) + " drops into a backwards roll to " +
                "avoid " + QTPNAME(attacker) + " attack.\n";
        }
    }
    /* Messages if kender has no hoopak and no brief. */
    else if (!hoopak)
    {
        switch(random(7))
        {
        case 0:
            msg1 = "With amazing grace, you do a backwards flip, avoiding " +
                   attacker->query_the_possessive_name(player) + " attack.\n";
            msg2 = "With amazing grace, " + player->query_the_name(attacker) +
                   " does a backward flip, avoiding your attack.\n";
            msg3 = "With amazing grace, " + QTNAME(player) +
                   " does a backward flip, avoiding " + QTPNAME(attacker) +
                   " attack.\n";
            break;
        case 1:
            msg1 = "You see " + attacker->query_the_name(player) +
                   " ready to aim a blow at you, and fall forward into a " +
                   "roll. You regain your feet quickly, turning to face " +
                   "your enemy once again.\n";
            msg2 = player->query_The_name(attacker) + " sees you getting " +
                   "ready to aim a blow at " + player->query_objective() +
                   ", and falls forward into a roll. " +
                   capitalize(player->query_pronoun()) + " regains " +
                   player->query_possessive() + " feet quickly, turning " +
                   "to face you once again.\n";
            msg3 = QCTNAME(player) + " sees " + QTNAME(attacker) + 
                   " getting ready to aim a blow at " + 
                   player->query_objective() + ", and falls forward " +
                   "into a roll. " + capitalize(player->query_pronoun()) + 
                   " regains " + player->query_possessive() + " feet " +
                   "quickly, turning to face " + player->query_possessive() + 
                   " enemy once again.\n";
            break;
        case 2:
            msg1 = "You spin into " + 
                   attacker->query_the_possessive_name(player) +
                   " attack, avoiding " + attacker->query_possessive() +
                   " blow. You grin mischievously at " +
                   attacker->query_the_name(player) + ".\n";
            msg2 = player->query_The_name(attacker) + " spins into your " +
                   "attack, avoiding your blow. " +
                   capitalize(player->query_pronoun()) + " grins with a " +
                   "mischievous look.\n";
            msg3 = QCTNAME(player) + " spins into " + QTPNAME(attacker) +
                   " attack, avoiding " + attacker->query_possessive() + 
                   " blow. " + capitalize(player->query_pronoun()) +
                   " grins at " + QTNAME(attacker) + " with a mischievous " +
                   "look.\n";
            break;
        case 3:
            msg1 = "With a powerful lunge, you flip over " +
                   attacker->query_the_name(player) + ", landing behind " +
                   attacker->query_pronoun() + " and avoiding " +
                   attacker->query_possessive() + " blow. " +
                   attacker->query_The_name(player) + " swivels around to " +
                   "face you again.\n";
            msg2 = "With a powerful lunge, " +
                   player->query_the_name(attacker) + " flips over you, " +
                   "landing behind you and avoiding your blow. You swivel " +
                   "around to face " + player->query_the_name(attacker) +
                   " again.\n";
            msg3 = "With a powerful lunge, " + QTNAME(player) + " flips " +
                   "over " + QTNAME(attacker) + ", landing behind " +
                   attacker->query_objective() + " and avoiding " +
                   attacker->query_possessive() + " blow. " + QCTNAME(attacker) +
                   " swivels around to face " + QTNAME(player) + 
                   " again.\n";
            break;
        case 4:
            msg1 = "Pushing off hard, you leap high into the air, avoiding " +
                   "a low attack by " + attacker->query_the_name(player) +
                   ". You land as gracefully as a cat, ready for the next " +
                   "attack.\n";
            msg2 = "Pushing off hard, " + player->query_the_name(attacker) +
                   " leaps high into the air, avoiding your low attack. " +
                   capitalize(player->query_pronoun()) + " lands as " +
                   "gracefully as a cat, ready for the next attack.\n";
            msg3 = "Pushing off hard, " + QTNAME(player) + " leaps high " +
                   "into the air, avoiding a low attack by " + QTNAME(attacker) +
                   ". " + capitalize(player->query_pronoun()) + " lands " +
                   "as gracefully as a cat, ready for the next attack.\n";
            break;
        case 5:
            msg1 = "Seeing an attack flying towards your head, you quickly " +
                   "drop into a backwards roll to evade it. You snap to " +
                   "your feet as the battle continues.\n";
            msg2 = "Seeing your attack aimed at " +
                   player->query_possessive() + " head, " +
                   player->query_the_name(attacker) + " drops into a " +
                   "backwards roll to evade it. " +
                   capitalize(player->query_pronoun()) + " snaps to " +
                   player->query_possessive() + " feet as the battle " +
                   "continues.\n";
            msg3 = "Seeing an attack flying towards " +
                   player->query_possessive() +
                   " head, " + QTNAME(player) + " drops into a " +
                   "backwards roll to evade it. " +
                   capitalize(player->query_pronoun()) + " snaps to " +
                   player->query_possessive() + " feet as the battle " +
                   "continues.\n";
            break;
        case 6:
            msg1 = "You see " + attacker->query_the_name(player) +
                   " driving an attack at you, and you push off into a " +
                   "back handspring. Enjoying yourself immensely, you do a " +
                   "few more back handsprings, then remember that you were " +
                   "in battle. You return swiftly with a powerful front " +
                   "handspring.\n";
            msg2 = player->query_The_name(attacker) + " sees you driving " +
                   "an attack at " + player->query_objective() + ", and " +
                   "pushes off into a back handspring. Surprisingly, " +
                   player->query_the_name(attacker) + " does a few more " +
                   "back handsprings until " + player->query_pronoun() +
                   " remembers what " + player->query_pronoun() + " was " +
                   "doing. " + capitalize(player->query_pronoun()) +
                   " returns swiftly with a powerful front handspring.\n";
            msg3 = QCTNAME(player) + " sees " + QTNAME(attacker) + 
                   " driving an attack at " + player->query_objective() +
                   ", and pushes off into a back handspring. Surprisingly, " +
                   QTNAME(player) + " does a few more back handsprings " +
                   "until " + player->query_pronoun() + " remembers " +
                   "what " + player->query_pronoun() + " was doing. " +
                   capitalize(player->query_pronoun()) + " returns " +
                   "swiftly with a powerful front handspring.\n";
            break;
        }
    }
    else
    {
        switch(random(7))
        {
        case 0:
            msg1 = "With amazing grace, you push yourself into a backwards " +
                "flip with your hoopak, avoiding " +
                attacker->query_the_possessive_name(player) + " attack.\n";
            msg2 = "With amazing grace, " + 
                player->query_the_name(attacker) + " pushes " + 
                player->query_objective() + "self into a " +
                "backwards flip with " + player->query_possessive() +
                " hoopak, avoiding your attack.\n";
            msg3 = "With amazing grace, " + QTNAME(player) +
                " pushes " + player->query_objective() + "self into a " +
                "backwards flip, avoiding " + QTPNAME(attacker) + " attack.\n";
            break;
        case 1:
            msg1 = "You see " + attacker->query_the_name(player) +
                " ready to aim a blow at you, and fall forward into a " +
                "roll. You regain your feet quickly, holding your hoopak " +
                "in front of you protectively.\n";
            msg2 = player->query_The_name(attacker) + " sees you getting " +
                "ready to aim a blow at " + player->query_objective() +
                ", and falls forward into a roll. " +
                capitalize(player->query_pronoun()) + " regains " +
                player->query_possessive() + " feet quickly, holding " +
                player->query_possessive() + " hoopak in front of " +
                player->query_objective() + "self protectively.\n";
            msg3 = QCTNAME(player) + " sees " + QTNAME(attacker) + 
                " getting ready to aim a blow at " + 
                player->query_objective() + ", and falls forward " +
                "into a roll. " + capitalize(player->query_pronoun()) + 
                " regains " + player->query_possessive() + " feet " +
                "quickly, holding " + player->query_possessive() + 
                " hoopak in front of " + player->query_objective() + 
                "self protectively.\n";
            break;
        case 2:
            msg1 = "You spin into " +
                attacker->query_the_possessive_name(player) + " attack, " +
                "using your hoopak as a pivotal point, avoiding " +
                attacker->query_possessive() + " blow. You grin mischievously " +
                "at " + attacker->query_the_name(player) + ".\n";
            msg2 = player->query_The_name(attacker) + " spins into your " +
                "attack, using " + player->query_possessive() +
                " hoopak as a pivotal point, avoiding your blow. " +
                capitalize(player->query_pronoun()) + " grins with a " +
                "mischievous look.\n";
            msg3 = QCTNAME(player) + " spins into " + QTPNAME(attacker) +
                " attack, using " + player->query_possessive() +
                " hoopak as a pivotal point, avoiding " + QPNAME(attacker) +
                " blow. " + capitalize(player->query_pronoun()) +
                " grins at " + QTNAME(attacker) + " with a mischievous look.\n";
            break;
        case 3:
            msg1 = "With a powerful lunge, you flip over " +
                   attacker->query_the_name(player) + ". Using your " +
                   "hoopak to balance yourself, you land behind " +
                   attacker->query_objective() + " and avoid " +
                   attacker->query_possessive() + " blow. " +
                   attacker->query_The_name(player) + " swivels around to " +
                   "face you again.\n";
            msg2 = "With a powerful lunge, " +
                   player->query_the_name(attacker) + " flips over you. " +
                   "Using " + player->query_possessive() + " hoopak for " +
                   "balance, " + player->query_pronoun() + " lands " +
                   "behind you and avoids your blow. You swivel around to " +
                   "face " + player->query_the_name(attacker) + " again.\n";
            msg3 = "With a powerful lunge, " + QTNAME(player) + " flips " +
                   "over " + QTNAME(attacker) + ". Using " +
                   player->query_possessive() + " hoopak for balance, " +
                   player->query_pronoun() + " lands behind " +
                   attacker->query_objective() + " and avoids " +
                   attacker->query_possessive() + " blow. " + QCTNAME(attacker) +
                   " swivels around to face " + QTNAME(player) + 
                   " again.\n";
            break;
        case 4:
            msg1 = "Using your hoopak, you push off hard and leap high " +
                   "into the air, avoiding a low attack by " +
                   attacker->query_the_name(player) + ". You land as " +
                   "gracefully as a cat, ready for the next attack.\n";
            msg2 = "Using " + player->query_possessive() + " hoopak, " +
                   player->query_the_name(attacker) + " pushes off hard "  +
                   "and leaps high into the air, avoiding your low attack. " +
                   capitalize(player->query_pronoun()) + " lands as " +
                   "gracefully as a cat, ready for the next attack.\n";
            msg3 = "Using " + player->query_possessive() + " hoopak, " +
                   QTNAME(player) + " pushes off hard and leaps high " +
                   "into the air, avoiding a low attack by " + QTNAME(attacker) +
                   capitalize(player->query_pronoun()) + " lands as " +
                   "gracefully as a cat, ready for the next attack.\n";
            break;
        case 5:
            msg1 = "Seeing an attack flying towards your head, you quickly " +
                   "drop into a backwards roll to evade it. You snap to " +
                   "your feet, hoopak held ready, as the battle continues.\n";
            msg2 = "Seeing your attack aimed at " +
                   player->query_possessive() + " head, " +
                   player->query_the_name(attacker) + " drops into a " +
                   "backwards roll to evade it. " +
                   capitalize(player->query_pronoun()) + " snaps to " +
                   player->query_possessive() + " feet, hoopak held " +
                   "ready, as the battle continues.\n";
            msg3 = "Seeing an attack flying towards " +
                   player->query_possessive() + " head, " +
                   QTNAME(player) + " drops into a backwards roll to " +
                   "evade it. " + capitalize(player->query_pronoun()) +
                   " snaps to " + player->query_possessive() + " feet, " +
                   "hoopak held ready as the battle continues.\n";
            break;
        case 6:
            msg1 = "You see " + attacker->query_the_name(player) +
                   " driving an attack at you, and you push off into a back " +
                   "handspring. Enjoying yourself immensely, you do a few " +
                   "more back handsprings, twirl your hoopak around, then " +
                   "remember that you were in battle. You return swiftly " +
                   "with a powerful front handspring.\n";
            msg2 = player->query_The_name(attacker) + " sees you driving " +
                   "an attack at " + player->query_objective() + ", and " +
                   "pushes off into a back handspring. Surprisingly, " +
                   player->query_the_name(attacker) + " does a few more " +
                   "back handsprings and twirls " +
                   player->query_possessive() + " hoopak around until " +
                   player->query_pronoun() + " remembers what " +
                   player->query_pronoun() + " was doing. " +
                   capitalize(player->query_pronoun()) + " returns " +
                   "swiftly with a powerful front handspring.\n";
            msg3 = QCTNAME(player) + " sees " + QTNAME(attacker) + 
                   " driving an attack at " + player->query_objective() + 
                   ", " + "and pushes off into a back handspring. " +
                   "Surprisingly, " + QTNAME(player) + " does a few " +
                   "more back handsprings and twirls " + 
                   player->query_possessive() +
                   " hoopak around until " + player->query_pronoun() +
                   " remembers what " + player->query_pronoun() + " was " +
                   "doing. " + capitalize(player->query_pronoun()) +
                   " returns swiftly with a powerful front handspring.\n";
            break;
        }
    }
    
    player->catch_msg(msg1);
    attacker->catch_msg(msg2);
    player->tell_watcher(msg3, attacker, ({ player, attacker }));
}

