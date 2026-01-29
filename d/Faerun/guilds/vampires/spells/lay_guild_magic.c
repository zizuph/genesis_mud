/*
*  /d/Faerun/guilds/vampires/spells/lay_guild_magic.c
*
*  Command soul for the Vampires, containing the various spells
*  that are available to the players.
*
*  Originally created by Eowul, Oktober 6th, 2009, borrowed
*  and modified by Nerull 2021
*/
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
#include "../guild.h"




/*
* Function name: get_soul_id
* Description:   Give a name for this soul
* Returns:       string - the soul's id
*/
public string
get_soul_id()
{
    return "Vampire Spells";
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
    
            // VAMPIRE SPELLS
            //--------------------------------------------
            "sanctuary" : "do_ability",
            
            
            // Tier 1           
            "resilience" : "do_ability",
            "eluvisveness" : "do_ability",  
            
            "incognito" : "do_ability",

            "childwhisper" : "do_ability",                        
           
            
            //Tier 2
            //ABILITY: ethereal
            "obfuscate" : "do_ability",
            
            "deadeye" : "do_ability",
            
            
            
            //Tier 3
            "lifeward" : "do_ability",
            "regeneration" : "do_ability",
            "amplify" : "do_ability",
            "augmentation" : "do_ability",
            "siphon" : "do_ability",
            //"ABILITY: strangulate"
            
            "celerity" : "do_ability",
            
            
            
            //Tier 4
            //fly
            "swarm" : "do_ability",
            
            //"ABILITY: mesmerize"
            
            
            
            //Tier 5
            // TODO, SPELL: "sigil" : "do_ability",                       
    ]);
}


public mapping
query_ability_map()
{
    return ([
    
           // BASE SPELLS ------------------------------------------------
           "sanctuary" : VAMPIRES_GUILD_DIR + "spells/sanctuary",
           "resilience" : VAMPIRES_GUILD_DIR + "spells/resilience",
           "elusiveness" : VAMPIRES_GUILD_DIR + "spells/elusiveness",
           "incognito" : VAMPIRES_GUILD_DIR + "spells/incognito",
           "obfuscate" : VAMPIRES_GUILD_DIR + "spells/obfuscate",
           "deadeye" : VAMPIRES_GUILD_DIR + "spells/deadeye",
           "lifeward" : VAMPIRES_GUILD_DIR + "spells/lifeward",
           "celerity" : VAMPIRES_GUILD_DIR + "spells/celerity",
           "swarm" : VAMPIRES_GUILD_DIR + "spells/swarm",
           "regeneration" : VAMPIRES_GUILD_DIR + "spells/regeneration",
           "siphon" : VAMPIRES_GUILD_DIR + "spells/siphon",
           "amplify" : VAMPIRES_GUILD_DIR + "spells/amplify",
           "augmentation" : VAMPIRES_GUILD_DIR + "spells/augmentation",
           "childwhisper" : VAMPIRES_GUILD_DIR + "spells/child_whisper",
           "thrallwhisper" : VAMPIRES_GUILD_DIR + "spells/thrall_whisper",
    ]);
}
