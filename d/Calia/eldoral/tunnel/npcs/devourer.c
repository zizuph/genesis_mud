/*
 * Eldoral Standard Devourer
 *
 * Undead Devourer for the Eldoral Tunnel Caves and Underground.
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
    set_race_name("devourer");
    set_short(implode(query_adjs(), " ") + " devourer");
    set_long("This hideous creature is the stomach-wrenching "
        + "monster known as the devourer. It is a cadaverous creature "
        + "that traps the spirit of a living humanoid inside its "
        + "ribcage. You can see the spirit thrashing about, tormented "
        + "and in agony as it is used as unholy fuel for the devourer. "
        + "\n");

    set_act_time(30);
	add_act("emote torments the soul trapped in its rib cage.");
	add_act("emote devours some fleshy leftovers.");

    default_config_undead(150);
    
    set_exp_factor(120); // extra 20% for ability to drain and heal, as 
                         // well as hard hitting special
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
        die_message = QCTNAME(this_object()) + " crumbles to dust "
            + "as it perishes, releasing the tormented spirit. The "
            + "spirit, finally free, gives a look of thanks and "
            + "disappears.\n";
        break;
    
    case 1:
        die_message = QCTNAME(this_object()) + " screams loudly as "
            + "the spirit within its ribcage breaks free. "
            + QCTNAME(this_object()) + " reaches for the released "
            + "spirit, but crumbles to dust before it can recapture "
            + "it.\n";
        break;
    
    case 2:
    default:
        die_message = QCTNAME(this_object()) + " bursts apart in a flare "
            + "of spiritual essence, releasing the trapped spirit within "
            + "and disappearing forever.\n";
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

    tar = QCTNAME(this_object()) + " reaches out towards you "
        + "with its disgusting tendril and ";
    wat = QCTNAME(this_object()) + " reaches out towards " + QTNAME(enemy) 
        + " with its disgusting tendril and ";

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
            tar += "wraps it around you briefly as you feel a bit of "
                + "your life drain away.\n";
            wat += "wraps it around " + enemy->query_objective()
                + " briefly and drains a bit of " + enemy->query_possessive()
                + " life away.\n";
            break;
        
        case 6..10:
            tar += "grabs you with it and you feel it feeding on your "
                + "life energy, your life draining away to energize "
                + QTNAME(this_object()) + ".\n";
            wat += "grabs " + QTNAME(enemy) + " with it and feeds on "
                + enemy->query_possessive() + " life, energizing "
                + QTNAME(this_object()) + ".\n";
            break;
        
        case 11..20:
            tar += "holds onto you tightly while another tendril encircles "
                + "your body. You see your life energy flow like a "
                + "current from your own body to energize "
                + QTNAME(this_object()) + ".\n";
            wat += "holds onto " + QTNAME(enemy) + " tightly while "
                + "another tendril encircles " + enemy->query_possessive()
                + " body. A visible current of life energy flows from "
                + QTNAME(enemy) + " to " + QTNAME(this_object()) + ".\n";
            break;
        
        case 21..40:
            tar += "hits you on the head, while more tendrils encircle "
                + "all your limbs holding you immobile as it sucks the "
                + "life out of you, restoring " + QTNAME(this_object())
                + ".\n";
            wat += "hits " + QTNAME(enemy) + " on the head, while more "
                + "tendrils encircle all " + enemy->query_possessive()
                + " limbs and holds " + enemy->query_objective()
                + " immobile as it sucks the life out of " + QTNAME(enemy)
                + ", restoring " + QTNAME(this_object()) + ".\n";
            break;
        
        default:
            tar += "entangles your legs first before its other tendrils "
                + "wrap themselves around your whole body. It drains "
                + "you almost completely of your life before finally "
                + "letting you go, renewed and refreshed from feeding "
                + "upon you.\n";
            wat += "entangles " + QTPNAME(enemy) + " legs first before "
                + "its other tendrils wrap themselves around "
                + enemy->query_possessive() + " whole body. It drains "
                + enemy->query_objective() + " almost completely of life "
                + "before finally letting go, renewed and refreshed from "
                + "a successful feeding.\n";
            break;
        }
        
        // Restore the hit points of the devourer, up to 75.
        this_object()->heal_hp(min(hitresult[3], 75));
        send_debug_message("eldoral_devourer", "Healing " +
            min(hitresult[3], 75) + " hit points from draining.");
    }
    
    enemy->catch_msg(tar);
    enemy->tell_watcher(wat, enemy);
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }
    
    return 1;
}
