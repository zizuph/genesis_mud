/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * towerguard.c
 *
 * Vader
 * Modified by Sorgum 950707
 * Modified by Bronco 950719
 *
 * Modified June 2008 by Lilith
 * Experimenting with scalable npcs
 *
 * June 24, 2008  Lilith
 *  Scale-up to 10% max
 *  Natural armour scales to enemy
 *  Added scaling Haste
 *  Heal based off damage done during special
 *  Added some scaling magic and poison res
 *
 * NO ONE COMES TO RIBOS ANYMORE.
 * LETS SEE WHAT I CAN DO TO CHANGE THAT.
 * 
 * Aug 8, 2008  Lilith
 *  Put coins back to where they orignally were. 
 *
 * Aug 9, 2008 Lilith
 *  Ribos npcs had a cloning error in equip_me. Fixed it.
 *
 *  Also, it appears some wizards think adding haste to 
 *   npcs to make them tougher for players to kill is no 
 *   longer a good idea because vamps can drain a little 
 *   bit of haste from npcs, so I've removed the haste and
 *   upped the healing rate. Pandering to Paranoiacs. Bleh.
 *
 * Aug 24, 2008 Lilith
 *   Updated the logging of heals and the frequency.
 *
 * May 2009 Petros
 *   Removed scaling from npcs
 *   Removed resistances
 *   Removed money given. Armours and weapons sufficient treasure
 *   Added blind combat skill to more closely match the goblins who
 *     have see in dark.
 *   Reduced special hit percentage, reduced heal percentage, upped
 *     exp_factor to 115 based on hard hitting specials.
 *   Added up to 7 levels of possible guards
 *   Added ability for knights to team up and assist.
 *
 * September 2009 Petros
 *   Changed random type generation scheme to generate the least available
 *   type always. This allows for more even distribution throughout
 *   Armageddon.
 * 
 * July 2020 Cotillion
 *   XP factor adjusted to 122  
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/d/Genesis/specials/npc/stat_based_specials";

#include <money.h>
#include <composite.h>
#include <options.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

#include "local.h"

#define KILL_FILE	"/d/Terel/ribos/castle/monster/log_deaths"
#define HEAL_FILE	"/d/Terel/ribos/castle/monster/log_heals"

// Define the different guard types
#define GUARD_WEAK      0
#define GUARD_HEFTY     1
#define GUARD_STRONG    2
#define GUARD_NOBLE     3
#define GUARD_POWERFUL  4
#define GUARD_MIGHTY    5
#define GUARD_VALOROUS  6

// Prototypes
public void notify_team_for_help(object attacker, int showmessages = 1);

// Global Variables
public int      Strength = 0;

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
 
   return ({
            CASTLE_DIR + "weapon/thsword",
            CASTLE_DIR + "armour/helmet",
            CASTLE_DIR + "armour/boots",
            CASTLE_DIR + "armour/armour",		
            CASTLE_DIR + "armour/gauntlets"
		});
}

/* 
 * Function:    set_guard_strength
 * Description: Called inside of setup_random_guard, it indicates
 *              which guard type this is.
 */
public void
set_guard_strength(int strength)
{
    Strength = strength;
}

/*
 * Function:    get_guard_strength
 * Description: Returns the value set during the random generation.
 */
public int
get_guard_strength()
{
    return Strength;
}

/*
 * Function:    setup_random_guard
 * Description: This function randomly selects a type of guard
 *              to create. They range from 100-200 stat at 25
 *              stat intervals. They will get a special adjective
 *              to help mortals identify which ones they want to
 *              fight.
 */
public void
setup_random_guard()
{
    int base_stat;    
    string short_desc;
    int guard_type;
    
    // The random generation type will take all the existing guards
    // and try to do an equal distribution.
    object * instances = object_clones(find_object(MASTER));
    if (!sizeof(instances))
    {
        guard_type = random(7);
    }
    else
    {
        int * counts = ({ 0, 0, 0, 0, 0, 0, 0 });
        foreach (object instance : instances)
        {
            int strength = instance->get_guard_strength();
            ++counts[strength];
        }
        int mincount = applyv(min, counts);
        guard_type = max(0, member_array(mincount, counts));
    }
    // Set the strength so that it can be looked up later.
    set_guard_strength(guard_type);
        
    switch (guard_type)
    {
    case GUARD_WEAK:
        add_adj("weak");
        break;
    
    case GUARD_HEFTY:
        add_adj("hefty");
        break;
       
    case GUARD_STRONG:
        add_adj("strong");
        break;
        
    case GUARD_NOBLE:
        add_adj("noble");
        break;
        
    case GUARD_POWERFUL:
        add_adj("powerful");
        break;
        
    case GUARD_MIGHTY:
        add_adj("mighty");
        break;
        
    case GUARD_VALOROUS:
        add_adj("valorous");
        break;
    }
    
    short_desc = implode(query_adjs(), " ") + " human knight";
    set_short(short_desc);
    
    // Set up the actual stats    
    base_stat = 50 + (guard_type * 25) + random(25);
    default_config_npc(base_stat);    
}

/*
 * Function name: create_terel_monster
 * Description:   Create the monster. (standard)
 */
public void
create_terel_monster()
{
    set_name("knight");
    add_name("_ribos_towerguard");
    set_race_name("human");
    set_adj("large");
    setup_random_guard();
    set_long("He is a very large Ribos Knight. His muscles are visible " +
	     "between the gaps in his armour. He is more than willing " +
	     "to ruin your day if you mess with him.\n");

    // Set up the skills after the avg stat has been set
    int avg_stat = query_average_stat();
    set_skill(SS_WEP_SWORD, query_skill_by_stat(avg_stat));
    set_skill(SS_DEFENCE, query_skill_by_stat(avg_stat));
    set_skill(SS_PARRY, query_skill_by_stat(avg_stat));
    set_skill(SS_AWARENESS, query_skill_by_stat(avg_stat));
    set_skill(SS_2H_COMBAT, query_skill_by_stat(avg_stat));
    set_skill(SS_BLIND_COMBAT, query_skill_by_stat(avg_stat));

    set_all_hitloc_unarmed(40); 
    set_alignment(500);
    set_exp_factor(122); // based on healing and special attacks
    
    SET_MAX_HP;

    add_prop(NPC_I_NO_UNARMED, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);

    set_act_time(2);
    add_act("say Move along. No dawdling allowed.");
    add_act("smile sternly");
    add_act("say I defend King and castle.");
    add_act("say I would take that dragon on myself if duty did not "+
        "keep me here.\n");
 
    set_cact_time(5);
    add_cact("say What, are you stupid too?  You should go talk to " +
	     "the priest and ask for forgiveness.");
    add_cact("cackle");
    add_cact("say For King and Ribos!!");
    add_cact("grin");    
}

/*
 * Function name: equip_actions
 * Description:   Initial commands (e.g. wield sword)
 */
public void
equip_actions()
{
    TO->command("wield all");
    TO->command("wear all");
}

/*
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack. 
 */
int
special_attack(object victim)
{
    mixed * hitresult;
    string how, hdesc;
    int avg_stat;
        
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
        return 1;
    }

    // In case someone gets around the attacked_by (attacks then leaves
    // the room for a second), this will guarantee that on every special
    // attack, it will call for help again.
    notify_team_for_help(victim, 0);   
   
    if (random(5))
    {
        // 20% chance of a normal attack.
        return 0;
    }

    if (!(hitresult = do_stat_based_attack(TO, victim, W_BLUDGEON)))
    {
        // Could not attack the target, or they evaded.
        return 1;
    }
        
    if (!strlen(hitresult[1]))
    {
        // Handle misses.
        tell_watcher(QCTNAME(TO) + " tries to bash " + QTNAME(victim) 
            + " but misses completely.\n", victim);
        victim->catch_msg(QCTNAME(TO) + " tries to bash you but misses "
            + "completely!\n");
        return 1;
    }
    
    how = "unharmed";    
    if (hitresult[0] > 0)
        how = "irritated";
    if (hitresult[0] > 20)
        how = "headachy";
    if (hitresult[0] > 50)
        how = "bemused";
    if (hitresult[0] > 100)
        how = "rather dazed";
    
    hdesc = hitresult[1];
    tell_watcher(QCTNAME(TO) + " bashes " + QTNAME(victim) + 
        " on the " + hdesc + " with a gauntleted fist.\n", victim); 
    victim->catch_msg(QCTNAME(TO) + " bashes you on the " + hdesc + " " +
        "with a gauntleted fist!\n");
    victim->catch_msg("You feel " + how + ".\n");

    /* Lets heal me to draw out the fight. 
     * Since it goes off every 5 seconds make it a bit random. 
     */
    if (!random(3)) /* heal with 33% chance */
    {
        int heal = (query_max_hp() / 30);
        TO->heal_hp(heal);
        write_file(HEAL_FILE, ctime(time())+" "+ TO->query_name()  +
            "("+ TO->query_average_stat() +")"+
            " healed "+ heal +" points.\n");
    }
            
    // Special already hit. We shouldn't hit again.  
    return 1;
}

// Adding code to support assisting of teammates

public void
notify_team_for_help(object attacker, int showmessages = 1)
{
    object * friends;
        
    friends = query_team_others();
    foreach (object friend : friends)
    {
        friend->help_friend(attacker, showmessages);
    }    
}

public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
 
    set_alarm(0.5, 0.0, &notify_team_for_help(attacker, 1));
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
public void
help_friend(object attacker, int showmessages)
{   
    if (objectp(attacker) 
        && !objectp(query_attack()) 
        && present(attacker, environment())) 
    {
        if (F_DARE_ATTACK(this_object(), attacker))
        {
            attack_object(attacker);
            attacker->catch_msg(QCTNAME(this_object()) + " attacks "
                + "you!\n");
            tell_room(environment(attacker), QCTNAME(this_object())
                + " attacks " + QTNAME(attacker) + ".\n",
                ({ attacker }));
        }
        else
        {
            if (showmessages)
            {
                attacker->catch_msg(QCTNAME(this_object()) + " looks at you "
                    + "as if ready to attack, though you see fear in "
                    + attacker->query_possessive() + " eyes.\n");
                tell_room(environment(attacker), QCTNAME(this_object())
                    + " looks at " + QTNAME(attacker) + " as if ready to "
                    + "attack, though you see fear in "
                    + attacker->query_possessive() + " eyes.\n",
                    ({ attacker }));
            }
        }
    }
}    

public void
init_living()
{
    ::init_living();
    
    if (sizeof(query_team_others()))
    {
        // Already on a team. No need to look for teammates
        return;
    }
    
    object * all_livings;
    
    all_livings = all_inventory(environment(this_object()));
    all_livings -= ({ this_object() });
    foreach (object friend : all_livings)
    {
        if (MASTER_OB(friend) == MASTER_OB(this_object()))
        {
            object leader;
            if (!objectp(leader = friend->query_leader()))
            {
                leader = friend;
            }
            leader->team_join(this_object());
            return;
        }
    }
}
