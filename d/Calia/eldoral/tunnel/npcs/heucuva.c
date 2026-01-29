
/*
 * heucuva.c
 *
 * An undead Heucuva for the Undead Tunnels near
 * Eldoral
 *
 * Copyright (C): Jaacar (Mike Phipps), October 13th, 2003
 *
 * - Removed obsolete tell_watcher function (Petros)
 * - Rewrote to use the new standard eldoral undead base (Petros)
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
#include "/d/Calia/sys/map.h"

#define A_LEFT_HAND  0
#define A_RIGHT_HAND 1

#define H_HEAD 0
#define H_BODY 1
#define H_ARMS 2
#define H_LEGS 3

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
    set_race_name("heucuva");
    set_short("robed heucuva");
    set_adj(({"robed"}));
    set_long("This is an undead spirit similar in appearance to a "+
        "skeleton, but appears to be much more dangerous. It appears "+
        "to be a humanoid skeleton of normal size wearing a tattered robe. "+
        "It is the restless spirit of a monastic priest who was less than "+
        "faithful to their holy vows. As punishment, it roams the realms "+
        "as undead.\n");

    set_alignment(-1100);
    add_prop(OBJ_I_RES_MAGIC, 10);
    set_aggressive(1);

    default_config_undead(115);

    // NPC is aggressive, has special attack, a poison, and also 
    // attacks in a group.
    set_exp_factor(120);    
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
    MONEY_MAKE_GC(random(2)+2)->move(npc);
}

/*
 * Function:    set_attacks_and_hitlocs
 * Description: Default function for setting all the attacks and hitlocs
 *              for the undead creature. Mask this to override and set
 *              your own.
 * Arguments:   none
 * Returns:     nothing
 */
public void
set_undead_attacks_and_hitlocs()
{
    set_attack_unarmed(A_LEFT_HAND, 40, 40, W_SLASH, 50, "bony left hand");
    set_attack_unarmed(A_RIGHT_HAND, 40, 40, W_SLASH, 50, "bony right hand");

    set_hitloc_unarmed(H_HEAD, ({40, 40, 35, 0}), 15, "head");
    set_hitloc_unarmed(H_BODY, ({40, 40, 35, 0}), 35, "body");
    set_hitloc_unarmed(H_ARMS, ({40, 40, 35, 0}), 25, "arms");
    set_hitloc_unarmed(H_LEGS, ({40, 40, 35, 0}), 25, "legs");
}

void
attacked_by(object attacker)
{
    object * heucuvas;
    
    ::attacked_by(attacker);
    
    heucuvas = FIND_STR_IN_OBJECT("heucuvas", environment());
    heucuvas -= ({ this_object(), attacker });
    
    if (sizeof(heucuvas))
    {
        MAP_ATTACK(heucuvas, attacker);
    }
}

public void
do_die(object killer)
{
    tell_room(environment(this_object()), "There is a bright flash of "
        + "light as the " + QTNAME(this_object()) + " implodes upon "
        + "itself.\n");
    ::do_die(killer);

}

/*
 * Function name: special_attack
 * Description  : Special attack for this NPC
 * Arguments    : enemy - Object pointer to the living to attack.
 * Returns      : 1 - Made attack, no further attacks this round.
 *                0 - No special attack, continue normal combat round.
 */
public int
special_attack(object enemy)
{
    string tar, wat;
    int add_poison;
    object poison;
    
    if (random(4))
        return 0;      /* 25% chance of special attack. */

    mixed hitresult;
    if (!(hitresult = do_stat_based_attack(this_object(), enemy, W_SLASH)))
    {
        // Could not attack the target, or they evaded.
        return 1;
    }

    tar = QCTNAME(this_object()) + " takes a swipe at you with its "
        + "sharp bony fingers and ";
    wat = QCTNAME(this_object()) + " takes a swipe at " + QTNAME(enemy)
        + " with its sharp bony fingers and ";

    add_poison = 0;
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
            tar += "barely scratches you, drawing a small trickle of blood.\n";
            wat += "barely scratches " + enemy->query_objective() 
                + ", drawing a small trickle of blood.\n";
            break;
        
        case 6..10:
            tar += "gashes you, breaking your skin open.\n";
            wat += "gashes " + enemy->query_objective() + ", breaking "
                + "through the skin to create an open wound.\n";
            break;
        
        case 11..20:
            tar += "rips through your skin, creating a burning sensation "
                + "at the same time as opening up a large wound.\n";
            wat += "rips through " + enemy->query_objective() + " skin, "
                + "opening up a large wound.\n";
            add_poison = 1;
            break;
        
        case 21..40:
            tar += "tears through your defences and takes a chunk of your "
                + "skin. You feel a burning sensation through the pain "
                + "of the attack.\n";
            wat += "tears through " + enemy->query_possessive() + " defences "
                + "and takes a chunk of " + enemy->query_possessive()
                + " skin.\n";
            add_poison = 1;
            break;
        
        default:
            tar += "masterfully works past your defences to deliver a "
                + "deadly wound. You feel a burning sensation as blood "
                + "begins to flow freely from your wound.\n";
            wat += "masterfully works past " + enemy->query_possessive() 
                + "defences to deliver a deadly wound and blood begins "
                + "to flow freely from it.\n";
            add_poison = 1;
            break;
        }
    }
    
    enemy->catch_msg(tar);
    enemy->tell_watcher(wat, enemy);
    
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(this_object());
    }
    else if (add_poison && !present("_heucuva_poison", enemy))
    {
        // Add a poison
        poison = clone_object(POISON_OBJECT);
        poison->set_name("_heucuva_poison");
        poison->move(enemy, 1);
        poison->set_time(60 + random(60));
        poison->set_interval(20);
        poison->set_strength(40);
        poison->set_damage( ({ POISON_FATIGUE, 100, POISON_HP, 30 }) );
        poison->set_poison_type("heucuva");
        poison->start_poison();
    }
        
    return 1;
}
