inherit "/std/monster";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";

#include "defs.h"

#define PIR_I_KILLED_GOAT "_pir_i_killed_goat"

void
create_monster()
{
   if (!IS_CLONE)
      return;
   
   set_name("neptune");
   set_short("salty god");
   set_adj("salty");
   add_name("god");
   set_long("He is the god of the sea!\n");
   
   set_base_stat(SS_STR, 101 + random(99));
   set_base_stat(SS_DEX, 100 + random(75));
   set_base_stat(SS_CON, 100 + random(75));
   set_base_stat(SS_INT, 100 + random(50));
   set_base_stat(SS_WIS, 100 + random(50));
   set_base_stat(SS_DIS, 100 + random(75));
   
   heal_hp(9000);
   
   set_skill(SS_DEFENCE, 100);
   set_skill(SS_UNARM_COMBAT,100);
   set_skill(SS_BLIND_COMBAT, 100);
   set_skill(SS_ELEMENT_LIFE, 100);
   set_skill(SS_AWARENESS,100);
   
   add_prop(OBJ_I_WEIGHT, 76000);
   add_prop(CONT_I_MAX_WEIGHT, 200000);
   add_prop(OBJ_I_VOLUME, 89000);
   add_prop(CONT_I_MAX_VOLUME, 100000);
   add_prop(LIVE_I_ALWAYSKNOWN,1);
   
   set_alarm(3.0,0.0,"enter_room");
   set_alarm(7.0,0.0,"instruct");
   set_alarm(11.0,0.0,"good_bye");
   
}

int
enter_room()
{
   object hook, *people;
   int i;
   
   TO->command("say I have witnessed the sacrifice thou hast made.");
   
   people = all_inventory(environment());
   for(i=0; i < sizeof(people) ; i++) {
      if(people[i]->query_prop(PIR_I_KILLED_GOAT)) {
         setuid();
         seteuid(getuid());
         hook = clone_object(PIRATES_DIR+"obj/m_hook");
         hook->move(people[i]);
         TO->command("say For your sacrifice to Me, I present you with a "+
            "gift.");
         people[i]->catch_msg("Neptune gives you a hook.\n");
         tell_room(ENV(TO),"Neptune gives "+ QCTNAME(people[i]) +
            " a hook.\n",people[i]);
         people->remove_prop(PIR_I_KILLED_GOAT);
         people->remove_prop(PIR_I_KILLED_GOAT);
       }
   }
}

int
instruct()
{
   tell_room(ENV(TO),"The hook of Mishrak "+
      "has been lost at the bottom of the ocean for countless ages "+
      "Mishrak's hook is the key to his treasure. "+
      "When you have found the treasure, you must return here "+
      "and cast the hook back into the ocean, its "+
      "proper resting place. If you do this I will help you return "+
      "to Emerald.\n");
   return 1;
}

int
good_bye()
{
   tell_room(ENV(TO),"Neptune disappears in a swirl of wind and water.\n");
   TO->remove_object();
   return 1;
}
