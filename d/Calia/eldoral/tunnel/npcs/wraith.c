/*
 * Eldoral Standard Wraith
 *
 * Undead Wraiths for the Eldoral Tunnel Caves and Underground.
 *
 * Created by Petros, November 2008
 */


#include "defs.h"
inherit ELDORAL_UNDEAD_CREATURE;

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <stdproperties.h>
#include <formulas.h>
#include <composite.h>
#include <poison_types.h>

// Global Variables

/*
 * Function:    create_undead_creature
 * Description: Default configure function to mask for undeads
 *              Define this in your own undead to override the standard
 *              stuff set here.
 * Arguments:   none
 * Returns:     nothing
 */
public void
create_undead_creature()
{
    set_race_name("wraith");
    set_short(implode(query_adjs(), " ") + " wraith");
    set_long("You see before you the " + query_short() + ", a restless "
        + "apparition lurking in the shadows. Its form shifts in and out of the "
        + "material world, and the shadowy wisps of its body distract "
        + "you from the vicious claws it possesses. Its eyes are lit up "
        + "like small red fires in the night as it thirsts "
        + "longingly for souls.\n");

    set_act_time(30);
	add_act("emote stares at you in pure hatred.");
	add_act("emote seems to disappear for a moment and the return.");

    default_config_undead(160);
    
    setuid();
    seteuid(getuid());
    
    object evade = clone_object(TUN_OBJECTS + "wraith_evade");
    if (objectp(evade))
    {
        evade->move(this_object(), 1);
        evade->start();
    }
        
    set_exp_factor(125); // extra 25% for strength drain, evade (10%)
}

/*
 * Function:    add_treasure
 * Description: Default function to add treasure to the undead. The base
 *              undead simply has a gem on him. Mask this function to set
 *              whatever you'd like the undead to drop. This gets called
 *              by default in default_config_undead.
 * Arguments:   none
 * Returns:     nothing
 */
public void
add_treasure(object npc)
{
    ::add_treasure(npc);
    MONEY_MAKE_GC(random(5)+2)->move(npc);
}

public void
do_die(object killer)
{
    string die_message;
    
    switch (random(3))
    {
    case 0:
        die_message = QCTNAME(this_object()) + " dissipates as its "
            + "spirit is freed from its corrupt state.\n";
        break;
    
    case 1:
        die_message = QCTNAME(this_object()) + " falls to the ground "
            + "and explodes into dark purple light, causing you to "
            + "avert your eyes. You look back and nothing remains "
            + "of the " + query_short() + ".\n";
        break;
    
    case 2:
    default:
        die_message = QCTNAME(this_object()) + " whispers dark curses "
            + "towards those around it as it dissipates.\n";
        break;
    }
    
    tell_room(environment(this_object()), die_message);
    ::do_die(killer);

}

/*
 * Function name: special_attack
 * Description  : Special attack for this npc.
 * Arguments    : enemy - Object pointer to the living to attack.
 * Returns      : 1 - Made attack, no further attacks this round.
 *                0 - No special attack, continue normal combat round.
 */
public int
special_attack(object enemy)
{
    string tar, wat;
    int drain_strength;
    
    if (random(4))
        return 0;      /* 25% chance of special attack. */

    mixed hitresult;
    if (!(hitresult = do_stat_based_attack(this_object(), enemy, W_SLASH)))
    {
        // Could not attack the target, or they evaded.
        return 1;
    }

    tar = QCTNAME(this_object()) + " glides forward, reaches "
        + "towards you with its vicious claws and ";
    wat = QCTNAME(this_object()) + " glides forward, reaches "
        + "towards " + QTNAME(enemy) + " with its vicious claws "
        + "and ";

    drain_strength = 0;
    if (hitresult[0] < 0)
    {
        tar += "just barely misses you.\n";
        wat += "just barely misses " + enemy->query_objective() + ".\n";
    }
    else
    {        
        switch (hitresult[0])
        {
        case 0..5:
            tar += "barely makes a scratch on you.\n";
            wat += "barely makes a scratch on " + enemy->query_objective() 
                + ".\n";
            break;
        
        case 6..10:
            tar += "slashes open a painful wound on your body.\n";
            wat += "slashes open a painful would on " 
                + enemy->query_possessive() + " body.\n";
            break;
        
        case 11..20:
            tar += "touches you gently, causing a lot of pain as it sends "
                + "waves of corrupt necrotic energy into your being.\n";
            wat += "touches " + QTNAME(enemy) + " gently, causing a lot "
                + "of pain as it sends waves of corrupt necrotic energy "
                + "into " + enemy->query_possessive() + " body.\n";
            drain_strength = 1; // 20 seconds
            break;
        
        case 21..40:
            tar += "grabs onto you briefly, delivering a tremendous "
                + "level of pain to your body as a current of necrotic "
                + "energy fills you.\n";
            wat += "grabs onto " + enemy->query_objective() + " briefly, "
                + "delivering a tremendous level of pain to " 
                + enemy->query_possessive() + " body as as current of "
                + "necrotic energy fills " + enemy->query_objective() 
                + ".\n";
            drain_strength = 2; // 40 seconds
            break;
        
        default:
            tar += "clings to you tightly as it drains your life out of "
                + "your body. You feel such an enormous amount of pain "
                + "that you almost pass out before it finally lets you "
                + "go.\n";
            wat += "clings to " + QTNAME(enemy) + " tightly as it drains "
                + enemy->query_possessive() + " life from "
                + enemy->query_possessive() + " body. " + QCTNAME(enemy)
                + " looks like " + enemy->query_pronoun() + " is in such "
                + "enormous amount of pain that " + enemy->query_pronoun()
                + " almost passes out before it finally lets "
                + enemy->query_objective() + " go.\n";
            drain_strength = 3; // 60 seconds
            break;
        }
    }
    
    enemy->catch_msg(tar);
    enemy->tell_watcher(wat, enemy);
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }
    else if (drain_strength)
    {
        enemy->add_tmp_stat(SS_STR, -10, drain_strength);
        enemy->catch_tell("The wraith's touch causes your muscles to "
            + "become like lead, and your feel a bit more sluggish.\n");
    }
    
    return 1;
}
