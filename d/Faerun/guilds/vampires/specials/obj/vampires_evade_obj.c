/*
*
*/

#pragma strict_type

inherit "/d/Genesis/specials/std/evade_obj_base";

#include "../../guild.h"
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

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{
    set_name("_vampires_evade_obj");
    add_name( ({"_vampires_evade_obj" }) );
    set_short("hidden vampires evasion object");    
    set_long("This is the secret and extremely hidden vampires evasion object.\n");
    
    setuid();
    seteuid(getuid());
    set_evade_stats( ({ SKILL_WEIGHT, 40, TS_STR, SKILL_WEIGHT, 40, TS_DEX, 
                        SKILL_WEIGHT, 20, TS_WIS }) );
    set_evade_skills( SS_DEFENSE );
    set_evade_combat_aid(38);
}


public int
is_vampires_evade_base_occ()
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
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(player->query_name()) == 1)
    {
        return 1;
    }
    
    return 0;
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

    switch(random(3))
    {
    case 0:
        msg1 = "With your heightened reaction, you easily "
        +"glide away from "+attacker->query_the_possessive_name(player)
        +" attack attempt.\n";
               
        msg2 = player->query_the_name(attacker)
        +" easily glides away from your attempted attack..\n";
               
        msg3 = QCTNAME(player) + " easily glides away from "
        +"the attack attempted by " + QTPNAME(attacker) + ".\n";
        break;
    case 1:
        msg1 = "Amusingly, you see " + player->query_The_name(attacker)
        + " moving into position and you effortlessly side-step the attack.\n";
               
        msg2 = player->query_The_name(attacker)+" has an amused smirk "
        +"on " +attacker->query_possessive()+ " face, effortlessly "
        +"side-stepping your attack.\n";
               
        msg3 = QCTNAME(player) + " seems amused and effortlessly "
        +"side-steps an attack by " + QTPNAME(attacker) + ".\n";
        break;
    case 2:
        msg1 = "Like a tall tree blowing in the wind, you "
        +"lean away from "+attacker->query_the_possessive_name(player)
        +" assault.\n";
               
        msg2 = "Drifting and swaying like a tall tree in "
        +"the wind, "+player->query_the_name(attacker)
        +" avoids your assault.\n";
               
        msg3 = QCTNAME(player) + " avoids "
        +attacker->query_the_possessive_name(player)
        +" assault by leaning away like a tall tree in the wind.\n";
        break;
    }
    
    player->catch_msg(msg1);
    attacker->catch_msg(msg2);
    player->tell_watcher(msg3, attacker, ({ player, attacker }));
}