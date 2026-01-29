/*
 * Dragon Fear Object for Dragonarmy dragons
 *
 * Created by Petros, March 2009
 */
 
inherit "/d/Krynn/common/objects/dragon_fear_new";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

private int weakened_message = 0;

/*
 * Disable command filtering.
 */
public int
check_apply_command_filter(object who)
{
    return 0;
}

/*
 * Dragonarmy Dragonfear causes slightly different effects.
 *
 * Apply Effects
 *
 * Removes all existing effects and applies the new ones.
 */
static void
apply_effect(int strength)
{    
    /*Kender are immune.  Standard dragonfear still calls */
    /*this for kender*/
    if (victim->query_race_name() == "kender") 
    {
        return;
    }

    /* Remove the applied effects */
    victim->set_skill_extra(SS_DEFENCE, 
        victim->query_skill_extra(SS_DEFENCE) - defence_penalty);
    victim->set_skill_extra(SS_PARRY, 
        victim->query_skill_extra(SS_PARRY) - parry_penalty);

    if (!strength)
    {
        defence_penalty = 0;
        parry_penalty = 0;
        return;
    }

    /*Tell them how they're feeling*/
    if (!weakened_message) {
        victim->catch_msg("You feel the dragonfear weakening your "+
            "ability to defend yourself.\n");
        weakened_message = 1;
    }
    
    int victim_skill = victim->query_skill(SS_DEFENCE);    
    defence_penalty = 10;
    /* Don't reduce to less than 0 */
    defence_penalty = defence_penalty + min(victim_skill - defence_penalty, 0);
    defence_penalty = -defence_penalty; // penalties are negative
    
    victim_skill = victim->query_skill(SS_PARRY);    
    parry_penalty = 10;
    /* Don't reduce to less than 0 */
    parry_penalty = parry_penalty + min(victim_skill - parry_penalty, 0);
    parry_penalty = -parry_penalty; // penalties are negative
    
    /* Add the effects */
    victim->set_skill_extra(SS_DEFENCE, 
        victim->query_skill_extra(SS_DEFENCE) + defence_penalty);
    victim->set_skill_extra(SS_PARRY, 
        victim->query_skill_extra(SS_PARRY) + parry_penalty);
}

