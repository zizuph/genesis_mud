/*  
 * Standard Undead Content Base
 *  
 * This is the base content class for all undeads in Calia. It contains
 * things that can be shared between the humanoid undead base and the
 * creature undead base.
 *
 * Created by Petros, November 2008
 */

#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include "/d/Genesis/gems/gem.h"
#include "../defs.h"

inherit "/d/Genesis/specials/npc/stat_based_specials";

#include "/d/Genesis/specials/debugger/debugger_tell.h"


// Prototypes
public void     add_gem_treasure(object npc);
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
    int avg_stat;
    
    avg_stat = npc->query_average_stat();
    npc->set_skill(SS_UNARM_COMBAT, query_skill_by_stat(avg_stat));
    npc->set_skill(SS_BLIND_COMBAT, query_skill_by_stat(avg_stat));
    npc->set_skill(SS_DEFENCE,      query_skill_by_stat(avg_stat));
    npc->set_skill(SS_AWARENESS,    query_skill_by_stat(avg_stat));       
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
    add_gem_treasure(npc);
}

/*
 * Function:    equip_undead
 * Description: Standard equipping function for the undead creature. This
 *              gets called in default_config_undead, so mask this function
 *              to define what you want the undead to wear and wield.
 * Arguments:   npc - undead to equip
 * Returns:     nothing
 */
public void
equip_undead(object npc)
{
}

public void
add_gem_treasure(object npc)
{
    object gem;
    int quality = GEM_EXTREMELY_COMMON;
    
    if (random(5))
    {
        switch (npc->query_average_stat())
        {
        case 0..25:
            quality = GEM_COMMON;
            break;
        
        case 26..50:
            quality = GEM_SOMEWHAT_COMMON;
            break;
        
        case 51..75:
            quality = GEM_SLIGHTLY_COMMON;
            break;
        
        case 76..100:
            quality = GEM_SLIGHTLY_RARE;
            break;
        
        case 101..125:
            quality = GEM_SOMEWHAT_RARE;
            break;
        
        case 126..150:
            quality = GEM_RARE;
            break;
        
        case 151..175:
            quality = GEM_VERY_RARE;
            break;
        
        break;
            quality = GEM_EXTREMELY_RARE;
            break;
        }
        gem = RANDOM_GEM_BY_RARITY(quality);
        gem->move(npc, 1);
    }    
}
