inherit "/std/monster";
inherit "/std/combat/unarmed";
inherit "/std/act/chat";
inherit "/std/act/action";

#include "defs.h"

#define PIR_I_KILLED_CYCLOPS "_pir_i_killed_cyclops"

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
   add_prop(CONT_I_MAX_VOLUME, 1000000);
   add_prop(LIVE_I_ALWAYSKNOWN,1);
   
   set_alarm(1.0,0.0,"entrance");
   set_alarm(4.0,0.0,"enter_room");
   set_alarm(7.0,0.0,"good_bye");
   
}

int
entrance()
{
   tell_room(ENV(TO),"Thunder echos across the sky as "+
      "Neptune steps forth from the sea.\n");
   return 1;
}

int
enter_room()
{
   object *people;
   int i;
   
   
   people = all_inventory(environment());
   for(i=0; i < sizeof(people) ; i++) {
      if(people[i]->query_prop(PIR_I_KILLED_CYCLOPS)) {
         TO->command("say You have killed my son.");
         TO->command("say You must leave my island.");
         write("You fell yourself magically transfered.\n");
         tell_room(ENV(TO),"Neptune banishes "+QCTNAME(TP)+
            "from the island.\n",TP);
         people->remove_prop(PIR_I_KILLED_CYCLOPS);
         people->remove_prop(PIR_I_KILLED_CYCLOPS);
         people[i]->move_living("X",PIRATES_DIR+"quest/m9");
         TO->command("take corpse");
       }
   }
}


int
good_bye()
{
   tell_room(ENV(TO),"Neptune disappears in a swirl of wind and water.\n");
   TO->remove_object();
   return 1;
}
