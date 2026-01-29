/*
 * Eldoral Standard Skeleton
 *
 * Undead Skeletons for the Eldoral Tunnel Caves and Underground.
 *
 * Created by Petros, November 2008
 */


#include "defs.h"
inherit ELDORAL_UNDEAD_HUMANOID;

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
#include <formulas.h>

public mapping      avail_leftovers = ([
    "tooth" : 5,
    "rib" : 5,
    "thighbone" : 2,
    "skull" : 1 
]);

public string * avail_weapons = ({
    TUN_WEAPONS + "scimitar",
    TUN_WEAPONS + "longsword",
    TUN_WEAPONS + "handaxe",
    TUN_WEAPONS + "spear",
    TUN_WEAPONS + "maul",
});

public string * avail_armours = ({
    TUN_ARMOURS + "plate_armour",
    TUN_ARMOURS + "chainmail",
});
    
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
    set_race_name("skeleton");
    set_short(implode(query_adjs(), " ") + " skeleton");
    set_long("This " + query_short() + " appears to be nothing but a set "
        + "of animated bones. Pinpoints of red light smolder in its "
        + "empty eye sockets. Emanations of corrupt energy can be felt "
        + "whenever you catch its gaze. It seems to be controlled by "
        + "a force beyond that which is natural. You have to wonder "
        + "WHO could possibly be creating and controlling it.\n");

    set_act_time(30);
	add_act("emote moves with crackling bones back and forth.");
	add_act("emote turns its gaze to look at you.");
    add_act("emote sees a bone slightly out of place and carelessly "
        + "pushes it back in.");

    default_config_undead(90);
    
    set_all_hitloc_unarmed( ({ 60, 30, 20 }) );
    
    /* Adjust, Cotillion 2016-02-18, a bit tricky due to different ac 
     * based on damage type. But they're very well equipped for their size. */
    set_exp_factor(180); // high AC with armour, and pretty strong special
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
    MONEY_MAKE_SC(random(10)+2)->move(npc);
}

/*
 * Function:    equip_undead
 * Description: Standard equipping function for the undead creature. This
 *              gets called in default_config_undead, so mask this function
 *              to define what you want the undead to wear and wield.
 * Arguments:   none
 * Returns:     nothing
 */
public void
equip_undead(object npc)
{
    string weapon, armour;
    
    setuid();
    seteuid(getuid());
    weapon = one_of_list(avail_weapons);
    armour = one_of_list(avail_armours);
    if (strlen(weapon))
    {
        clone_object(weapon)->move(npc);
    }
    if (strlen(armour))
    {
        clone_object(armour)->move(npc);
    }
    npc->command("wield all");
    npc->command("wear all");
}

/*
 * Function:    set_undead_skills
 * Description: Default function for setting all the skills that the undead
 *              possesses. Override this to define your own set of skills
 *              in your own undead npc.
 * Arguments:   none
 * Returns:     nothing
 */
public void
set_undead_skills(object npc)
{
    ::set_undead_skills(npc);
    
    int avg_stat;
    
    avg_stat = npc->query_average_stat();
    npc->set_skill(SS_WEP_SWORD, query_skill_by_stat(avg_stat));    
    npc->set_skill(SS_WEP_CLUB, query_skill_by_stat(avg_stat));    
    npc->set_skill(SS_WEP_POLEARM, query_skill_by_stat(avg_stat));    
    npc->set_skill(SS_WEP_AXE, query_skill_by_stat(avg_stat));    
}

public void
do_die(object killer)
{
    string die_message;
    
    switch (random(3))
    {
    case 0:
        die_message = QCTNAME(this_object()) + " glows briefly as the "
            + "corrupt energy that infused its skeletal body departs "
            + "and collapses into a pile of bones.\n";
        break;
    
    case 1:
        die_message = QCTNAME(this_object()) + " grasps around it "
            + "as its eyes grow dim until finally collapsing into "
            + "a mound of bones.\n";
        break;
    
    case 2:
    default:
        die_message = QCTNAME(this_object()) + " shakes violently "
            + "as the corrupt powers that inhabit " 
            + this_object()->query_possessive() + " skeletal body "
            + "depart for good. The violent motion thrusts bones "
            + "everywhere in the room.\n";
        break;
    }
    
    tell_room(environment(this_object()), die_message);
    
    // Move the leftovers into the body
    string * leftovers = m_indices(avail_leftovers);
    // We select two leftovers
    for (int i = 0; i < 2; ++i)
    {
        string leftover = one_of_list(leftovers);
        object bone = clone_object(LEFTOVER_OBJECT);
        bone->leftover_init(leftover, "human");
        bone->move(this_object(), 1);
        leftovers -= ({ leftover });
    }
        
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

    tar = QCTNAME(this_object()) + " reaches out with its sharp claws "
        + "towards you and ";
    wat = QCTNAME(this_object()) + " reaches out with its sharp claws "
        + "towards " + QTNAME(enemy) + " and ";

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
            tar += "slashes you twice with the same claw, opening up a "
                + "painful criss-cross wound.\n";
            wat += "slashes " + enemy->query_objective() + " twice with "
                + "the same claw, opening up a painful criss-cross wound.\n";
            break;
        
        case 11..20:
            tar += "mauls you with one claw, then brings the other "
                + "claw around to rip at your sides.\n";
            wat += "mauls " + enemy->query_objective() + " with one "
                + "claw, then brings the other claw around to rip "
                + "at " + enemy->query_objective() + " sides.\n";
            break;
        
        case 21..40:
            tar += "digs the claw into your shoulder, pulls you towards "
                + this_object()->query_objective() + " with great strength "
                + "and viciously bites you.\n";
            wat += "digs its claws into " + enemy->query_objective() + " shoulder, "
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

