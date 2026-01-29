/*
 * Knight Skill Manager
 * 
 * Manager for Skills for the Knights. This manages all the various
 * skill levels depending on the order that you are in.
 *
 * Created by Petros, November 2008
 */
 
#pragma strict_types

#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

#include "../guild.h"

// Global Variables
public mapping      weapon_choice_mapping = ([ ]);

// Defines
#define DATA        (KDATA + "secondary_weapon")

// Prototypes
public int      query_secondary_weapon_choice(object player);

static mapping knight_skills_mapping = ([
    L_SQUIRE : ([
                    SS_WEP_SWORD : 50,
                    SS_WEP_POLEARM : 30,
                    SS_WEP_CLUB : 30,
                    SS_2H_COMBAT : 50,
                    SS_BLIND_COMBAT : 30,
                    SS_DEFENCE : 50,
                    SS_PARRY : 50,
                    SS_RESCUE : 50,
                    SS_KATTACK : 50,
                    SS_BLOCK : 50,                    
                    SS_LANGUAGE : 30, // Lowest
                    SS_AWARENESS : 40,
                    SS_RIDING : 30,
                    SS_MOUNTED_COMBAT: 0
                    ]),
    L_CROWN : ([
                    SS_WEP_SWORD : 100,
                    SS_WEP_POLEARM : 30,
                    SS_WEP_CLUB : 30,
                    SS_2H_COMBAT : 75, // High
                    SS_BLIND_COMBAT : 60, // High
                    SS_DEFENCE : 75,
                    SS_PARRY : 90,
                    SS_RESCUE : 100,
                    SS_KATTACK : 100,
                    SS_BLOCK : 100,                    
                    SS_LANGUAGE : 35, // Low
                    SS_AWARENESS : 50, // Low
                    SS_RIDING : 40,
                    SS_MOUNTED_COMBAT: 100
                    ]),
    L_SWORD : ([
                    SS_WEP_SWORD : 100,
                    SS_WEP_POLEARM : 30,
                    SS_WEP_CLUB : 30,
                    SS_2H_COMBAT : 60, // Normal
                    SS_BLIND_COMBAT : 40, // Normal
                    SS_DEFENCE : 75,
                    SS_PARRY : 90,
                    SS_RESCUE : 100,
                    SS_KATTACK : 100,
                    SS_BLOCK : 100,                    
                    SS_LANGUAGE : 55, // Medium
                    SS_AWARENESS : 60, // High
                    SS_RIDING : 40,
                    SS_MOUNTED_COMBAT: 100
                    ]),
    L_ROSE : ([
                    SS_WEP_SWORD : 100,
                    SS_WEP_POLEARM : 30,
                    SS_WEP_CLUB : 30,
                    SS_2H_COMBAT : 60, // Normal
                    SS_BLIND_COMBAT : 40, // Normal
                    SS_DEFENCE : 75,
                    SS_PARRY : 90,
                    SS_RESCUE : 100,
                    SS_KATTACK : 100,
                    SS_BLOCK : 100,                    
                    SS_LANGUAGE : 65, // High
                    SS_AWARENESS : 60, // High
                    SS_RIDING : 40,
                    SS_MOUNTED_COMBAT: 100
                    ]),
]);                    
                    
// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    setuid();
    seteuid(getuid());
    
    if (file_size(DATA + ".o"))
    {
        restore_object(DATA);
    }
}

public int
query_skill_exceptions(object player, int snum, int order_max)
{
    if (snum != SS_WEP_POLEARM && snum != SS_WEP_CLUB)
    {
        // We only care about polearm and club for secondary
        // weapons processing, so just return the original max
        return order_max;
    }
    
    if (query_secondary_weapon_choice(player) == snum)
    {
        // The chosen skill is the secondary weapon. Full knights
        // get sup master. Squires get sup journeyman.
        switch (player->query_knight_level())
        {
        case L_CROWN:
        case L_SWORD:
        case L_ROSE:
            return 90;
        
        case L_SQUIRE:
            return 50;
         
        default:
            break;
        }
    }
    
    return order_max;
}

/*
 * Function:        query_skill_max
 * Description:     This function is used by the training
 *                  rooms to determine whether we should
 *                  override the maximums given for the skills.
 *                  Currently, this is used because Crown
 *                  Knights get to train many of their skills
 *                  to a higher level than other Orders.
 * Arguments:       player - person training
 *                  snum   - skill number
 * Returns:         the new maximum level to be trained to
 */
public int
query_skill_max(object player, int snum)
{
    int knight_level, order_max, adv_guild_max, extra;
    mapping skills;
    
    knight_level = player->query_knight_level();
    if (!IN_ARRAY(knight_level, m_indices(knight_skills_mapping)))
    {
        // Knight level is not defined in mapping
        return 0;
    }
    
    skills = knight_skills_mapping[knight_level];
    if (!IN_ARRAY(snum, m_indices(skills)))
    {
        // Skill is not available for this Knightly order.
        return 0;
    }
    
    order_max = skills[snum];
    order_max = query_skill_exceptions(player, snum, order_max);
    adv_guild_max = 0;
    if (IN_ARRAY(snum, m_indices(SS_SKILL_DESC)))
    {
        adv_guild_max = SS_SKILL_DESC[snum][4];
    }
    if (knight_level == L_SQUIRE)
    {
        // Limit skills traineable by guild stat. Once Squires achieve
        // guild stat of 60, then their skills are traineable to
        // maximum
        extra = (order_max - adv_guild_max) 
                  * player->query_stat(SS_OCCUP) / 60;
        order_max = min(order_max, adv_guild_max + extra);
        // Make sure that they can at least train to adv guild max for
        // everything.
        if (order_max > 0)
        {
            order_max = max(adv_guild_max, order_max);
        }
    }        
    else if (player->query_stat(SS_OCCUP) < 120)
    {
        // Limit skills traineable by guild stat. Once they achieve
        // guild stat of 120, then their skills are traineable to
        // maximum
        extra = (order_max - adv_guild_max) 
                  * player->query_stat(SS_OCCUP) / 60;
        order_max = min(order_max, adv_guild_max + extra);
        // Make sure that they can at least train to adv guild max for
        // everything.
        if (order_max > 0)
        {
            order_max = max(adv_guild_max, order_max);
        }
    }   
    return order_max;
}

public int
set_secondary_weapon_choice(object player, int snum)
{
    int current_selection;
    string name;
    
    if (snum != SS_WEP_POLEARM && snum != SS_WEP_CLUB)
    {
        notify_fail("You can only select either polearms or "
            + "clubs as your secondary weapon.\n");
        return 0;
    }
    
    name = player->query_real_name();
    weapon_choice_mapping[name] = snum;
    
    setuid();
    seteuid(getuid());    
    save_object(DATA);
    return 1;        
}

public int
query_secondary_weapon_choice(object player)
{
    string name;
    
    name = player->query_real_name();
    if (!IN_ARRAY(name, m_indices(weapon_choice_mapping)))
    {
        return 0;
    }
    
    return weapon_choice_mapping[name];
}
