
/* 
   This is Rein-Sake, the bartender in the Leaping Dolphin Tavern. 
    
   Codeed by Maniac 13/9/96
*/ 

#include <ss_types.h>
#include <macros.h> 
#include <stdproperties.h>
#include "defs.h"

inherit "/std/monster"; 

#include HAUNT

void
create_monster()
{
    set_name("rein-Sake"); 
    add_name("rein-sake"); 
    add_name("bartender"); 

    set_adj(({"hairy", "smiling"}));  
   
    set_race_name("human"); 

    set_long("This hairy individual is Rein-Sake, the bartender. " +
             "He has a short but wide build, somewhat " + 
             "reminiscent of a dwarf, although his beard " +
             "is nowhere near as impressive. " + 
             "He makes a good living here in his coastal pub, " +
             "especially as more adventurers seem to be " +
             "passing through lately.\n"); 

    default_config_npc(60); 

    set_act_time(1); 
    add_act("emote gives a broad grin.");
    add_act("emote wipes the bar with a towel."); 
    add_act("say Whew, they warned me about drinking on an empty stomach."); 
    add_act("emote throws water over an unconscious villager, " +
            "who sits up groggily."); 
    add_act("emote collects a tip from a satisfied customer."); 
    add_act("say It's hard to tell whether the merfolk are real after " +
            "a visit here."); 
    add_act("say I saw one! I saw a mermaid come in here! When she "+
        "swam up to the shore, her big fin turned into legs and she "+
        "walked right in here! She came from that city under the sea "+
        "she said. When she went back in the sea, her legs turned back "+
        "into a fin. Damnedest thing I'd ever seen after five drinks.");

    set_skill(SS_UNARM_COMBAT, 50); 
    set_skill(SS_DEFENCE, 50); 

    add_prop(NPC_I_NO_RUN_AWAY, 1); 
    add_prop(CONT_I_WEIGHT, 65000); 
    add_prop(CONT_I_VOLUME, 65000); 
}


void
add_introduced(string str)
{
    set_alarm(2.0, 0.0, &command("introduce me")); 
}

