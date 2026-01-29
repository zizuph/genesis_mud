
/* 
 *  This is Ripper, a beach comber, shopkeeper in a sea cave.   
 *
 *  Coded by Maniac 28/9/96 
 */ 

inherit "/std/monster"; 

#include <stdproperties.h>
#include <macros.h> 
#include <ss_types.h>
#include <const.h>
#include "defs.h"


void
create_monster()
{
   set_name("ripper"); 
   set_adj(({"ancient", "broad"})); 
   set_race_name("dwarf"); 

   set_long(
     "Ripper the Beach Comber still goes by his early title, although " +
     "many years have passed since the days of his youth, which he spent " +
     "sweeping the coastal beaches for unclaimed odds and ends. " +
     "He has since expanded his business and started his own shop in " +
     "this cave, which was the nearest free location available. Well, " +
     "one has to start somewhere.\n"); 

   set_title("the Beach Comber");  
   
   default_config_npc(50);  
   set_skill(SS_UNARM_COMBAT, 35); 
   set_skill(SS_DEFENCE, 35); 

   add_prop(CONT_I_HEIGHT, 110); 
   add_prop(CONT_I_WEIGHT, 60000); 
   add_prop(CONT_I_VOLUME, 60000); 
   add_prop(NPC_I_NO_RUN_AWAY, 1); 

   set_act_time(10); 
   add_act("emote splashes his feet idly in the water."); 
   add_act("say This place has a major opportunity for growth!");  
   add_act("emote checks his store room for invading crustaceans."); 
   add_act("say What can I do for you?"); 
   add_act("say ok, I know this place isn't perfect, but this time " +
           "next year.."); 
}


void
add_introduced(string str)
{
    set_alarm(1.0, 0.0, &command("introduce me")); 
}

