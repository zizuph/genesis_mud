/*
*  /d/Faerun/guilds/warlocks/lay_guild_magic.c
*
*  Command soul for the Warlocks, containing the various spells
*  that are available to the players.
*
*  Originally created by Eowul, Oktober 6th, 2009, borrowed
*  and modified by Nerull 2017
*/

#include "../guild.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";


/*
* Function name: get_soul_id
* Description:   Give a name for this soul
* Returns:       string - the soul's id
*/
public string
get_soul_id()
{
    return WARLOCK_NAME + " Spells";
}


/*
* Function name: query_cmd_soul
* Description:   identify this as a valid cmdsoul
* Returns:       1
*/
public int
query_cmd_soul()
{
    return 1;
}


public mapping
query_cmdlist()
{
    return ([
    
            // STANDARD WARLOCK SPELLS
            //--------------------------------------------
            "ascendstep" : "do_ability",
            "gate" : "do_ability",      
            "coldlight" : "do_ability",
            "witchstep" : "do_ability", 
            "sculptor-of-flesh" : "do_ability", 
            "disenchant" : "do_ability", 
            "consume" : "do_ability", 
            "immolate" : "do_ability", 
            "desecrate" : "do_ability", 
            "mask" : "do_ability", 
            "eldritch-sight" : "do_ability", 
            "falselife" : "do_ability",
            "rejuvenation":"do_ability",
            "scry" : "do_ability",
            "warp-reality" : "do_ability",
            "gift_of_depth" : "do_ability",
            "infusion" : "do_ability",
            
            // -------------------------------------------
            
            "barkskin" : "do_ability",
            "armor-of-agathys" : "do_ability",
            "spikes" : "do_ability",
            
            "aversion" : "do_ability",
            "spook" : "do_ability",
            "dread" : "do_ability",
            
            "mist" : "do_ability",
            "armor-of-shadows" : "do_ability",
            "schroud" : "do_ability",
            
            "witchbolt" : "do_ability",
            "dream" : "do_ability",
            "detonate" : "do_ability",
            
            //-------------------------------------------
            // "aura1" : "do_ability",
            // "dream_tes" : "do_ability",
    ]);
}


public mapping
query_ability_map()
{
    return ([
    
           // BASE SPELLS ------------------------------------------------
           "ascendstep" : WARLOCK_GUILDDIR + "spells/ascend_step",
           "gate" : WARLOCK_GUILDDIR + "spells/gate",
           "coldlight" : WARLOCK_GUILDDIR + "spells/coldlight",
           "witchstep" : WARLOCK_GUILDDIR + "spells/witchstep",
           "sculptor-of-flesh" : WARLOCK_GUILDDIR + "spells/s_o_flesh",
           "disenchant" : WARLOCK_GUILDDIR + "spells/disenchant",
           "immolate" : WARLOCK_GUILDDIR + "spells/immolate",
           "consume" : WARLOCK_GUILDDIR + "spells/consume",         
           "desecrate" : WARLOCK_GUILDDIR + "spells/desecrate",
           "mask" : WARLOCK_GUILDDIR + "spells/mask",
           "eldritch-sight" : WARLOCK_GUILDDIR + "spells/e_sight",
           "falselife" : WARLOCK_GUILDDIR + "spells/falselife",
           "rejuvenation": WARLOCK_GUILDDIR + "spells/rejuvenation",
           "scry" : WARLOCK_GUILDDIR + "spells/scry", 
           "warp-reality" : WARLOCK_GUILDDIR + "spells/warp_r",
           "gift_of_depth" : WARLOCK_GUILDDIR + "spells/gift_of_depth",
           "infusion" : WARLOCK_GUILDDIR + "spells/infusion",
           
          
          
           "barkskin" : WARLOCK_GUILDDIR + "spells/barkskin",
           "armor-of-agathys" : WARLOCK_GUILDDIR + "spells/a_agathys",
           "spikes" : WARLOCK_GUILDDIR + "spells/spikes",
           
           "aversion" : WARLOCK_GUILDDIR + "spells/aversion",
           "spook" : WARLOCK_GUILDDIR + "spells/spook",
           "dread" : WARLOCK_GUILDDIR + "spells/dread",
           
           "mist" : WARLOCK_GUILDDIR + "spells/mist",
           "armor-of-shadows" : WARLOCK_GUILDDIR + "spells/a_shadows",
           "shroud" : WARLOCK_GUILDDIR + "spells/shroud",
           
           "witchbolt" : WARLOCK_GUILDDIR + "spells/witchbolt",
           "dream" : WARLOCK_GUILDDIR + "spells/dream",
           "detonate" : WARLOCK_GUILDDIR + "spells/detonate",
           
           // "aura1" : WARLOCK_GUILDDIR + "spells/aura_test",
           // "dream_tes" : WARLOCK_GUILDDIR + "spells/dream_tes",
    ]);
}
