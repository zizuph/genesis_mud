/* 
 * Throtyl Raiders Loot Manager 
 *
 *
 * Created by Arman July 2020
 */

#pragma strict_types

#include <files.h>
#include <ss_types.h>
#include <const.h>
#include "guild.h"
#include "/d/Krynn/common/defs.h"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping      cached_loot_info = ([ ]);

#define CLUBDATA  (GUILD_DIR + "log/")
#define EVENT_LOG (CLUBDATA + "loot_events")

 
// Prototypes

// The create function is called for every object. We mask it here
// to do some basic initialization for the handler
void
create()
{
    setuid();
    seteuid(getuid());
}


/*=======================
 * LOOT-SPECIFIC FUNCTIONS
 ========================*/

/* 
 * Function:    load_loot_info
 * Description: This loads the loot info from their specific file
 *              and returns the mapping of it.
 */
public mapping
load_loot_info()
{
    mapping loot_info;    
        
    loot_info = ([ ]);
        
    // Look for the file
    if (file_size(CLUBDATA + "raider_loot.o") >= 0)
    {
        loot_info = restore_map(CLUBDATA + "raider_loot");
    }

    // Add the value to the cache
    cached_loot_info["raider_loot"] = loot_info;
    return loot_info;
}

/* 
 * Function:    query_loot_property
 * Description: Generic function to return values from the
 *              manager mapping. This will be used by all
 *              customized getters
 */
public mixed
query_loot_property(string prop)
{
    mapping loot_info = load_loot_info();
    
    return loot_info[prop];    
}

/*
 * Function:    set_loot_property
 * Description: Generic function to set the values in
 *              the manager mapping. This will be used by all customized
 *              setters
 */
public string
set_loot_property(string prop, mixed value)
{
    mapping loot_info = load_loot_info();
    
    if (value)
    {
        loot_info[prop] = value;
    }
    else
    {
        m_delkey(loot_info, prop);
    }
    
    cached_loot_info["raider_loot"] = loot_info;
    save_map(loot_info, CLUBDATA + "raider_loot");    
    return "raider_loot";
}



/*===========================================
 *          WARFARE STATS FUNCTIONS
 ============================================*/

public mapping
query_raider_loot()
{ 
    mixed list = query_loot_property("raider_loot");
    
    if (!mappingp(list))
        list = ([ ]);
    
    return list;
}

public void
add_raider_loot(int steel, int platinum, int gold, int silver)
{
    mapping list = query_raider_loot();
    
    if (!m_sizeof(list) || !member_array("raider_loot_tally", m_indexes(list)) > -1)
        list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
    
    set_loot_property("raider_loot", list);
}

public void
increase_coin(string coin, int increase)
{
    mapping list = query_raider_loot();
    int * army_stats;
    int steel, platinum, gold, silver;
    
    if (!m_sizeof(list))
    {
        switch(coin)
        {
            case "steel":
                steel = steel + increase;
                list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                break;
            case "platinum":
                platinum = platinum + increase;
                list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                break;
            case "gold":
                gold = gold + increase;
                list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                break;
            default:
                silver = silver + increase;
                list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                break;
        }
    }
    else if (member_array("raider_loot_tally", m_indexes(list)) == -1)
    {
        switch(coin)
        {
            case "steel":
                steel = steel + increase;
                list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                break;
            case "platinum":
                platinum = platinum + increase;
                list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                break;
            case "gold":
                gold = gold + increase;
                list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                break;
            default:
                silver = silver + increase;
                list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                break;
        }
    }
    else
    {
        foreach(string army_list, int * army_stats : list)
        {
            if(army_list == "raider_loot_tally")
            {
                steel = army_stats[0];
                platinum = army_stats[1];
                gold = army_stats[2];
                silver = army_stats[3];

                switch(coin)
                {
                    case "steel":
                        steel = steel + increase;
                        list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                        break;
                    case "platinum":
                        platinum = platinum + increase;
                        list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                        break;
                    case "gold":
                        gold = gold + increase;
                        list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                        break;
                    default:
                        silver = silver + increase;
                        list += ([ "raider_loot_tally" : ({ steel, platinum, gold, silver }) ]);
                        break;
                }
            }
        }
    }

    set_loot_property("raider_loot", list);
}

