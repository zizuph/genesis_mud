
/* 
 *  This is Syr-Lin, proprietor of the Shark's Tooth Shack. 
 *
 *  Coded by Maniac 1/9/96 
 */ 

inherit "/std/monster"; 

#include <stdproperties.h>
#include <macros.h> 
#include <ss_types.h>
#include <const.h>
#include "defs.h"

#include HAUNT


void
create_monster()
{
   set_name("syr-Lin"); 
   add_name("syr-lin"); 
   add_name("proprietor"); 
   add_name("shopkeeper"); 

   set_gender(G_FEMALE); 

   set_adj(({"tall", "black-haired"})); 
   set_race_name("human"); 

   set_long(
     "Syr-Lin is the shopkeeper here, a tall young woman dressed " +
     "in working clothes. She recently took over the business from " +
     "her retired father, and makes most of her profit these days from " +
     "the increasing number of adventurers and traders along the " +
     "coast. The locals, however, are often also in need of her wares.\n"); 

   default_config_npc(50);  
   set_skill(SS_UNARM_COMBAT, 35); 
   set_skill(SS_DEFENCE, 35); 

   add_prop(CONT_I_HEIGHT, 180); 
   add_prop(CONT_I_WEIGHT, 60000); 
   add_prop(CONT_I_VOLUME, 60000); 
   add_prop(NPC_I_NO_RUN_AWAY, 1); 
   add_prop(NPC_I_NO_LOOKS, 1); 

   set_act_time(10); 
   add_act("smile"); 
   add_act("twinkle brightly"); 
   add_act("emote fetches a needle and thread to repair some old packs.");  
   add_act("emote polishes some equipment."); 
   add_act("emote inspects her inventory."); 
   add_act("say I'll buy back any of the hardware sold in Calia."); 
}


void
add_introduced(string str)
{
    set_alarm(1.0, 0.0, &command("introduce me")); 
}

