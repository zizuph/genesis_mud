/*
 * Eldoral Standard Ghoul
 *
 * Undead Ghouls for the Eldoral Tunnel Caves and Underground.
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
public mapping      avail_leftovers = ([
    "heart" : 1,
    "tooth" : 5,
    "intestine" : 2,
    "nail" : 5,
    "eye" : 2,
    "kidney" : 2,
    "rib" : 5,
    "thighbone" : 2,
    "ear" : 2,
    "skull" : 1 
]);
    
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
    set_race_name("ghoul");
    set_short(implode(query_adjs(), " ") + " ghoul");
    set_long("You suddenly realize that you've stumbled upon a ghoul! "
        + "This " + query_short() + " is a ravenous undead creature "
        + "that has an unappeasable hunger for living flesh. It has "
        + "glowing yellow eyes and its many sharp teeth within its "
        + "jaws drip with warm blood.\n");

    set_act_time(30);
	add_act("emote chews on a piece of flesh as blood drips down from "
	    + "its mouth.");
	add_act("emote looks longingly for warm flesh.");

    add_prop(LIVE_I_NO_CORPSE, 0); // ghouls have real corpses.
    
    default_config_undead(130);
    
    set_exp_factor(110); // extra 10% for attack delay
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
    string * leftovers;
    
    ::add_treasure(npc);
    MONEY_MAKE_GC(random(5)+2)->move(npc);

    leftovers = m_indices(avail_leftovers);
    // We select three leftovers
    for (int i = 0; i < 3; ++i)
    {
        string leftover = one_of_list(leftovers);
        npc->add_leftover(LEFTOVER_OBJECT, leftover, 
            random(avail_leftovers[leftover]), 0, 1, 0);
        leftovers -= ({ leftover });
    }
}

public void
do_die(object killer)
{
    string die_message;
    
    switch (random(3))
    {
    case 0:
        die_message = QCTNAME(this_object()) + " makes a grotesque "
            + "gurgling noise as " + this_object()->query_pronoun()
            + " slumps to the floor.\n";
        break;
    
    case 1:
        die_message = QCTNAME(this_object()) + " makes one last attempt "
            + "to claw at warm flesh before the corrupt energy that "
            + "inhabited its body departs. It slumps to the ground, "
            + "lifeless.\n";
        break;
    
    case 2:
    default:
        die_message = QCTNAME(this_object()) + " looks directly at you "
            + "and you see its yellow eyes grow dim. It makes a most "
            + "vile sound before finally succumbing to true death.\n";
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
    int add_delay;
    
    if (random(4))
        return 0;      /* 25% chance of special attack. */

    mixed hitresult;
    if (!(hitresult = do_stat_based_attack(this_object(), enemy, W_SLASH)))
    {
        // Could not attack the target, or they evaded.
        return 1;
    }

    add_delay = 0;
    tar = QCTNAME(this_object()) + " lunges at you with its claws "
        + "and ";
    wat = QCTNAME(this_object()) + " lunges at " + QTNAME(enemy)
        + " with its claws and ";

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
            tar += "slashes you, but barely misses you as it tries to "
                + "bite you.\n";
            wat += "slashes " + enemy->query_objective() + ", but barely "
                + "misses " + QTNAME(enemy) + " as it tries to bite "
                + enemy->query_objective() + ".\n";
            break;
        
        case 11..20:
            tar += "mauls you with one claw, then brings the other "
                + "claw around to strike at you again. It then comes "
                + "close and makes a scratch at it bites you.\n";
            wat += "mauls " + enemy->query_objective() + " with one "
                + "claw, then brings the other hand around to strike "
                + "at " + enemy->query_objective() + " again. It then "
                + "comes close and makes a scratch as it bites "
                + QTNAME(enemy) + ".\n";
            add_delay = 1;
            break;
        
        case 21..40:
            tar += "grabs you by the shoulder, pulls you towards "
                + this_object()->query_objective() + " with great strength "
                + "and viciously bites you.\n";
            wat += "grabs " + enemy->query_objective() + " by the shoulder, "
                + "pulls " + enemy->query_objective() + " with great strength "
                + "and viciously bites " + QTNAME(enemy) + ".\n";
            add_delay = 1;
            break;
        
        default:
            tar += "rips apart your chest with dual swipes. As you slump "
                + "over from the wound, it bites you voraciously on the "
                + "neck.\n";
            wat += "rips apart " + enemy->query_possessive() + " chest with "
                + "dual swipes of its claws. As " + QTNAME(enemy) + " slumps "
                + "over from the wound, " + QTNAME(this_object()) + " bites "
                + enemy->query_objective() + " voraciously on the neck.\n";
            add_delay = 1;
            break;
        }
    }
    
    enemy->catch_msg(tar);
    enemy->tell_watcher(wat, enemy);
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }
        
    if (add_delay)
    {
        tar += "You feel " + QTPNAME(this_object()) + " saliva enter your "
            + "bloodstream and feel sluggish as it takes effect.\n";
        enemy->add_attack_delay(3, 1);
    }
    
    return 1;
}
