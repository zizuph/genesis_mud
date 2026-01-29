inherit "/d/Krynn/common/objects/dragon_fear";
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
    return !interactive(who);
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
    if (victim->query_race_name() == "kender") {
        return;
    }


    /* Remove the applied effects */
    victim->set_skill_extra(SS_DEFENCE, 
        victim->query_skill_extra(SS_DEFENCE) - defence_penalty);

    if (!strength)
    {
        defence_penalty = 0;
        return;
    }

    /*Tell them how they're feeling*/
    if (!weakened_message) {
        victim->catch_msg("You feel the dragonfear weakening your "+
            "ability to defend yourself.\n");
        weakened_message = 1;
    }
    
    dis_stat = ((2 * victim->query_stat(SS_DIS)) + victim->query_stat(SS_WIS))
/ 3;
    dis_stat += victim->query_dragonfear_bonus();
    dis_stat += 3 * victim->query_knight_level();
    
    if (victim->query_dragonarmy_occ_member())
        dis_stat += victim->query_stat(SS_OCCUP) / 4;
    if (victim->query_pot_member())
        dis_stat += victim->query_priest_sublevel() * 8;
    if (victim->query_prop(NPC_I_NO_FEAR))
        dis_stat *= 2;

    if (dis_stat < 1) //prevent division by zero runtime Milan 22.6.2004
        dis_stat = 1;
    
    /*How much panic to add? 30 max. */
    int panic_penalty = MIN(4 * (random(strength) + random(strength) + 
                random(strength)) /dis_stat, 30);
    
    /* How much defence to subtract? 40 max. */
    defence_penalty = -MIN((40 * strength) / dis_stat, 40);

    /* Don't reduce to less than 0 */
    if (defence_penalty * -1 > victim->query_skill(SS_DEFENCE)) {
        defence_penalty = victim->query_skill(SS_DEFENCE) * -1;
    }
    
    /* Add the effects */
    victim->set_skill_extra(SS_DEFENCE, 
        victim->query_skill_extra(SS_DEFENCE) + defence_penalty);
    victim->add_panic(panic_penalty);
}

