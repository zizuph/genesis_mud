inherit "/std/monster";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <money.h>

create_monster() {
   
   if (!IS_CLONE)
      return;
   
   set_race_name("human");
   set_name("miranda");
   set_short("crying young human");
   set_adj("crying");
   set_gender(1);
   
   set_long("A very sad and depressed woman.  She looks as if " +
            "she has been crying\nfor quite a while.\n");

   set_chat_time(1);
   add_chat("Edward!!");
   set_act_time(1);
   add_act("cry");
   add_chat("Have you seen my Edward?");
   add_chat("My Edward got lost in Ribos, and that monster probably " +
            "ate him!");
   add_act("sob");
   
   default_config_npc(20);
}

age() {
   string *ages;
   ages = ({"young", "old", "mature", "youthful", 
         "ancient", "", "middle-aged"});
   return ages[random(sizeof(ages))];
}

face() {
   string *faces;
   faces = ({"sad", "stupid-looking", "dirty", "optimistic", 
         "blond-haired", "blue-eyed", "sorrowfull"});
   return faces[random(sizeof(faces))];
}




