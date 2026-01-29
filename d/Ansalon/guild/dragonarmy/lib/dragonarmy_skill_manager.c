/*
 * Dragonarmy Skill Manager
 * 
 * Manager for Skills for the Dragonarmies. This manages all the various
 * skill levels depending on the army you are in, and which promotion
 * level you are at.
 *
 * Created by Petros, February 2009
 */
 
#pragma strict_types

#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

#include "../guild.h"

#define DA_DEBUG(x)        find_player("arman")->catch_msg(x)
#define CLUB_MANAGER        ("/d/Krynn/clubs/warfare/warfare_club_manager")
#define WAR_WINNER          (CLUB_MANAGER->query_army_winner())
#define WAR_ARMY(x)         (CLUB_MANAGER->query_warfare_army_string(x))
#define DA_SECOND_SKILL(x)  CLUB_MANAGER->query_dragonarmy_second_wep(x)
#define DA_SECOND_SKILL_MAX(x)  CLUB_MANAGER->query_dragonarmy_second_wep_skill_bonus(x)


// Secondary weapon skill options
// Only one can be trained up based on participation
// in the warfare system. Functions for skill levels 
// can be found in /d/Krynn/clubs/warfare/warfare_club_manager.c

static mapping dragonarmy_skills_mapping = ([
    RED_ARMY : ([
                    SS_WEP_POLEARM : 100,
                    SS_DEFENCE : 85,
                    SS_PARRY : 85,
                    SS_BLIND_COMBAT : 75,
                    SS_APPR_MON : 70,
                    SS_AWARENESS : 60,
                    SS_ANI_HANDL : 70,
                    SS_DRAGONARMY_ATTACK : 100,
                    SS_WEP_KNIFE : 85,
                    SS_WEP_SWORD : 85,
                    SS_WEP_AXE : 85,
                    SS_WEP_CLUB : 85,
                    SS_WEP_MISSILE : 85,
                    SS_2H_COMBAT : 90,
                    ]),
    BLUE_ARMY : ([
                    SS_WEP_SWORD : 100,
                    SS_DEFENCE : 85,
                    SS_PARRY : 85,
                    SS_2H_COMBAT : 85,
                    SS_BLIND_COMBAT : 75,
                    SS_APPR_MON : 70,
                    SS_AWARENESS : 60,
                    SS_ANI_HANDL : 70,
                    SS_DRAGONARMY_ATTACK : 100,
                    SS_WEP_KNIFE : 85,
                    SS_WEP_POLEARM : 85,
                    SS_WEP_AXE : 85,
                    SS_WEP_CLUB : 85,
                    SS_WEP_MISSILE : 85,
                    ]),
]);                                        

public int
query_skill_exceptions(object player, int snum, int order_max)
{
    int finished_guru, level, max_wep_skill;
    int max_rda_2h = (DA_SECOND_SKILL_MAX(player) + 5);
    string da_army = player->query_dragonarmy_division();
      
    switch (snum)
    {
    case SS_2H_COMBAT:
        if (player->query_dragonarmy_division() != BLUE_ARMY)
        {
                if (WAR_ARMY(da_army) == WAR_WINNER)
                    return max_rda_2h;
                else
                    return max_rda_2h;
        }
        else
        {
            return order_max;
        }
        break;
    case SS_WEP_SWORD:
        if (player->query_dragonarmy_division() != BLUE_ARMY)
        {
            if (DA_SECOND_SKILL(player) == "sword")
            {
                if (WAR_ARMY(da_army) == WAR_WINNER)
                    return DA_SECOND_SKILL_MAX(player);
                else
                    return DA_SECOND_SKILL_MAX(player);
            }
            else
            {
                return 0;
            }
        }
        break;
        
    case SS_WEP_POLEARM:
        if (player->query_dragonarmy_division() != RED_ARMY)
        {
            if (DA_SECOND_SKILL(player) == "polearm")
            {
                if (WAR_ARMY(da_army) == WAR_WINNER)
                    return DA_SECOND_SKILL_MAX(player);
                else
                    return DA_SECOND_SKILL_MAX(player);
            }
            else
            {
                return 0;
            }
        }
        break;

    case SS_WEP_KNIFE:
        if (DA_SECOND_SKILL(player) == "knife")
        {
            if (WAR_ARMY(da_army) == WAR_WINNER)
                return DA_SECOND_SKILL_MAX(player);
            else
                return DA_SECOND_SKILL_MAX(player);
        }
        else
        {
            return 0;
        }
        break;

    case SS_WEP_AXE:
        if (DA_SECOND_SKILL(player) == "axe")
        {
            if (WAR_ARMY(da_army) == WAR_WINNER)
                return DA_SECOND_SKILL_MAX(player);
            else
                return DA_SECOND_SKILL_MAX(player);
        }
        else
        {
            return 0;
        }
        break;

    case SS_WEP_CLUB:
        if (DA_SECOND_SKILL(player) == "club")
        {
            if (WAR_ARMY(da_army) == WAR_WINNER)
                return DA_SECOND_SKILL_MAX(player);
            else
                return DA_SECOND_SKILL_MAX(player);
        }
        else
        {
            return 0;
        }
        break;

    case SS_WEP_MISSILE:
        if (DA_SECOND_SKILL(player) == "bow")
        {
            if (WAR_ARMY(da_army) == WAR_WINNER)
                return DA_SECOND_SKILL_MAX(player);
            else
                return DA_SECOND_SKILL_MAX(player);
        }
        else
        {
            return 0;
        }
        break;
    
    default:
        // No exceptions, just use the order maximum
        return order_max;
    }
        
    finished_guru = player->test_bit("Ansalon", 3, 0);
    level = player->query_dragonarmy_promotions();
    max_wep_skill = 85; // Start out at 85 max
    switch (level)
    {
    case 1:
        max_wep_skill += 10;
        break;
    
    case 2:    
    case 3:
    case 4:
        max_wep_skill += 15;
    }
    
    if (!finished_guru)
    {
        max_wep_skill = min(90, max_wep_skill);
    }
    
    return max_wep_skill;
}

/*
 * Function:        query_skill_max
 * Description:     This function is used by the training
 *                  rooms to determine whether we should
 *                  override the maximums given for the skills.
 * Arguments:       player - person training
 *                  snum   - skill number
 * Returns:         the new maximum level to be trained to
 */
public int
query_skill_max(object player, int snum)
{
    int order_max, adv_guild_max;
    mapping skills;
    string division;
    int max_rda_2h = (DA_SECOND_SKILL_MAX(player) + 5);
    string da_army = player->query_dragonarmy_division();
    
    division = player->query_dragonarmy_division();
    if (!IN_ARRAY(division, m_indices(dragonarmy_skills_mapping)))
    {
        // DA_DEBUG("skill max called, division not defined.\n");
        // Division is not defined
        return 0;
    }
    
    skills = dragonarmy_skills_mapping[division];
    if (!IN_ARRAY(snum, m_indices(skills)))
    {
        // DA_DEBUG("skill max called, skill not available.\n");
        // Skill is not available for this Dragonarmy division
        return 0;
    }
    
    // Check if Council has limited the training for this person
    if (MANAGER->query_punishment(player, PUN_DEATH | PUN_NOTRAIN))
    {
        // DA_DEBUG("skill max called, punished cannot train.\n");
	return 0;
    }
    
    order_max = skills[snum];
    order_max = query_skill_exceptions(player, snum, order_max);
    adv_guild_max = 0;
    if (IN_ARRAY(snum, m_indices(SS_SKILL_DESC)))
    {
        adv_guild_max = SS_SKILL_DESC[snum][4];
    }
    
    if (player->query_stat(SS_OCCUP) < 120)
    {
        // Limit skills traineable by guild stat. Once they achieve
        // guild stat of 120, then their skills are traineable to
        // maximum
        order_max = (order_max - adv_guild_max) 
                        * player->query_stat(SS_OCCUP) / 120;
        order_max = order_max + adv_guild_max;
        // Make sure that they can at least train to adv guild max for
        // everything.
        if (order_max > 0)
        {
            order_max = max(adv_guild_max, order_max);
        }
    }  

    switch (snum)
    {
    case SS_2H_COMBAT:
        if (player->query_dragonarmy_division() != BLUE_ARMY)
        {
                if (WAR_ARMY(da_army) == WAR_WINNER)
                    return max_rda_2h;
                else
                    return max_rda_2h;
        }
        break;
    case SS_WEP_SWORD:
        if (player->query_dragonarmy_division() != BLUE_ARMY)
        {
            if (DA_SECOND_SKILL(player) == "sword")
            {
                if (WAR_ARMY(da_army) == WAR_WINNER)
                {
                    return DA_SECOND_SKILL_MAX(player);
                }
                else
                    return DA_SECOND_SKILL_MAX(player);
            }
            else
            {
                return 0;
            }
        }
        break;
        
    case SS_WEP_POLEARM:
        if (player->query_dragonarmy_division() != RED_ARMY)
        {
            if (DA_SECOND_SKILL(player) == "polearm")
            {
                if (WAR_ARMY(da_army) == WAR_WINNER)
                    return DA_SECOND_SKILL_MAX(player);
                else
                    return DA_SECOND_SKILL_MAX(player);
            }
            else
            {
                return 0;
            }
        }
        break;

    case SS_WEP_KNIFE:
        if (DA_SECOND_SKILL(player) == "knife")
        {
            if (WAR_ARMY(da_army) == WAR_WINNER)
                return DA_SECOND_SKILL_MAX(player);
            else
                return DA_SECOND_SKILL_MAX(player);
        }
        else
        {
            return 0;
        }
        break;

    case SS_WEP_AXE:
        if (DA_SECOND_SKILL(player) == "axe")
        {
            if (WAR_ARMY(da_army) == WAR_WINNER)
                return DA_SECOND_SKILL_MAX(player);
            else
                return DA_SECOND_SKILL_MAX(player);
        }
        else
        {
            return 0;
        }
        break;

    case SS_WEP_CLUB:
        if (DA_SECOND_SKILL(player) == "club")
        {
            if (WAR_ARMY(da_army) == WAR_WINNER)
                return DA_SECOND_SKILL_MAX(player);
            else
                return DA_SECOND_SKILL_MAX(player);
        }
        else
        {
            return 0;
        }
        break;

    case SS_WEP_MISSILE:
        if (DA_SECOND_SKILL(player) == "bow")
        {
            if (WAR_ARMY(da_army) == WAR_WINNER)
                return DA_SECOND_SKILL_MAX(player);
            else
                return DA_SECOND_SKILL_MAX(player);
        }
        else
        {
            return 0;
        }
        break;
    
    default:
        // No exceptions, just use the order maximum
        return order_max;
    }
 
    return order_max;
}
