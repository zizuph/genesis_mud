/*
 * Eldoral Standard Zombie
 *
 * Undead Zombies for the Eldoral Tunnel Caves and Underground.
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
    set_race_name("zombie");
    set_short(implode(query_adjs(), " ") + " zombie");
    set_long("This " + query_short() + " is an animated corpse of a "
        + "formerly living creature. Imbued with the barest semblance "
        + "of life, this shambling monster seemingly has no aim in "
        + "unlife other than terrorizing the living by obeying its "
        + "creator's commands. You wonder WHO the creator might be!\n");

    set_act_time(30);
	add_act("emote shambles along, occasionally dropping decayed flesh.");
	add_act("emote moans in a chilling gurgle.");

    set_cact_time(15);
    add_cact("emote turns its head slightly and glares balefully.");
    add_cact("emote seems unaffected by his wounds.");
    add_cact("emote reaches out with both claws.");

    add_prop(LIVE_I_NO_CORPSE, 0); // zombies have real corpses.
    
    default_config_undead(120);
    
    set_exp_factor(105); // pretty hard hitting special
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
    MONEY_MAKE_SC(random(2)+2)->move(npc);

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
        die_message = QCTNAME(this_object()) + " makes one last dying "
            + "grasp at those around with " + this_object()->query_possessive()
            + " claws before collapsing to the ground motionless.\n";
        break;
    
    case 2:
    default:
        die_message = QCTNAME(this_object()) + " shakes violently "
            + "as the corrupt powers that inhabit " 
            + this_object()->query_possessive() + " body depart "
            + "for good.\n";
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
    
    if (random(4))
        return 0;      /* 25% chance of special attack. */

    mixed hitresult;
    if (!(hitresult = do_stat_based_attack(this_object(), enemy, W_SLASH)))
    {
        // Could not attack the target, or they evaded.
        return 1;
    }

    tar = QCTNAME(this_object()) + " reaches out with its decayed "
        + "fleshy hands towards you and ";
    wat = QCTNAME(this_object()) + " reaches out with its decayed "
        + "fleshy hands towards " + QTNAME(enemy) + " and ";

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
            tar += "slashes you, breaking through your skin to create "
                + "an open wound.\n";
            wat += "slashes " + enemy->query_objective() + ", breaking "
                + "through the skin to create an open wound.\n";
            break;
        
        case 11..20:
            tar += "mauls you with one hand, then brings the other "
                + "hand around to strike at you again.\n";
            wat += "mauls " + enemy->query_objective() + " with one "
                + "hand, then brings the other hand around to strike "
                + "at " + enemy->query_objective() + " again.\n";
            break;
        
        case 21..40:
            tar += "grabs you by the shoulder, pulls you towards "
                + this_object()->query_objective() + " with great strength "
                + "and viciously bites you.\n";
            wat += "grabs " + enemy->query_objective() + " by the shoulder, "
                + "pulls " + enemy->query_objective() + " with great strength "
                + "and viciously bites " + QTNAME(enemy) + ".\n";
            break;
        
        default:
            tar += "brings it quickly upwards as " + this_object()->query_pronoun()
                + " rips apart your chest, opening up a large wound "
                + "from the deadly attack.\n";
            wat += "brings it quickly upwards as " + this_object()->query_pronoun()
                + " rips apart " + enemy->query_possessive() + " chest, opening "
                + "up a large wound from the deadly attack.\n";
            break;
        }
    }
    
    enemy->catch_msg(tar);
    enemy->tell_watcher(wat, enemy);
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }
        
    return 1;
}
