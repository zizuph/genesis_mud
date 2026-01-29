inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

query_mm_out(){
   return "summons a street car, enters it. and it dings its way away";
}

query_mm_in(){
   return "is dropped off by a passing street car";
}
query_m_in(){
   return "arrives crouched in a miserable running position";
}
query_m_out(){
   return "runs off";
}

create_monster(){
   
   set_name("destrego");
   set_living_name("destrego");
   set_long(break_string(
         "A loving, wonderful wormy creature. Adorned with wiry glasses, old "
         +"stinky skag clothes and an ermine cape. It is a beautiful creature, "
         +"belonging to a tropical subspecies of the common earthworm, it is "
         +"genuine and bold, above all macho.\n", 70));
   
   set_chat_time(3);
   add_chat("Uh, you aren't very macho!");
   add_chat("I will take you to see my coffins...");
   add_chat("So! We meet again!");
   add_chat("Uh, eh, uh..");
   
   set_act_time(1);
   add_act("emote preens itself.");
   add_act("emote wails loudly!");
   add_act("emote transforms momentarily into an old man!");
   add_act("emote looks upwards, transfixed!");
   add_act("emote suddenly reaches its arms up into the air in joyful desperation!");
   add_act("emote becomes a baby.");
   add_act("emote looks full.");
   add_act("emote stares at you with pride.");
   add_act("emote rolls on the ground!");
   
   
   
}





